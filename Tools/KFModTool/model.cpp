#include "model.h"
#include <iostream>

Model::Model(TFile & tFile, unsigned int fileIndex)
{
    auto file = tFile.getFile(fileIndex);
    if (!file.isEmpty())
    {
        if (TFile::isMO(file)) // MO File
            loadMO(file);
        else if (TFile::isRTMD(file)) // RTMD File
            loadRTMD(file);
        else if (TFile::isTMD(file)) // TMD File
            loadTMD(file);
        else
            KFMTError::error("Model: Tried to build a model from a file that's not MO, RTMD or TMD.");
    }
}

void Model::loadMO(const QByteArray &file)
{
    QDataStream moStream(file);
    moStream.setByteOrder(QDataStream::LittleEndian);
    
    quint32 tempUInt;
    quint32 animationAmount_;
    quint32 tmdOffset;
    quint32 morphTargetTableOffset;
    quint32 animationTableOffset;

    // Read header
    moStream.setByteOrder(QDataStream::LittleEndian);
    moStream >> tempUInt; // Skip file length
    moStream >> animationAmount_; // Get number of animations
    animations.reserve(animationAmount_);
    moStream >> tmdOffset;
    moStream >> morphTargetTableOffset;
    moStream >> animationTableOffset;
    
    // Here we do things a bit backwards: We'll read the TMD first
    auto tmdSection = file.mid(tmdOffset);
    loadTMD(tmdSection);
    
    // If there are no animations, we pack up and go. This MO serves as just a TMD encapsulator.
    if (animationAmount_ == 0)
        return;
    
    // Read the morph target table offsets
    moStream.device()->seek(morphTargetTableOffset);

    quint32 morphTargetTableEnd;
    // Create vector for the morph target offsets
    std::vector<quint32> morphTargetOffsets;

    // The first morph target offset also serves as the end of the morph target table
    moStream >> morphTargetTableEnd;
    morphTargetOffsets.push_back(morphTargetTableEnd);

    quint32 morphTargetTableSize = (morphTargetTableEnd - morphTargetTableOffset) / 4;
    
    for (size_t i = 0; i < morphTargetTableSize - 1; i++)
    {
        moStream >> tempUInt;
        morphTargetOffsets.push_back(tempUInt);
    }

    // Read the morph targets
    for (const auto &morphTargetOffset : morphTargetOffsets)
    {
        Mesh &referenceMesh = 
                // To define the reference mesh, check if animFrames is empty
                animFrames.empty() ? 
                    // If animFrames is empty, use the base TMD as a reference
                    baseObjects.front() :
                    // otherwise, use the last frame's final morph target
                    morphTargets.at(animFrames.back().targets.back()); 
        
        std::vector<quint32> packetOffsets;
        std::vector<MOPacket> packets;

        // Seek to the morph target's offset
        moStream.device()->seek(morphTargetOffset);

        // Read the amount of packets and preallocates the minimum amount of packets in the morph target
        quint16 packetAmount;
        moStream >> packetAmount;

        // Read the packets
        for (size_t curPacket = 0; curPacket < packetAmount; curPacket++)
        {
            short idOrX; // PacketID for type 1, X delta for type 2
            short numOrY; // Number of dummy packets it represents for type 1, Y delta for type 2
            moStream >> idOrX;
            moStream >> numOrY;
            if (idOrX == static_cast<short>(0x8000))
                for (short curDummyPacket = 0; curDummyPacket < numOrY; curDummyPacket++)
                    packets.emplace_back();
            else
            {
                short zDiff;
                moStream >> zDiff;
                packets.emplace_back(idOrX, numOrY, zDiff);
            }
        }
        
        // Initialize this target's mesh with our reference mesh
        Mesh targetMesh = referenceMesh;
        
        auto packetIt = packets.cbegin();
        auto vertexIt = targetMesh.vertices.begin();
        
        while (packetIt != packets.cend() && vertexIt != targetMesh.vertices.end())
        {
            vertexIt->applyPacket(*packetIt);
            packetIt++;
            vertexIt++;
        };
        
        morphTargets.push_back(targetMesh);
    }

    // Read the animation table

    moStream.device()->seek(animationTableOffset);
    std::vector<quint32> animationOffsets;
    animationOffsets.resize(animationAmount_);

    for (quint32 &animOffset : animationOffsets)
        moStream >> animOffset;

    auto curAnimNo = 0; // Used for printing the animation line
    // Read the animations
    for (const quint32 &animOffset : animationOffsets)
    {
        moStream.device()->seek(animOffset);
        quint32 frameAmount;
        std::vector<quint32> frameOffsets;
        MOAnimation newAnimation;

        moStream >> frameAmount;
        frameOffsets.resize(frameAmount);

        newAnimation.frameIndexes.reserve(frameAmount);

        for (quint32 &frameOffset : frameOffsets)
            moStream >> frameOffset;

        // Read the frames
        for (const quint32 &frameOffset : frameOffsets)
        {

            moStream.device()->seek(frameOffset);
            short unknown00;
            short weight;
            short frameID;
            short targetAmount;

            moStream >> unknown00;
            moStream >> weight;
            moStream >> frameID;
            moStream >> targetAmount;

            MOFrame newFrame(unknown00, weight, frameID, targetAmount);
            for (uint16_t &targetIndex : newFrame.targets)
                moStream >> targetIndex;

            animFrames.push_back(newFrame);
            newAnimation.frameIndexes.push_back(animFrames.size()-1);
        }


        animations.push_back(newAnimation);
        curAnimNo++;
    }
}

void Model::loadRTMD(const QByteArray &file)
{
    // This just calls the TMD loading function and then makes all objects except for the 
    // first one invisible.
    loadTMD(file);
    for (auto objIt = baseObjects.begin() + 1; objIt != baseObjects.end(); objIt++)
        objIt->visible = false;

    //Quick Hack:
    //  Loop through each primitive and convert the vertex offsets to indices
    //
    for(Model::Mesh &mesh : Model::baseObjects)
    {
        for(Model::Primitive &prim : mesh.primitives)
        {
            if(prim.isTriangle())
            {
                prim.vertex0 = prim.vertex0 >> 3;
                prim.vertex1 = prim.vertex1 >> 3;
                prim.vertex2 = prim.vertex2 >> 3;

                prim.normal0 = prim.normal0 >> 3;

                if(prim.isSmooth())
                {
                    prim.normal1 = prim.normal1 >> 3;
                    prim.normal2 = prim.normal2 >> 3;
                }
            }else
            if(prim.isQuad()){
                prim.vertex0 = prim.vertex0 >> 3;
                prim.vertex1 = prim.vertex1 >> 3;
                prim.vertex2 = prim.vertex2 >> 3;
                prim.vertex3 = prim.vertex3 >> 3;

                prim.normal0 = prim.normal0 >> 3;

                if(prim.isSmooth())
                {
                    prim.normal1 = prim.normal1 >> 3;
                    prim.normal2 = prim.normal2 >> 3;
                    prim.normal3 = prim.normal3 >> 3;
                }
            }else{

            }
        }
    }
}

void Model::loadTMD(const QByteArray &file)
{
    QDataStream tmdStream(file);
    tmdStream.setByteOrder(QDataStream::LittleEndian);
    
    // Header section
    uint32_t id;
    uint32_t flags;
    uint32_t nobj;
    
    tmdStream >> id;
    if (id != 0x41 && id != 00)
        KFMTError::error("Model: (R)TMD ID is not 0x41 or 0x00. Bailing out.");
    
    tmdStream >> flags;
    if (flags != 0 && flags != 0x12 && flags != 0x10)
        KFMTError::error( "TMD addresses are not relative. Bailing out.");
    
    tmdStream >> nobj;
    baseObjects.resize(nobj);
    
    quint64 objTableOffset = tmdStream.device()->pos();

    for (quint32 curObj = 0; curObj < nobj; curObj++)
    {
        quint32 verticesOffset;
        quint32 vertexCount;
        quint32 normalsOffset;
        quint32 normalCount;
        quint32 primitivesOffset;
        quint32 primitiveCount;
        qint32 tempScale;

        tmdStream >> verticesOffset;
        tmdStream >> vertexCount;
        tmdStream >> normalsOffset;
        tmdStream >> normalCount;
        tmdStream >> primitivesOffset;
        tmdStream >> primitiveCount;
        tmdStream >> tempScale;
        scale = static_cast<float>(tempScale) / 4096.f;

        verticesOffset += objTableOffset;
        normalsOffset += objTableOffset;
        primitivesOffset += objTableOffset;

        auto &objMesh = baseObjects[curObj];
        
        objMesh.vertices.resize(vertexCount);
        objMesh.normals.resize(normalCount);
        objMesh.primitives.resize(primitiveCount);

        // Read object vertices
        tmdStream.device()->seek(verticesOffset);
        for (auto &vertex : objMesh.vertices)
            vertex.readSVECTOR(tmdStream);

        // Read object normals
        tmdStream.device()->seek(normalsOffset);
        for (auto &normal : objMesh.normals)
            normal.readSVECTOR(tmdStream);

        // Read object primitives
        tmdStream.device()->seek(primitivesOffset);
        for (auto &primitive : objMesh.primitives)
            tmdStream >> primitive;
        
        // Seek to the next object's position in the object table
        tmdStream.device()->seek(objTableOffset + ((curObj + 1) * 28));
    }
}

void Model::Vec3::applyPacket(const MOPacket & packet)
{
    if (packet.x == 0 && packet.y == 0 && packet.z == 0)
        return;
    
    x = static_cast<float>(packet.x) / 4096.f;
    y = static_cast<float>(packet.y) / 4096.f;
    z = static_cast<float>(packet.z) / 4096.f;
}

void Model::Vec3::readSVECTOR(QDataStream & in)
{
    short vx;
    short vy;
    short vz;
    
    in >> vx;
    in >> vy;
    in >> vz;
    in.skipRawData(2);
    
    x = static_cast<float>(vx) / 4096.f;
    y = static_cast<float>(vy) / 4096.f;
    z = static_cast<float>(vz) / 4096.f;
}

QDataStream &operator>>(QDataStream & in, Model::Primitive & primitive)
{
    uint8_t tempByte;
    
    // Lambda for reading gradation if necessary
    auto readGradation = [](QDataStream &inStream, Model::Primitive &prim)
    {
        if (prim.isGradation())
        {
            inStream >> prim.r1;
            inStream >> prim.g1;
            inStream >> prim.b1;
            inStream.skipRawData(1);
            inStream >> prim.r2;
            inStream >> prim.g2;
            inStream >> prim.b2;
            inStream.skipRawData(1);
            if (prim.isQuad())
            {
                inStream >> prim.r3;
                inStream >> prim.g3;
                inStream >> prim.b3;
                inStream.skipRawData(1);
            }
        }
    };
    
    // The elements are read in inverse order because the PS1 is a little endian architecture,
    // and this entire section is read as one 32-bit integer to save speed on the actual hardware.
    in >> primitive.olen;
    in >> primitive.ilen;
    
    in >> tempByte;
    primitive.flag = static_cast<Model::Primitive::PrimitiveFlag>(tempByte);
    
    in >> tempByte;
    primitive.mode = static_cast<Model::Primitive::PrimitiveMode>(tempByte);
    
    if (tempByte < 0x20 || tempByte > 0x7e)
    {
        KFMTError::error(QString::asprintf("Model: TMD: Invalid mode 0x%x.", tempByte));
        in.skipRawData(primitive.ilen);
        return in;
    }
    
    switch(primitive.mode)
    {
        case(Model::Primitive::PrimitiveMode::x22TriFlatNoTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x20TriFlatNoTexOpaqueLit):
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            readGradation(in, primitive);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            break;
        case(Model::Primitive::PrimitiveMode::x26TriFlatTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x24TriFlatTexOpaqueLit):
            in >> primitive.u0;
            in >> primitive.v0;
            in >> primitive.cba;
            in >> primitive.u1;
            in >> primitive.v1;
            in >> primitive.tsb;
            in >> primitive.u2;
            in >> primitive.v2;
            in.skipRawData(2);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            break;
        case(Model::Primitive::PrimitiveMode::x27TriFlatTexTranslucentUnlit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x25TriFlatTexOpaqueUnlit):
            in >> primitive.u0;
            in >> primitive.v0;
            in >> primitive.cba;
            in >> primitive.u1;
            in >> primitive.v1;
            in >> primitive.tsb;
            in >> primitive.u2;
            in >> primitive.v2;
            in.skipRawData(2);
            // FIXME: Is this supposed to be here?
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            in.skipRawData(2);
            break;
        case(Model::Primitive::PrimitiveMode::x2aQuadFlatNoTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x28QuadFlatNoTexOpaqueLit):
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            readGradation(in, primitive);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            in >> primitive.vertex3;
            in.skipRawData(2);
            break;
        case(Model::Primitive::PrimitiveMode::x2eQuadFlatTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x2cQuadFlatTexOpaqueLit):
            in >> primitive.u0;
            in >> primitive.v0;
            in >> primitive.cba;
            in >> primitive.u1;
            in >> primitive.v1;
            in >> primitive.tsb;
            in >> primitive.u2;
            in >> primitive.v2;
            in.skipRawData(2);
            in >> primitive.u3;
            in >> primitive.v3;
            in.skipRawData(2);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            in >> primitive.vertex3;
            in.skipRawData(2);
            break;
        case(Model::Primitive::PrimitiveMode::x32TriGouraudNoTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x30TriGouraudNoTexOpaqueLit):
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            readGradation(in, primitive);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.normal1;
            in >> primitive.vertex1;
            in >> primitive.normal2;
            in >> primitive.vertex2;         
            break;
        case(Model::Primitive::PrimitiveMode::x36TriGouraudTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x34TriGouraudTexOpaqueLit):
            in >> primitive.u0;
            in >> primitive.v0;
            in >> primitive.cba;
            in >> primitive.u1;
            in >> primitive.v1;
            in >> primitive.tsb;
            in >> primitive.u2;
            in >> primitive.v2;
            in.skipRawData(2);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.normal1;
            in >> primitive.vertex1;
            in >> primitive.normal2;
            in >> primitive.vertex2;
            break;
        case(Model::Primitive::PrimitiveMode::x3aQuadGouraudNoTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x38QuadGouraudNoTexOpaqueLit):
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            readGradation(in, primitive);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.normal1;
            in >> primitive.vertex1;
            in >> primitive.normal2;
            in >> primitive.vertex2;
            in >> primitive.normal3;
            in >> primitive.vertex3;           
            break;
        case(Model::Primitive::PrimitiveMode::x3eQuadGouraudTexTranslucentLit):
            primitive.alpha = 127;
        case(Model::Primitive::PrimitiveMode::x3cQuadGouraudTexOpaqueLit):
            in >> primitive.u0;
            in >> primitive.v0;
            in >> primitive.cba;
            in >> primitive.u1;
            in >> primitive.v1;
            in >> primitive.tsb;
            in >> primitive.u2;
            in >> primitive.v2;
            in.skipRawData(2);
            in >> primitive.u3;
            in >> primitive.v3;
            in.skipRawData(2);
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.normal1;
            in >> primitive.vertex1;
            in >> primitive.normal2;
            in >> primitive.vertex2;
            in >> primitive.normal3;
            in >> primitive.vertex3;
            break;
        default:
            KFMTError::error(QString::asprintf("Model: TMD: Unsupported mode 0x%x. Please implement!\n",
                                               static_cast<unsigned int>(primitive.mode)));
            in.skipRawData(primitive.ilen * 4);
            break;
    }
    return in;
}

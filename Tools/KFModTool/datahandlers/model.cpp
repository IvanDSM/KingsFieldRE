#include "model.h"
#include "core/kfmtcore.h"
#include "core/kfmterror.h"
#include "utilities.h"
#include <iostream>
#include <QVector2D>

Model::Model(KFMTFile& modelFile) : KFMTDataHandler(modelFile)
{
    if (core.currentGame() == KFMTCore::SimpleGame::KF1 && Utilities::fileIsMIM(modelFile.rawData))
        loadMIM(modelFile.rawData);
    else if (Utilities::fileIsMO(modelFile.rawData))
        loadMO(modelFile.rawData);
    else if (Utilities::fileIsRTMD(modelFile.rawData))
        loadRTMD(modelFile.rawData);
    else if (Utilities::fileIsTMD(modelFile.rawData))
        loadTMD(modelFile.rawData);
    // Adding handler so ACMission can construct a model container without triggering an error.
    else if (core.currentGame() == KFMTCore::SimpleGame::AC)
    {
        if (modelFile.getDataType() == KFMTFile::DataType::ACMissionStream)
            return; // ACMission populates baseObjects directly
        baseObjects = parseAC1PABlock(modelFile.rawData);
    }
    else
        KFMTError::error(QStringLiteral("Model: Tried to make a model from an unknown file type."));
}

std::vector<Model::Mesh> Model::parseAC1PABlock(const QByteArray& block)
{
    std::vector<Mesh> meshes;
    if (block.size() < 12) return meshes;

    const auto* raw = reinterpret_cast<const uint8_t*>(block.constData());
    auto readU16 = [&](size_t off) -> uint16_t {
        return static_cast<uint16_t>(raw[off] | (raw[off + 1] << 8));
    };
    auto readI16 = [&](size_t off) -> int16_t {
        return static_cast<int16_t>(readU16(off));
    };
    auto readU32 = [&](size_t off) -> uint32_t {
        return static_cast<uint32_t>(raw[off] | (raw[off + 1] << 8) | (raw[off + 2] << 16)
                                     | (raw[off + 3] << 24));
    };

    const uint32_t a0 = readU32(8);
    const uint32_t reloc = a0 + 12;
    if (reloc + 8 > static_cast<size_t>(block.size())) return meshes;

    const uint32_t subCount = readU32(a0 + 8);
    const uint32_t tbl = a0 + 12;

    for (uint32_t i = 0; i < subCount; i++)
    {
        const size_t o = tbl + i * 28;
        if (o + 28 > static_cast<size_t>(block.size())) break;

        const uint16_t flags = readU16(o + 0x0E);
        if (flags & 0x8000) continue; // terminated/skipped sub-object

        const uint32_t vtxOff = readU32(o + 0x00) + reloc;
        const uint16_t vBase = readU16(o + 0x04);
        const uint16_t vDetail = readU16(o + 0x06);
        const uint32_t vtxCnt = vBase + vDetail;

        const uint32_t normOff = readU32(o + 0x08) + reloc;
        const uint16_t normCnt = readU16(o + 0x0C);

        const uint32_t primOff = readU32(o + 0x10) + reloc;
        const uint16_t primBase = readU16(o + 0x14);
        const uint32_t primCnt = primBase + (flags & 0x1FF);

        Mesh mesh;
        mesh.vertices.reserve(vtxCnt);
        for (uint32_t v = 0; v < vtxCnt; v++)
        {
            const size_t p = vtxOff + v * 8;
            if (p + 8 > static_cast<size_t>(block.size())) break;
            // Scale by 1/4096.f to match KFModTool's Vec3::readSVECTOR convention
            mesh.vertices.push_back({static_cast<float>(readI16(p)) / 4096.f,
                                     static_cast<float>(readI16(p + 2)) / 4096.f,
                                     static_cast<float>(readI16(p + 4)) / 4096.f});
        }

        mesh.normals.reserve(normCnt);
        for (uint32_t n = 0; n < normCnt; n++)
        {
            const size_t p = normOff + n * 8;
            if (p + 8 > static_cast<size_t>(block.size())) break;
            mesh.normals.push_back({static_cast<float>(readI16(p)) / 4096.f,
                                    static_cast<float>(readI16(p + 2)) / 4096.f,
                                    static_cast<float>(readI16(p + 4)) / 4096.f});
        }

        size_t cur = primOff;
        for (uint32_t pIdx = 0; pIdx < primCnt && cur + 4 <= static_cast<size_t>(block.size());
             pIdx++)
        {
            const uint8_t b1 = raw[cur + 1];
            const uint8_t rawType = raw[cur + 3];
            const uint8_t typ = rawType & 0xBC;
            const size_t reclen = 4 + b1 * 4;
            if (reclen < 4 || cur + reclen > static_cast<size_t>(block.size())) break;

            Primitive prim{};
            const bool isTex = (typ & 0x04) != 0;
            const bool isQuad = (typ & 0x08) != 0;
            const bool isGouraud = (typ & 0x10) != 0;
            const bool isUnlit = (typ & 0x80) != 0;

            prim.flag = isUnlit
                            ? Primitive::PrimitiveFlag::SingleColorDoubleFaceLightSourceNoCalc
                            : Primitive::PrimitiveFlag::SingleColorDoubleFaceLightSourceCalc;

            if (!isTex && !isQuad && !isGouraud)
                prim.mode = Primitive::PrimitiveMode::x20TriFlatNoTexOpaqueLit;
            else if (isTex && !isQuad && !isGouraud)
                prim.mode = Primitive::PrimitiveMode::x24TriFlatTexOpaqueLit;
            else if (!isTex && isQuad && !isGouraud)
                prim.mode = Primitive::PrimitiveMode::x28QuadFlatNoTexOpaqueLit;
            else if (isTex && isQuad && !isGouraud)
                prim.mode = Primitive::PrimitiveMode::x2cQuadFlatTexOpaqueLit;
            else if (!isTex && !isQuad && isGouraud)
                prim.mode = Primitive::PrimitiveMode::x30TriGouraudNoTexOpaqueLit;
            else if (isTex && !isQuad && isGouraud)
                prim.mode = Primitive::PrimitiveMode::x34TriGouraudTexOpaqueLit;
            else if (!isTex && isQuad && isGouraud)
                prim.mode = Primitive::PrimitiveMode::x38QuadGouraudNoTexOpaqueLit;
            else
                prim.mode = Primitive::PrimitiveMode::x3cQuadGouraudTexOpaqueLit;

            if (!isTex)
            {
                prim.r0 = raw[cur + 4];
                prim.g0 = raw[cur + 5];
                prim.b0 = raw[cur + 6];
            }
            else if (cur + 0x12 <= static_cast<size_t>(block.size()))
            {
                prim.u0 = raw[cur + 4];
                prim.v0 = raw[cur + 5];
                prim.cba = readU16(cur + 6);
                prim.u1 = raw[cur + 8];
                prim.v1 = raw[cur + 9];
                prim.tsb = readU16(cur + 10);
                prim.u2 = raw[cur + 12];
                prim.v2 = raw[cur + 13];
                if (isQuad)
                {
                    prim.u3 = raw[cur + 16];
                    prim.v3 = raw[cur + 17];
                }
                if (isUnlit && cur + (isQuad ? 0x18 : 0x14) <= static_cast<size_t>(block.size()))
                {
                    const size_t colOff = isQuad ? cur + 0x14 : cur + 0x10;
                    prim.r0 = static_cast<uint8_t>(std::min(255, raw[colOff] * 2));
                    prim.g0 = static_cast<uint8_t>(std::min(255, raw[colOff + 1] * 2));
                    prim.b0 = static_cast<uint8_t>(std::min(255, raw[colOff + 2] * 2));
                }
            }

            // Vertex index offset & stride per PA_FORMAT.md table
            size_t vOff = 0;
            size_t vStride = isGouraud ? 4 : 2;
            switch (typ)
            {
                case 0x20: case 0x28: case 0x30: case 0x38: vOff = 0x0A; break;
                case 0x24: case 0x34: vOff = 0x12; break;
                case 0x2C: case 0x3C: vOff = 0x16; break;
                case 0xA0: case 0xA8: vOff = 0x08; break;
                case 0xA4: vOff = 0x14; break;
                case 0xAC: vOff = 0x18; break;
                default: break;
            }

            const size_t nVerts = isQuad ? 4 : 3;
            if (vOff > 0 && cur + vOff + vStride * (nVerts - 1) + 2 <= static_cast<size_t>(block.size()))
            {
                prim.vertex0 = readU16(cur + vOff);
                prim.vertex1 = readU16(cur + vOff + vStride);
                prim.vertex2 = readU16(cur + vOff + vStride * 2);
                if (isQuad) prim.vertex3 = readU16(cur + vOff + vStride * 3);

                if (!isUnlit)
                {
                    prim.normal0 = readU16(cur + vOff - 2);
                    if (isGouraud)
                    {
                        prim.normal1 = readU16(cur + vOff + vStride - 2);
                        prim.normal2 = readU16(cur + vOff + vStride * 2 - 2);
                        if (isQuad) prim.normal3 = readU16(cur + vOff + vStride * 3 - 2);
                    }
                }

                // Bounds check before adding primitive
                const size_t maxV = mesh.vertices.size();
                if (prim.vertex0 < maxV && prim.vertex1 < maxV && prim.vertex2 < maxV
                    && (!isQuad || prim.vertex3 < maxV))
                {
                    mesh.primitives.push_back(prim);
                }
            }

            cur += reclen;
        }

        // Adding this for a fallback normal check so unlit primitives never index empty normals vector
        if (mesh.normals.empty()) mesh.normals.push_back({0.f, 1.f, 0.f});

        meshes.push_back(std::move(mesh));
    }

    return meshes;
}

void Model::fixShiftedIndices()
{
    //Quick Hack:
    //  Loop through each primitive and convert the vertex offsets to indices
    //
    for (Model::Mesh& mesh : Model::baseObjects)
    {
        for (Model::Primitive& prim : mesh.primitives)
        {
            prim.vertex0 = prim.vertex0 >> 3;
            prim.vertex1 = prim.vertex1 >> 3;
            prim.vertex2 = prim.vertex2 >> 3;
            if (prim.isQuad()) prim.vertex3 = prim.vertex3 >> 3;

            prim.normal0 = prim.normal0 >> 3;

            if (prim.isSmooth())
            {
                prim.normal1 = prim.normal1 >> 3;
                prim.normal2 = prim.normal2 >> 3;
                if (prim.isQuad()) prim.normal3 = prim.normal3 >> 3;
            }
        }
    }
}

void Model::loadMIM(const QByteArray& file)
{
    QDataStream mimStream(file);
    mimStream.setByteOrder(QDataStream::LittleEndian);

    const auto header = readMIMOrMOHeader(mimStream);
    const auto tmdSection = file.mid(header.tmdOffset);

    if (!Utilities::fileIsTMD(tmdSection))
    {
        KFMTError::error("Model::loadMIM: Did not find a TMD at the expected location!");
        return;
    }

    loadTMD(tmdSection);

    return;

    // If there are no animations, we pack up and go. This MO serves as just a TMD encapsulator.
    if (header.animationCount == 0) return;

    // Read the morph target table offsets
    mimStream.device()->seek(header.morphTargetsOffset);

    quint32 morphTargetTableEnd;
    // Create vector for the morph target offsets
    std::vector<quint32> morphTargetOffsets;

    // The first morph target offset also serves as the end of the morph target table
    mimStream >> morphTargetTableEnd;
    morphTargetOffsets.push_back(morphTargetTableEnd);

    quint32 morphTargetTableSize = (morphTargetTableEnd - header.morphTargetsOffset) / 4;

    for (size_t i = 0; i < morphTargetTableSize - 1; i++)
    {
        uint32_t morphTargetOffset;
        mimStream >> morphTargetOffset;
        morphTargetOffsets.push_back(morphTargetOffset);
    }

    // Read the morph targets
    for (const auto& morphTargetOffset : morphTargetOffsets)
    {
        // To define the reference mesh, check if animFrames is empty
        // If animFrames is empty, use the base TMD as a reference
        // otherwise, use the last frame's final morph target
        Mesh targetMesh = animFrames.empty() ? baseObjects.front()
                                             : morphTargets.at(animFrames.back().targets.back());

        // Seek to the morph target's offset
        mimStream.device()->seek(morphTargetOffset);

        // Skip the two unknown uints at the beginning of a MIM morph target
        mimStream.skipRawData(8u);

        uint32_t vertexAmount;
        mimStream >> vertexAmount;

        for (size_t curVertex = 0; curVertex < vertexAmount; curVertex++)
        {
            Vec3 morph;
            if (morph.x == 0 && morph.y == 0 && morph.z == 0) continue;
        }

        morphTargets.push_back(targetMesh);
    }
}

void Model::loadMO(const QByteArray& file)
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
    moStream >> tempUInt;         // Skip file length
    moStream >> animationAmount_; // Get number of animations
    animations.reserve(animationAmount_);
    moStream >> tmdOffset;
    moStream >> morphTargetTableOffset;
    moStream >> animationTableOffset;

    // Here we do things a bit backwards: We'll read the TMD first
    auto tmdSection = file.mid(tmdOffset);

    if (!Utilities::fileIsTMD(tmdSection))
    {
        KFMTError::error("Model::loadMO: Did not find a TMD at the expected location!");
        return;
    }

    loadTMD(tmdSection);

    // If there are no animations, we pack up and go. This MO serves as just a TMD encapsulator.
    if (animationAmount_ == 0 || Utilities::fileIsSTTMD(tmdSection)) return;

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
    for (const auto& morphTargetOffset : morphTargetOffsets)
    {
        Mesh& referenceMesh =
            // To define the reference mesh, check if animFrames is empty
            animFrames.empty() ?
                               // If animFrames is empty, use the base TMD as a reference
                baseObjects.front()
                               :
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
            short idOrX;  // PacketID for type 1, X delta for type 2
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

    for (quint32& animOffset : animationOffsets) moStream >> animOffset;

    auto curAnimNo = 0; // Used for printing the animation line
    // Read the animations
    for (const quint32& animOffset : animationOffsets)
    {
        moStream.device()->seek(animOffset);
        quint32 frameAmount;
        std::vector<quint32> frameOffsets;
        MOAnimation newAnimation;

        moStream >> frameAmount;
        frameOffsets.resize(frameAmount);

        newAnimation.frameIndexes.reserve(frameAmount);

        for (quint32& frameOffset : frameOffsets) moStream >> frameOffset;

        // Read the frames
        for (const quint32& frameOffset : frameOffsets)
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
            for (uint16_t& targetIndex : newFrame.targets) moStream >> targetIndex;

            animFrames.push_back(newFrame);
            newAnimation.frameIndexes.push_back(animFrames.size() - 1);
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

    fixShiftedIndices();
}

void Model::loadTMD(const QByteArray& file)
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
        KFMTError::error("TMD addresses are not relative. Bailing out.");

    tmdStream >> nobj;
    baseObjects.resize(nobj);

    quint64 objTableOffset = tmdStream.device()->pos();

    // We need to check if this is a Shadow Tower TMD file or a traditional TMD file.
    // You'll find out why soon.
    bool isShadowTower = Utilities::fileIsSTTMD(file);

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
        if (!isShadowTower)
        {
            tmdStream >> tempScale;
            scale = static_cast<float>(tempScale) / 4096.f;
        }

        verticesOffset += objTableOffset;
        normalsOffset += objTableOffset;
        primitivesOffset += objTableOffset;

        auto& obj = baseObjects[curObj];

        obj.vertices.resize(vertexCount);
        obj.normals.resize(normalCount);
        obj.primitives.resize(primitiveCount);

        // Shadow Tower has a customized TMD that does some funky stuff to eliminate the 4 byte
        // overhead of the primitive header, replacing that with a fixed number of primitive counts
        // in the TMD header.

        uint16_t stPrimx24Count; // Size: 0x14
        uint16_t stPrimx34Count; // Size: 0x18
        uint16_t stPrimx2cCount; // Size: 0x1c
        uint16_t stPrimx3cCount; // Size: 0x20
        uint16_t stPrimx20Count;
        uint16_t stPrimx30Count;
        uint16_t stPrimx28Count;
        uint16_t stPrimx38Count;

        if (isShadowTower)
        {
            tmdStream >> stPrimx24Count;
            tmdStream >> stPrimx34Count;
            tmdStream >> stPrimx2cCount;
            tmdStream >> stPrimx3cCount;
            tmdStream >> stPrimx20Count;
            tmdStream >> stPrimx30Count;
            tmdStream >> stPrimx28Count;
            tmdStream >> stPrimx38Count;

            size_t curPrim = 0;

            for (uint16_t i = 0; i < stPrimx24Count; i++, curPrim++)
            {
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x24TriFlatTexOpaqueLit;
                obj.primitives[curPrim].readx24(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx34Count; i++, curPrim++)
            {
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x34TriGouraudTexOpaqueLit;
                obj.primitives[curPrim].readx34(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx2cCount; i++, curPrim++)
            {
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x2cQuadFlatTexOpaqueLit;
                obj.primitives[curPrim].readx2c(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx3cCount; i++, curPrim++)
            {
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x3cQuadGouraudTexOpaqueLit;
                obj.primitives[curPrim].readx3c(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx20Count; i++, curPrim++)
            {
                obj.primitives[curPrim].flag
                    = Primitive::PrimitiveFlag::SingleColorSingleFaceLightSourceCalc;
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x20TriFlatNoTexOpaqueLit;
                obj.primitives[curPrim].readx20(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx30Count; i++, curPrim++)
            {
                obj.primitives[curPrim].flag
                    = Primitive::PrimitiveFlag::SingleColorSingleFaceLightSourceCalc;
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x30TriGouraudNoTexOpaqueLit;
                obj.primitives[curPrim].readx30(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx28Count; i++, curPrim++)
            {
                obj.primitives[curPrim].flag
                    = Primitive::PrimitiveFlag::SingleColorSingleFaceLightSourceCalc;
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x28QuadFlatNoTexOpaqueLit;
                obj.primitives[curPrim].readx28(tmdStream);
            }
            for (uint16_t i = 0; i < stPrimx38Count; i++, curPrim++)
            {
                obj.primitives[curPrim].flag
                    = Primitive::PrimitiveFlag::SingleColorSingleFaceLightSourceCalc;
                obj.primitives[curPrim].mode = Primitive::PrimitiveMode::x38QuadGouraudNoTexOpaqueLit;
                obj.primitives[curPrim].readx38(tmdStream);
            }

            fixShiftedIndices();
        }

        // Read object vertices
        tmdStream.device()->seek(verticesOffset);
        for (auto& vertex : obj.vertices) vertex.readSVECTOR(tmdStream);

        // Read object normals
        tmdStream.device()->seek(normalsOffset);
        for (auto& normal : obj.normals) normal.readSVECTOR(tmdStream);

        if (!isShadowTower)
        {
            // Read object primitives
            tmdStream.device()->seek(primitivesOffset);
            for (auto& primitive : obj.primitives) primitive.readFrom(tmdStream);
        }

        // Seek to the next object's position in the object table
        // ST TMD object tables are bigger than normal TMDs, so we need a distinction
        if (isShadowTower)
            tmdStream.device()->seek(objTableOffset + ((curObj + 1u) * 40u));
        else
            tmdStream.device()->seek(objTableOffset + ((curObj + 1u) * 28u));
    }
}

Model::MIMOrMOHeader Model::readMIMOrMOHeader(QDataStream& stream)
{
    MIMOrMOHeader header{};

    stream.skipRawData(4u);          // Skip file length
    stream >> header.animationCount; // Get number of animations
    stream >> header.tmdOffset;
    stream >> header.morphTargetsOffset;
    stream >> header.animationsOffset;

    return header;
}

void Model::Vec3::applyPacket(const MOPacket& packet)
{
    if (packet.x == 0 && packet.y == 0 && packet.z == 0)
        return;
    
    x = static_cast<float>(packet.x) / 4096.f;
    y = static_cast<float>(packet.y) / 4096.f;
    z = static_cast<float>(packet.z) / 4096.f;
}

void Model::Vec3::readSVECTOR(QDataStream& in)
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

static constexpr std::array<QVector2D, 32> tPageCoords{
    QVector2D(0.f, 0.f), // TPage 0 - I have to write the intializer out like this
    {256.f, 0.f},        // TPage 1
    {512.f, 0.f},        // TPage 2
    {768.f, 0.f},        // TPage 3
    {1024.f, 0.f},       // TPage 4
    {1280.f, 0.f},       // TPage 5
    {1536.f, 0.f},       // TPage 6
    {1792.f, 0.f},       // TPage 7
    {2048.f, 0.f},       // TPage 8
    {2304.f, 0.f},       // TPage 9
    {2560.f, 0.f},       // TPage 10
    {2816.f, 0.f},       // TPage 11
    {3072.f, 0.f},       // TPage 12
    {3328.f, 0.f},       // TPage 13
    {3584.f, 0.f},       // TPage 14
    {3840.f, 0.f},       // TPage 15
    {0.f, 256.f},        // TPage 16
    {256.f, 256.f},      // TPage 17
    {512.f, 256.f},      // TPage 18
    {768.f, 256.f},      // TPage 19
    {1024.f, 256.f},     // TPage 20
    {1280.f, 256.f},     // TPage 21
    {1536.f, 256.f},     // TPage 22
    {1792.f, 256.f},     // TPage 23
    {2048.f, 256.f},     // TPage 24
    {2304.f, 256.f},     // TPage 25
    {2560.f, 256.f},     // TPage 26
    {2816.f, 256.f},     // TPage 27
    {3072.f, 256.f},     // TPage 28
    {3328.f, 256.f},     // TPage 29
    {3584.f, 256.f},     // TPage 30
    {3840.f, 256.f},     // TPage 31
};

std::vector<QVector2D> Model::Primitive::getAdaptedTexCoords() const
{
    std::vector<QVector2D> adaptedCoords;

    if (isTriangle())
        adaptedCoords.resize(3);
    else if (isQuad())
        adaptedCoords.resize(4);
    else
        KFMTError::fatalError(QStringLiteral(
            "Tried to adapt texcoords for primitive which is neither tri nor quad."));

    std::fill(adaptedCoords.begin(), adaptedCoords.end(), tPageCoords[tsb & 0x1fu]);

    float fixedU0 = u0;
    float fixedU1 = u1;
    float fixedU2 = u2;
    float fixedU3 = u3;

    adaptedCoords[0] += {fixedU0, static_cast<float>(v0)};
    adaptedCoords[1] += {fixedU1, static_cast<float>(v1)};
    adaptedCoords[2] += {fixedU2, static_cast<float>(v2)};
    if (isQuad()) adaptedCoords[3] += {fixedU3, static_cast<float>(v3)};

    for (auto& coord : adaptedCoords)
    {
        coord /= {4096.f, 512.f};
        //coord.setY(1.f - coord.y());
    }

    return adaptedCoords;
}

void Model::Primitive::readFrom(QDataStream& stream)
{
    uint8_t tempByte;

    // The elements are read in inverse order because the PS1 is a little endian architecture,
    // and this entire section is read as one 32-bit integer to save speed on the actual hardware.
    stream >> olen;
    stream >> ilen;

    stream >> tempByte;
    flag = static_cast<Model::Primitive::PrimitiveFlag>(tempByte);

    stream >> tempByte;
    mode = static_cast<Model::Primitive::PrimitiveMode>(tempByte);

    if (tempByte < 0x20 || tempByte > 0x7e)
    {
        KFMTError::error(
            QString::asprintf("Model: TMD: Invalid mode 0x%x (ilen = %d).", tempByte, ilen));
        stream.skipRawData(ilen * 4);
        return;
    }

    switch (mode)
    {
        case (Model::Primitive::PrimitiveMode::x22TriFlatNoTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x20TriFlatNoTexOpaqueLit): readx20(stream); break;
        case (Model::Primitive::PrimitiveMode::x26TriFlatTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x24TriFlatTexOpaqueLit): readx24(stream); break;
        case (Model::Primitive::PrimitiveMode::x27TriFlatTexTranslucentUnlit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x25TriFlatTexOpaqueUnlit): readx25(stream); break;
        case (Model::Primitive::PrimitiveMode::x2aQuadFlatNoTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x28QuadFlatNoTexOpaqueLit): readx28(stream); break;
        case (Model::Primitive::PrimitiveMode::x2eQuadFlatTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x2cQuadFlatTexOpaqueLit): readx2c(stream); break;
        case (Model::Primitive::PrimitiveMode::x32TriGouraudNoTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x30TriGouraudNoTexOpaqueLit): readx30(stream); break;
        case (Model::Primitive::PrimitiveMode::x36TriGouraudTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x34TriGouraudTexOpaqueLit): readx34(stream); break;
        case (Model::Primitive::PrimitiveMode::x3aQuadGouraudNoTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x38QuadGouraudNoTexOpaqueLit):
            readx38(stream);
            break;
        case (Model::Primitive::PrimitiveMode::x3eQuadGouraudTexTranslucentLit):
            alpha = 127;
            [[fallthrough]];
        case (Model::Primitive::PrimitiveMode::x3cQuadGouraudTexOpaqueLit): readx3c(stream); break;
        default:
            KFMTError::error(QString::asprintf("Model: TMD: Unsupported mode 0x%x. Please "
                                               "implement!\n",
                                               static_cast<unsigned int>(mode)));
            stream.skipRawData(ilen * 4);
            break;
    }
}

void Model::Primitive::readx20(QDataStream& stream)
{
    stream >> r0;
    stream >> g0;
    stream >> b0;
    stream.skipRawData(1);
    readGradation(stream);
    stream >> normal0;
    stream >> vertex0;
    stream >> vertex1;
    stream >> vertex2;
}

void Model::Primitive::readx24(QDataStream& stream)
{
    stream >> u0;
    stream >> v0;
    stream >> cba;
    stream >> u1;
    stream >> v1;
    stream >> tsb;
    stream >> u2;
    stream >> v2;
    stream.skipRawData(2);
    stream >> normal0;
    stream >> vertex0;
    stream >> vertex1;
    stream >> vertex2;
}

void Model::Primitive::readx25(QDataStream& stream)
{
    stream >> u0;
    stream >> v0;
    stream >> cba;
    stream >> u1;
    stream >> v1;
    stream >> tsb;
    stream >> u2;
    stream >> v2;
    stream.skipRawData(2);
    // FIXME: Is this supposed to be here?
    stream >> r0;
    stream >> g0;
    stream >> b0;
    stream.skipRawData(1);
    stream >> vertex0;
    stream >> vertex1;
    stream >> vertex2;
    stream.skipRawData(2);
}

void Model::Primitive::readx28(QDataStream& stream)
{
    stream >> r0;
    stream >> g0;
    stream >> b0;
    stream.skipRawData(1);
    readGradation(stream);
    stream >> normal0;
    stream >> vertex0;
    stream >> vertex1;
    stream >> vertex2;
    stream >> vertex3;
    stream.skipRawData(2);
}

void Model::Primitive::readx2c(QDataStream& stream)
{
    stream >> u0;
    stream >> v0;
    stream >> cba;
    stream >> u1;
    stream >> v1;
    stream >> tsb;
    stream >> u2;
    stream >> v2;
    stream.skipRawData(2);
    stream >> u3;
    stream >> v3;
    stream.skipRawData(2);
    stream >> normal0;
    stream >> vertex0;
    stream >> vertex1;
    stream >> vertex2;
    stream >> vertex3;
    stream.skipRawData(2);
}

void Model::Primitive::readx30(QDataStream& stream)
{
    stream >> r0;
    stream >> g0;
    stream >> b0;
    stream.skipRawData(1);
    readGradation(stream);
    stream >> normal0;
    stream >> vertex0;
    stream >> normal1;
    stream >> vertex1;
    stream >> normal2;
    stream >> vertex2;
}

void Model::Primitive::readx34(QDataStream& stream)
{
    stream >> u0;
    stream >> v0;
    stream >> cba;
    stream >> u1;
    stream >> v1;
    stream >> tsb;
    stream >> u2;
    stream >> v2;
    stream.skipRawData(2);
    stream >> normal0;
    stream >> vertex0;
    stream >> normal1;
    stream >> vertex1;
    stream >> normal2;
    stream >> vertex2;
}

void Model::Primitive::readx38(QDataStream& stream)
{
    stream >> r0;
    stream >> g0;
    stream >> b0;
    stream.skipRawData(1);
    readGradation(stream);
    stream >> normal0;
    stream >> vertex0;
    stream >> normal1;
    stream >> vertex1;
    stream >> normal2;
    stream >> vertex2;
    stream >> normal3;
    stream >> vertex3;
}

void Model::Primitive::readx3c(QDataStream& stream)
{
    stream >> u0;
    stream >> v0;
    stream >> cba;
    stream >> u1;
    stream >> v1;
    stream >> tsb;
    stream >> u2;
    stream >> v2;
    stream.skipRawData(2);
    stream >> u3;
    stream >> v3;
    stream.skipRawData(2);
    stream >> normal0;
    stream >> vertex0;
    stream >> normal1;
    stream >> vertex1;
    stream >> normal2;
    stream >> vertex2;
    stream >> normal3;
    stream >> vertex3;
}

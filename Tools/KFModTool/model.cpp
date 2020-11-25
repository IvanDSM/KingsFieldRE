#include "model.h"

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
    
}

void Model::loadRTMD(const QByteArray &file)
{
    
}

void Model::loadTMD(const QByteArray &file)
{
    QDataStream in(file);
    
    // Header section
    uint32_t id;
    uint32_t flags;
    uint32_t nobj;
    
    in >> id;
    if (id != 0x41)
        KFMTError::error("Model: TMD ID is not 0x41. Bailing out.");
    
    in >> flags;
    if (flags != 0)
        KFMTError::error( "TMD addresses are not relative. Bailing out.");
    
    in >> nobj;
    
    
    quint64 objTableOffset = in.device()->pos();

    for (quint32 curObj = 0; curObj < nobj; curObj++)
    {
        quint32 verticesOffset;
        quint32 vertexCount;
        quint32 normalsOffset;
        quint32 normalCount;
        quint32 primitivesOffset;
        quint32 primitiveCount;
        qint32 tempScale;

        in >> verticesOffset;
        in >> vertexCount;
        in >> normalsOffset;
        in >> normalCount;
        in >> primitivesOffset;
        in >> primitiveCount;
        in >> tempScale;
        scale = static_cast<float>(tempScale) / 4096.f;

        verticesOffset += objTableOffset;
        normalsOffset += objTableOffset;
        primitivesOffset += objTableOffset;

        baseMesh.vertices.resize(vertexCount);
        normals.resize(normalCount);
        primitives.resize(primitiveCount);

        // Read object vertices
        in.device()->seek(verticesOffset);
        for (auto &vertex : baseMesh.vertices)
            vertex.readSVECTOR(in);

        // Read object normals
        in.device()->seek(normalsOffset);
        for (auto &normal : normals)
            normal.readSVECTOR(in);

        // Read object primitives
        in.device()->seek(primitivesOffset);
        for (auto &primitive : primitives)
        {
            in >> primitive;
        }
    }
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
    
    // The elements are read in inverse order because the PS1 is a little endian architecture,
    // and this entire section is read as one 32-bit integer to save speed.
    in >> primitive.olen;
    in >> primitive.ilen;
    
    in >> tempByte;
    primitive.flag = static_cast<Model::Primitive::PrimitiveFlag>(tempByte);
    
    in >> tempByte;
    primitive.mode = static_cast<Model::Primitive::PrimitiveMode>(tempByte);
    
    switch(primitive.mode)
    {
        case(Model::Primitive::PrimitiveMode::TriFlatNoTexOpaqueLit):
            in >> primitive.r0;
            in >> primitive.g0;
            in >> primitive.b0;
            in.skipRawData(1);
            if (Model::Primitive::isGradation(primitive.flag))
            {
                in >> primitive.r1;
                in >> primitive.g1;
                in >> primitive.b1;
                in.skipRawData(1);
                in >> primitive.r2;
                in >> primitive.g2;
                in >> primitive.b2;
                in.skipRawData(1);
            }
            in >> primitive.normal0;
            in >> primitive.vertex0;
            in >> primitive.vertex1;
            in >> primitive.vertex2;
            break;
        case(Model::Primitive::PrimitiveMode::TriFlatTexOpaqueLit):
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
        case(Model::Primitive::PrimitiveMode::TriGouraudTexOpaqueLit):
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
        case(Model::Primitive::PrimitiveMode::TriGouraudTexTranslucentLit):
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
        default:
            KFMTError::error(QString::asprintf("Model: TMD: Unsupported mode 0x%x. Please implement!\n",
                                               static_cast<unsigned int>(primitive.mode)));
            break;
    }
    
    return in;
}

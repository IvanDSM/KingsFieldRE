#include "tmdreader.h"
#include <QVector2D>

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
    {0.f, 256.f},        // TPage 17
    {256.f, 256.f},      // TPage 16
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

// Coefficient used to transform PS1 VRAM texcoords into normal texcoords
static constexpr QVector2D texCoordCoeff{4096.f, 512.f};

void TMDReader::readPrimitive(uint8_t primMode)
{
    auto ilen = curPrimPtr[1];

    // Here we check if primMode came with the default value. If that is the case, no manual mode
    // was specified, so we can just load the mode from the current primitive.
    bool manual = primMode != 0;
    if (!manual) primMode = curPrimMode();

    size_t colorOffset = 0;

    if (primMode < 0x20 || primMode > 0x7e)
    {
        KFMTError::error(QStringLiteral("TMDReader::readPrimitive: Invalid mode 0x%1 (ilen = %2).")
                             .arg(primMode, 2, 16)
                             .arg(ilen));
        goto advance;
    }

    if (isTextured())
        if (isQuad()) {}

    readTexcoords();
    readColors();

    switch (primMode)
    {
        case (0x20): readx20(1.0f); break;
        case (0x22): readx20(0.5f); break;
        case (0x24): readx24(1.0f); break;
        case (0x26): readx24(0.5f); break;
        case (0x25): readx25(1.0f); break;
        case (0x27): readx25(0.5f); break;
        case (0x28): readx28(1.0f); break;
        case (0x2a): readx28(0.5f); break;
        case (0x2c): readx2c(1.0f); break;
        case (0x2e): readx2c(0.5f); break;
        case (0x30): readx30(1.0f); break;
        case (0x32): readx30(0.5f); break;
        case (0x34): readx34(1.0f); break;
        case (0x36): readx34(0.5f); break;
        case (0x38): readx38(1.0f); break;
        case (0x3a): readx38(0.5f); break;
        case (0x3c): readx3c(1.0f); break;
        case (0x3e): readx3c(0.5f); break;
        default:
            KFMTError::error(
                QStringLiteral("TMDReader::readPrimitive: Unsupported mode 0x%1. Please implement!")
                    .arg(curPrimMode(), 2, 16));
            break;
    }

advance:
    if (manual)
    {
        // TODO: Handle this.
    }
    curPrimPtr += ilen * 4;
}

void TMDReader::readColors(float alpha, size_t offset)
{
    QVector4D col0{curPrimPtr[0 + offset] / 255.0f,
                   curPrimPtr[1 + offset] / 255.0f,
                   curPrimPtr[2 + offset] / 255.0f,
                   alpha};

    QVector4D col1 = isGradation() ? QVector4D(curPrimPtr[8 + offset] / 255.0f,
                                               curPrimPtr[9 + offset] / 255.0f,
                                               curPrimPtr[10 + offset] / 255.0f,
                                               alpha)
                                   : col0;

    QVector4D col2 = isGradation() ? QVector4D(curPrimPtr[12 + offset] / 255.0f,
                                               curPrimPtr[13 + offset] / 255.0f,
                                               curPrimPtr[14 + offset] / 255.0f,
                                               alpha)
                                   : col0;

    QVector4D col3 = isGradation() ? QVector4D(curPrimPtr[16 + offset] / 255.0f,
                                               curPrimPtr[17 + offset] / 255.0f,
                                               curPrimPtr[18 + offset] / 255.0f,
                                               alpha)
                                   : col0;

    curMesh->color.push_back(col2);
    curMesh->color.push_back(col1);
    curMesh->color.push_back(col0);
    if (!isQuad()) return;
    curMesh->color.push_back(col2);
    curMesh->color.push_back(col3);
    curMesh->color.push_back(col1);
}

void TMDReader::readPositionsAndNormals() {}

void TMDReader::readTexcoords()
{
    auto tPage = Utilities::as<uint16_t>(curPrimPtr, 10) & 0x1fu;

    // We might as well calculate UV3 even if this is a triangle. We just won't use it, and it avoids
    // having the extra branch caused by the if statement.
    auto uv0 = (tPageCoords[tPage] + QVector2D(curPrimPtr[4], curPrimPtr[5])) / texCoordCoeff;
    auto uv1 = (tPageCoords[tPage] + QVector2D(curPrimPtr[8], curPrimPtr[9])) / texCoordCoeff;
    auto uv2 = (tPageCoords[tPage] + QVector2D(curPrimPtr[12], curPrimPtr[13])) / texCoordCoeff;
    auto uv3 = (tPageCoords[tPage] + QVector2D(curPrimPtr[16], curPrimPtr[17])) / texCoordCoeff;

    curMesh->texCoords.push_back(uv2);
    curMesh->texCoords.push_back(uv1);
    curMesh->texCoords.push_back(uv0);
    if (!isQuad()) return;

    curMesh->texCoords.push_back(uv2);
    curMesh->texCoords.push_back(uv3);
    curMesh->texCoords.push_back(uv1);
}

void TMDReader::readx20(float alpha)
{
    curMesh->color.push_back(
        {curPrimPtr[4] / 255.0f, curPrimPtr[5] / 255.0f, curPrimPtr[6] / 255.0f, alpha});
    readGradation(alpha);
    auto normalIndex = Utilities::as<uint16_t>(curPrimPtr, 8 + isGradation() * 8);
    auto vertex0Index = Utilities::as<uint16_t>(curPrimPtr, 10 + isGradation() * 8);
    auto vertex1Index = Utilities::as<uint16_t>(curPrimPtr, 12 + isGradation() * 8);
    auto vertex2Index = Utilities::as<uint16_t>(curPrimPtr, 14 + isGradation() * 8);

    for (auto i = 0; i < 3; i++) curMesh->normals.push_back(curNormalPtr[normalIndex]);

    curMesh->frames.push_back(curVertexPtr[vertex2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex0Index]);
}

void TMDReader::readx24(float alpha)
{
    readTexcoords();
    auto normalIndex = Utilities::as<uint16_t>(curPrimPtr, 16 + isGradation() * 8);
    auto vertex0Index = Utilities::as<uint16_t>(curPrimPtr, 18 + isGradation() * 8);
    auto vertex1Index = Utilities::as<uint16_t>(curPrimPtr, 20 + isGradation() * 8);
    auto vertex2Index = Utilities::as<uint16_t>(curPrimPtr, 22 + isGradation() * 8);

    for (auto i = 0; i < 3; i++) curMesh->normals.push_back(curNormalPtr[normalIndex]);

    curMesh->frames.push_back(curVertexPtr[vertex2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex0Index]);
}

void TMDReader::readx25(float alpha) {}

void TMDReader::readx28(float alpha)
{
    curMesh->color.push_back(
        {curPrimPtr[4] / 255.0f, curPrimPtr[5] / 255.0f, curPrimPtr[6] / 255.0f, alpha});
    readGradation(alpha);
    auto normalIndex = Utilities::as<uint16_t>(curPrimPtr, 8 + isGradation() * 8);
    auto vertex0Index = Utilities::as<uint16_t>(curPrimPtr, 10 + isGradation() * 8);
    auto vertex1Index = Utilities::as<uint16_t>(curPrimPtr, 12 + isGradation() * 8);
    auto vertex2Index = Utilities::as<uint16_t>(curPrimPtr, 14 + isGradation() * 8);
    auto vertex3Index = Utilities::as<uint16_t>(curPrimPtr, 16 + isGradation() * 8);

    for (auto i = 0; i < 6; i++) curMesh->normals.push_back(curNormalPtr[normalIndex]);

    curMesh->frames.push_back(curVertexPtr[vertex2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex0Index]);

    curMesh->frames.push_back(curVertexPtr[vertex2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex3Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);
}

void TMDReader::readx2c(float alpha) {}

void TMDReader::readx30(float alpha)
{
    curMesh->color.push_back(
        {curPrimPtr[4] / 255.0f, curPrimPtr[5] / 255.0f, curPrimPtr[6] / 255.0f, alpha});
    readGradation(alpha);
    auto normal0Index = Utilities::as<uint16_t>(curPrimPtr, 8 + isGradation() * 8);
    auto vertex0Index = Utilities::as<uint16_t>(curPrimPtr, 10 + isGradation() * 8);
    auto normal1Index = Utilities::as<uint16_t>(curPrimPtr, 12 + isGradation() * 8);
    auto vertex1Index = Utilities::as<uint16_t>(curPrimPtr, 14 + isGradation() * 8);
    auto normal2Index = Utilities::as<uint16_t>(curPrimPtr, 16 + isGradation() * 8);
    auto vertex2Index = Utilities::as<uint16_t>(curPrimPtr, 18 + isGradation() * 8);

    curMesh->normals.push_back(curNormalPtr[normal2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex2Index]);

    curMesh->normals.push_back(curNormalPtr[normal1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);

    curMesh->normals.push_back(curNormalPtr[normal0Index]);
    curMesh->frames.push_back(curVertexPtr[vertex0Index]);
}

void TMDReader::readx34(float alpha) {}

void TMDReader::readx38(float alpha)
{
    curMesh->color.push_back(
        {curPrimPtr[4] / 255.0f, curPrimPtr[5] / 255.0f, curPrimPtr[6] / 255.0f, alpha});
    readGradation(alpha);
    auto normal0Index = Utilities::as<uint16_t>(curPrimPtr, 8 + isGradation() * 8);
    auto vertex0Index = Utilities::as<uint16_t>(curPrimPtr, 10 + isGradation() * 8);
    auto normal1Index = Utilities::as<uint16_t>(curPrimPtr, 12 + isGradation() * 8);
    auto vertex1Index = Utilities::as<uint16_t>(curPrimPtr, 14 + isGradation() * 8);
    auto normal2Index = Utilities::as<uint16_t>(curPrimPtr, 16 + isGradation() * 8);
    auto vertex2Index = Utilities::as<uint16_t>(curPrimPtr, 18 + isGradation() * 8);
    auto normal3Index = Utilities::as<uint16_t>(curPrimPtr, 20 + isGradation() * 8);
    auto vertex3Index = Utilities::as<uint16_t>(curPrimPtr, 22 + isGradation() * 8);

    curMesh->normals.push_back(curNormalPtr[normal2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex2Index]);

    curMesh->normals.push_back(curNormalPtr[normal1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);

    curMesh->normals.push_back(curNormalPtr[normal0Index]);
    curMesh->frames.push_back(curVertexPtr[vertex0Index]);

    curMesh->normals.push_back(curNormalPtr[normal2Index]);
    curMesh->frames.push_back(curVertexPtr[vertex2Index]);

    curMesh->normals.push_back(curNormalPtr[normal3Index]);
    curMesh->frames.push_back(curVertexPtr[vertex3Index]);

    curMesh->normals.push_back(curNormalPtr[normal1Index]);
    curMesh->frames.push_back(curVertexPtr[vertex1Index]);
}

void TMDReader::readx3c(float alpha) {}

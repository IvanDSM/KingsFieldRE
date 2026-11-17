#include "acmission.h"
#include "core/kfmterror.h"
#include <algorithm>
#include <cmath>
#include <cstring>

ACMission::ACMission(KFMTFile& streamFile) : KFMTDataHandler(streamFile)
{
    assembledModel = std::make_unique<Model>(streamFile);
    assembledModel->baseObjects.clear();

    parseChunks();
    rebuildAssembledLevel();
}

void ACMission::parseChunks()
{
    blockInfos.clear();
    chunk0Blocks.clear();
    sections.clear();

    auto* data = reinterpret_cast<uint8_t*>(file.rawData.data());
    const size_t totalSize = static_cast<size_t>(file.rawData.size());

    size_t offset = 0;
    size_t chunkIndex = 0;

    while (offset + 4 <= totalSize)
    {
        uint32_t chunkLen = 0;
        std::memcpy(&chunkLen, data + offset, sizeof(uint32_t));
        if (chunkLen == 0 || offset + 4 + chunkLen > totalSize) break;

        const size_t payloadFileOffset = offset + 4;
        uint8_t* payload = data + payloadFileOffset;

        if (chunkIndex == 0 && chunkLen >= 8)
        {
            size_t pos = 4;
            while (pos + 4 <= chunkLen)
            {
                uint32_t blockSize = 0;
                std::memcpy(&blockSize, payload + pos, sizeof(uint32_t));
                if (blockSize < 12 || pos + blockSize > chunkLen) break;

                const size_t blockFileOffset = payloadFileOffset + pos;
                QByteArray blockBytes(reinterpret_cast<const char*>(payload + pos),
                                      static_cast<int>(blockSize));

                BlockInfo info;
                info.byteOffset = blockFileOffset;
                info.byteSize = blockSize;

                // Parse sub-object descriptor table to record raw vertex pool offsets
                const auto* raw = reinterpret_cast<const uint8_t*>(blockBytes.constData());
                uint32_t a0 = 0;
                std::memcpy(&a0, raw + 8, sizeof(uint32_t));
                const uint32_t reloc = a0 + 12;
                if (reloc + 8 <= blockSize)
                {
                    uint32_t subCount = 0;
                    std::memcpy(&subCount, raw + a0 + 8, sizeof(uint32_t));
                    const uint32_t tbl = a0 + 12;

                    for (uint32_t s = 0; s < subCount; s++)
                    {
                        const size_t o = tbl + s * 28;
                        if (o + 28 > blockSize) break;

                        uint32_t vtxOff = 0;
                        uint16_t vBase = 0, vDetail = 0, flags = 0;
                        std::memcpy(&vtxOff, raw + o + 0x00, sizeof(uint32_t));
                        std::memcpy(&vBase, raw + o + 0x04, sizeof(uint16_t));
                        std::memcpy(&vDetail, raw + o + 0x06, sizeof(uint16_t));
                        std::memcpy(&flags, raw + o + 0x0E, sizeof(uint16_t));

                        SubObjectInfo sub;
                        sub.index = static_cast<int>(s);
                        sub.vtxByteOffset = blockFileOffset + reloc + vtxOff;
                        sub.vtxCount = static_cast<uint32_t>(vBase) + static_cast<uint32_t>(vDetail);
                        sub.flags = flags;
                        sub.terminated = (flags & 0x8000) != 0;
                        info.subObjects.push_back(sub);
                    }
                }

                blockInfos.push_back(std::move(info));
                chunk0Blocks.push_back(Model::parseAC1PABlock(blockBytes));
                pos += blockSize;
            }
        }
        else if (chunkIndex == 7)
        {
            sectionTablePtr = reinterpret_cast<AC1::SectionPlacement*>(payload);
            const size_t maxRecs = chunkLen / sizeof(AC1::SectionPlacement);
            for (size_t i = 0; i < maxRecs; i++)
            {
                if (sectionTablePtr[i].cellIndex == -1) break;
                sections.push_back(sectionTablePtr[i]);
            }
        }
        else if (chunkIndex == 12 && chunkLen >= sizeof(AC1::SpawnRecord))
        {
            spawns = reinterpret_cast<AC1::SpawnRecord*>(payload);
            spawnCount_ = std::min(spawnTableSize, static_cast<size_t>(chunkLen) / sizeof(AC1::SpawnRecord));
        }

        offset += 4 + chunkLen;
        chunkIndex++;
    }
}

void ACMission::reloadBlockMeshes(size_t blockIdx)
{
    if (blockIdx >= blockInfos.size() || blockIdx >= chunk0Blocks.size()) return;
    const auto& info = blockInfos.at(blockIdx);
    QByteArray blockBytes(file.rawData.constData() + info.byteOffset,
                          static_cast<int>(info.byteSize));
    chunk0Blocks.at(blockIdx) = Model::parseAC1PABlock(blockBytes);
}

std::array<int16_t, 3> ACMission::getSubObjectVertex(size_t blockIdx, size_t subIdx, uint32_t vtxIdx) const
{
    std::array<int16_t, 3> result = {0, 0, 0};
    if (blockIdx >= blockInfos.size()) return result;
    const auto& subs = blockInfos.at(blockIdx).subObjects;
    if (subIdx >= subs.size()) return result;
    const auto& sub = subs.at(subIdx);
    if (vtxIdx >= sub.vtxCount) return result;

    const size_t off = sub.vtxByteOffset + static_cast<size_t>(vtxIdx) * 8;
    if (off + 6 > static_cast<size_t>(file.rawData.size())) return result;

    std::memcpy(result.data(), file.rawData.constData() + off, 6);
    return result;
}

void ACMission::setSubObjectVertex(size_t blockIdx, size_t subIdx, uint32_t vtxIdx,
                                   int16_t x, int16_t y, int16_t z)
{
    if (blockIdx >= blockInfos.size()) return;
    const auto& subs = blockInfos.at(blockIdx).subObjects;
    if (subIdx >= subs.size()) return;
    const auto& sub = subs.at(subIdx);
    if (vtxIdx >= sub.vtxCount) return;

    const size_t off = sub.vtxByteOffset + static_cast<size_t>(vtxIdx) * 8;
    if (off + 6 > static_cast<size_t>(file.rawData.size())) return;

    std::array<int16_t, 3> xyz = {x, y, z};
    std::memcpy(file.rawData.data() + off, xyz.data(), 6);

    reloadBlockMeshes(blockIdx);
    rebuildAssembledLevel();
}

void ACMission::translateSubObject(size_t blockIdx, size_t subIdx, int dx, int dy, int dz)
{
    if (blockIdx >= blockInfos.size()) return;
    const auto& subs = blockInfos.at(blockIdx).subObjects;
    if (subIdx >= subs.size()) return;
    const auto& sub = subs.at(subIdx);

    auto clampS16 = [](int v) -> int16_t {
        return static_cast<int16_t>(std::clamp(v, -32768, 32767));
    };

    for (uint32_t v = 0; v < sub.vtxCount; v++)
    {
        const size_t off = sub.vtxByteOffset + static_cast<size_t>(v) * 8;
        if (off + 6 > static_cast<size_t>(file.rawData.size())) break;

        std::array<int16_t, 3> xyz = {0, 0, 0};
        std::memcpy(xyz.data(), file.rawData.constData() + off, 6);
        xyz.at(0) = clampS16(static_cast<int>(xyz.at(0)) + dx);
        xyz.at(1) = clampS16(static_cast<int>(xyz.at(1)) + dy);
        xyz.at(2) = clampS16(static_cast<int>(xyz.at(2)) + dz);
        std::memcpy(file.rawData.data() + off, xyz.data(), 6);
    }

    reloadBlockMeshes(blockIdx);
    rebuildAssembledLevel();
}

Model::Mesh ACMission::makeSpawnMarker(const AC1::SpawnRecord& sp, bool isSelected) const
{
    Model::Mesh m;
    m.visible = true;
    const float s = (isSelected ? 280.f : 180.f) / 4096.f;
    const float cx = static_cast<float>(sp.posX) / 4096.f;
    const float cy = static_cast<float>(sp.posY) / 4096.f;
    const float cz = static_cast<float>(sp.posZ) / 4096.f;

    m.vertices = {
        {cx, cy - s, cz},
        {cx + s, cy, cz},
        {cx, cy, cz + s},
        {cx - s, cy, cz},
        {cx, cy, cz - s},
        {cx, cy + s, cz}
    };
    m.normals = {{0.f, -1.f, 0.f}};

    const uint8_t r = isSelected ? 255 : static_cast<uint8_t>(80 + (sp.resourceId * 53) % 175);
    const uint8_t g = isSelected ? 60  : static_cast<uint8_t>(80 + (sp.resourceId * 97) % 175);
    const uint8_t b = isSelected ? 60  : static_cast<uint8_t>(80 + (sp.resourceId * 149) % 175);

    const std::array<std::array<uint16_t, 3>, 8> faces = {{
        {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
        {5, 2, 1}, {5, 3, 2}, {5, 4, 3}, {5, 1, 4}
    }};

    for (const auto& f : faces)
    {
        Model::Primitive p{};
        p.mode = Model::Primitive::PrimitiveMode::x20TriFlatNoTexOpaqueLit;
        p.flag = Model::Primitive::PrimitiveFlag::SingleColorDoubleFaceLightSourceNoCalc;
        p.r0 = r;
        p.g0 = g;
        p.b0 = b;
        p.vertex0 = f.at(0);
        p.vertex1 = f.at(1);
        p.vertex2 = f.at(2);
        p.normal0 = 0;
        m.primitives.push_back(p);
    }

    return m;
}

void ACMission::rebuildAssembledLevel()
{
    if (!assembledModel) return;
    assembledModel->baseObjects.clear();

    constexpr float kBlockScale = 0.25f;
    constexpr float kHorizThreshold = 0.7f;
    constexpr float kTwoPi = 6.28318530718f;

    for (size_t i = 0; i < sections.size(); i++)
    {
        if (sectionTablePtr != nullptr) sectionTablePtr[i] = sections.at(i);

        const auto& sec = sections.at(i);
        if (sec.blockIndex < 0 || static_cast<size_t>(sec.blockIndex) >= chunk0Blocks.size())
            continue;

        const bool isSectionSel = (static_cast<int>(i) == selectedSection);
        const bool isBlockSel   = (selectedBlock >= 0 && sec.blockIndex == selectedBlock);

        const float tx = static_cast<float>(sec.translation.at(0)) / 4096.f;
        const float ty = static_cast<float>(sec.translation.at(1)) / 4096.f;
        const float tz = static_cast<float>(sec.translation.at(2)) / 4096.f;

        const float angle = static_cast<float>(sec.rotY) * (kTwoPi / 4096.f);
        const float cosR = std::cos(angle);
        const float sinR = std::sin(angle);

        for (const auto& srcMesh : chunk0Blocks.at(sec.blockIndex))
        {
            Model::Mesh placedMesh;
            placedMesh.vertices.reserve(srcMesh.vertices.size());
            for (const auto& v : srcMesh.vertices)
            {
                const float lx = v.x * kBlockScale;
                const float ly = v.y * kBlockScale;
                const float lz = v.z * kBlockScale;

                const float rx = (lx * cosR) - (lz * sinR);
                const float rz = (lx * sinR) + (lz * cosR);

                placedMesh.vertices.push_back({rx + tx, ly + ty, rz + tz});
            }
            placedMesh.normals = srcMesh.normals;

            for (const auto& srcPrim : srcMesh.primitives)
            {
                const auto& a = placedMesh.vertices.at(srcPrim.vertex0);
                const auto& b = placedMesh.vertices.at(srcPrim.vertex1);
                const auto& c = placedMesh.vertices.at(srcPrim.vertex2);

                const float ux = b.x - a.x, uy = b.y - a.y, uz = b.z - a.z;
                const float vx = c.x - a.x, vy = c.y - a.y, vz = c.z - a.z;
                const float nx = uy * vz - uz * vy;
                const float ny = uz * vx - ux * vz;
                const float nz = ux * vy - uy * vx;
                const float len = std::sqrt(nx * nx + ny * ny + nz * nz);
                const float normY = (len > 1e-7f) ? (ny / len) : 0.f;

                const bool isCeiling = (normY < -kHorizThreshold);
                const bool isFloor   = (normY >  kHorizThreshold);

                if (isCeiling && !showCeilings)
                    continue;

                Model::Primitive prim = srcPrim;
                if (isBlockSel)
                {
                    prim.r0 = 80;  prim.g0 = 230; prim.b0 = 255; // Cyan highlight for edited block
                }
                else if (isSectionSel)
                {
                    prim.r0 = 255; prim.g0 = 220; prim.b0 = 80;  // Gold highlight for selected section
                }
                else if (isFloor)
                {
                    prim.r0 = 104; prim.g0 = 144; prim.b0 = 110;
                }
                else if (isCeiling)
                {
                    prim.r0 = 88;  prim.g0 = 84;  prim.b0 = 120;
                }
                else
                {
                    prim.r0 = 150; prim.g0 = 152; prim.b0 = 168;
                }

                placedMesh.primitives.push_back(prim);
            }

            if (!placedMesh.primitives.empty())
                assembledModel->baseObjects.push_back(std::move(placedMesh));
        }
    }
}

std::pair<QVector3D, QVector3D> ACMission::getSectionWorldBounds(size_t index) const
{
    const auto& sec = sections.at(index);
    constexpr float kBlockScale = 0.25f;
    constexpr float kTwoPi = 6.28318530718f;

    const float tx = static_cast<float>(sec.translation.at(0));
    const float ty = static_cast<float>(sec.translation.at(1));
    const float tz = static_cast<float>(sec.translation.at(2));

    if (sec.blockIndex >= 0 && static_cast<size_t>(sec.blockIndex) < chunk0Blocks.size())
    {
        const float angle = static_cast<float>(sec.rotY) * (kTwoPi / 4096.f);
        const float cosR = std::cos(angle);
        const float sinR = std::sin(angle);

        bool hasVerts = false;
        QVector3D bMin(1e9f, 1e9f, 1e9f);
        QVector3D bMax(-1e9f, -1e9f, -1e9f);

        for (const auto& mesh : chunk0Blocks.at(sec.blockIndex))
        {
            for (const auto& v : mesh.vertices)
            {
                const float lx = v.x * 4096.f * kBlockScale;
                const float ly = v.y * 4096.f * kBlockScale;
                const float lz = v.z * 4096.f * kBlockScale;

                const float wx = (lx * cosR) - (lz * sinR) + tx;
                const float wy = ly + ty;
                const float wz = (lx * sinR) + (lz * cosR) + tz;

                bMin.setX(std::min(bMin.x(), wx));
                bMin.setY(std::min(bMin.y(), wy));
                bMin.setZ(std::min(bMin.z(), wz));

                bMax.setX(std::max(bMax.x(), wx));
                bMax.setY(std::max(bMax.y(), wy));
                bMax.setZ(std::max(bMax.z(), wz));
                hasVerts = true;
            }
        }

        if (hasVerts)
            return {bMin, bMax};
    }

    return {QVector3D(sec.bboxMin.at(0), sec.bboxMin.at(1), sec.bboxMin.at(2)),
            QVector3D(sec.bboxMax.at(0), sec.bboxMax.at(1), sec.bboxMax.at(2))};
}

int16_t ACMission::snapSectionAxisToNeighbors(size_t secIdx, int axis, int16_t candidateTrans, int snapThreshold) const
{
    if (secIdx >= sections.size() || axis < 0 || axis > 2)
        return candidateTrans;

    const auto& activeSec = sections.at(secIdx);
    const auto [curMin, curMax] = getSectionWorldBounds(secIdx);

    const float localMin = curMin[axis] - static_cast<float>(activeSec.translation.at(axis));
    const float localMax = curMax[axis] - static_cast<float>(activeSec.translation.at(axis));

    const int otherA = (axis + 1) % 3;
    const int otherB = (axis + 2) % 3;
    constexpr float kNeighborMargin = 256.f;

    float bestTrans = static_cast<float>(candidateTrans);
    float bestDist = static_cast<float>(snapThreshold);

    for (size_t j = 0; j < sections.size(); ++j)
    {
        if (j == secIdx) continue;

        const auto [nMin, nMax] = getSectionWorldBounds(j);

        if (curMax[otherA] + kNeighborMargin < nMin[otherA] || curMin[otherA] - kNeighborMargin > nMax[otherA])
            continue;
        if (curMax[otherB] + kNeighborMargin < nMin[otherB] || curMin[otherB] - kNeighborMargin > nMax[otherB])
            continue;

        const std::array<float, 4> targets = {
            nMin[axis] - localMax,
            nMax[axis] - localMin,
            nMin[axis] - localMin,
            nMax[axis] - localMax
        };

        for (float t : targets)
        {
            const float d = std::abs(t - static_cast<float>(candidateTrans));
            if (d < bestDist)
            {
                bestDist = d;
                bestTrans = t;
            }
        }
    }

    return static_cast<int16_t>(std::clamp(static_cast<int>(std::round(bestTrans)), -32768, 32767));
}
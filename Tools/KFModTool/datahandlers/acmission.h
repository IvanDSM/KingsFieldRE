#ifndef ACMISSION_H
#define ACMISSION_H

#include "ac1/mission.h"
#include "datahandlers/kfmtdatahandler.h"
#include "datahandlers/model.h"
#include <QVector3D>
#include <array>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

class ACMission : public KFMTDataHandler
{
public:
    struct SubObjectInfo
    {
        int index = 0;
        size_t vtxByteOffset = 0; // Offset into file.rawData
        uint32_t vtxCount = 0;
        uint16_t flags = 0;
        bool terminated = false;
    };

    struct BlockInfo
    {
        size_t byteOffset = 0; // Offset into file.rawData
        uint32_t byteSize = 0;
        std::vector<SubObjectInfo> subObjects;
    };

    explicit ACMission(KFMTFile& streamFile);

    void saveChanges() override {}
    void rebuildAssembledLevel();

    void setShowCeilings(bool show) { showCeilings = show; rebuildAssembledLevel(); }
    bool getShowCeilings() const { return showCeilings; }

    void setSelectedSection(int index) { selectedSection = index; rebuildAssembledLevel(); }
    void setSelectedSpawn(int index) { selectedSpawn = index; rebuildAssembledLevel(); }
    void setSelectedBlock(int blockIdx) { selectedBlock = blockIdx; rebuildAssembledLevel(); }

    size_t sectionCount() const { return sections.size(); }
    AC1::SectionPlacement& getSection(size_t index) { return sections.at(index); }
    std::pair<QVector3D, QVector3D> getSectionWorldBounds(size_t index) const;
    int16_t snapSectionAxisToNeighbors(size_t secIdx, int axis, int16_t candidateTrans, int snapThreshold = 512) const;

    static constexpr size_t spawnTableSize = 256;
    size_t spawnCount() const { return spawnCount_; }
    AC1::SpawnRecord& getSpawn(size_t index) { return spawns[index]; }

    // Chunk 0 Block & Sub-Object accessors
    size_t blockCount() const { return blockInfos.size(); }
    const BlockInfo& getBlockInfo(size_t blockIdx) const { return blockInfos.at(blockIdx); }

    std::array<int16_t, 3> getSubObjectVertex(size_t blockIdx, size_t subIdx, uint32_t vtxIdx) const;
    void setSubObjectVertex(size_t blockIdx, size_t subIdx, uint32_t vtxIdx, int16_t x, int16_t y, int16_t z);
    void translateSubObject(size_t blockIdx, size_t subIdx, int dx, int dy, int dz);

    Model& getAssembledModel() { return *assembledModel; }

private:
    void parseChunks();
    void reloadBlockMeshes(size_t blockIdx);
    Model::Mesh makeSpawnMarker(const AC1::SpawnRecord& sp, bool isSelected) const;

    std::vector<BlockInfo> blockInfos;
    std::vector<std::vector<Model::Mesh>> chunk0Blocks;
    AC1::SectionPlacement* sectionTablePtr = nullptr;
    std::vector<AC1::SectionPlacement> sections;
    AC1::SpawnRecord* spawns = nullptr;
    size_t spawnCount_ = 0;

    bool showCeilings = false;
    int selectedSection = 0;
    int selectedSpawn = -1;
    int selectedBlock = -1;

    std::unique_ptr<Model> assembledModel;
};

#endif // ACMISSION_H

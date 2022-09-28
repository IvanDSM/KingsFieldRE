#ifndef MAP_H
#define MAP_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include "kf2/entity.h"
#include "kf2/object.h"
#include "kf2/tile.h"
#include "kf2/vfx.h"
#include <QMessageBox>

class Map : public KFMTDataHandler
{
public:
    Map(KFMTFile& file1, KFMTFile& file2, KFMTFile& file3);

    KF2::EntityClass& getEntityClassDeclaration(uint8_t classIndex)
    {
        if (classIndex >= entityClassesSize)
            KFMTError::outOfRange(classIndex, QStringLiteral("entity class declaration"));
        return entityClasses[classIndex];
    }

    KF2::EntityInstance &getEntityInstance(size_t instanceIndex)
    {
        if (instanceIndex >= entityInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("entity instance declaration"));
        return entityInstances[instanceIndex];
    }

    KF2::ObjectInstance& getObjectInstance(size_t instanceIndex)
    {
        if (instanceIndex >= objectInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("object instance declaration"));

        return objectInstances[instanceIndex];
    }

    uint8_t* getEntityStateBlobOffset(size_t offset) { return entityStateBlob + offset; }

    KF2::Tile& getTile(size_t line, size_t column, size_t layer)
    {
        if (line >= 80u || column >= 80u)
            KFMTError::fatalError(
                QStringLiteral("Tried accessing out-of-bounds tile at position (%1,%2).\n")
                    .arg(line)
                    .arg(column));

        switch (layer)
        {
            case 1: return tileMap[(line * 80u) + column].layer1;
            case 2: return tileMap[(line * 80u) + column].layer2;
            default:
                KFMTError::fatalError(
                    QStringLiteral("Tried to access inexistent layer %1").arg(layer));
        }
    }

    KF2::VFX& getVFXInstance(size_t instanceIndex)
    {
        if (instanceIndex >= vfxInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("VFX instance declaration"));

        return vfxInstances[instanceIndex];
    }

    void saveChanges() override {}

    // Convenience methods
    std::vector<KF2::EntityInstance*> entitiesAt(uint8_t x, uint8_t y, uint8_t layer);
    std::vector<KF2::ObjectInstance*> objectsAt(uint8_t x, uint8_t y, uint8_t layer);
    std::vector<KF2::VFX*> vfxsAt(uint8_t x, uint8_t y, uint8_t layer);

    static constexpr size_t entityClassesSize = 40;
    static constexpr size_t entityInstancesSize = 200;
    static constexpr size_t objectInstancesSize = 350;
    static constexpr size_t vfxInstancesSize = 128;

private:
    KF2::MetaTile* tileMap; ///< 2-layer 80x80 tilemap.
    KFMTFile& mapDB;
    KFMTFile& mapScript;
    KF2::EntityClass* entityClasses;
    KF2::EntityInstance* entityInstances;
    uint8_t* entityStateBlob;
    KF2::ObjectInstance* objectInstances;
    KF2::VFX* vfxInstances;

    // MapViewer needs access to the arrays
    friend class MapViewer;
};

#endif // MAP_H

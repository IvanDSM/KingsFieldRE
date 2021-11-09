#ifndef MAP_H
#define MAP_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include "games/kf2.h"
#include <QMessageBox>

class Map : public KFMTDataHandler
{
public:
    Map(KFMTFile& file1, KFMTFile& file2, KFMTFile& file3);

    KingsFieldII::EntityClass& getEntityClassDeclaration(byte classIndex)
    {
        if (classIndex >= entityClassesSize)
            KFMTError::outOfRange(classIndex, QStringLiteral("entity class declaration"));
        return entityClasses[classIndex];
    }

    KingsFieldII::EntityInstance &getEntityInstance(size_t instanceIndex)
    {
        if (instanceIndex >= entityInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("entity instance declaration"));
        return entityInstances[instanceIndex];
    }

    KingsFieldII::ObjectInstance& getObjectInstance(size_t instanceIndex)
    {
        if (instanceIndex >= objectInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("object instance declaration"));

        return objectInstances[instanceIndex];
    }

    uint8_t* getEntityStateBlobOffset(size_t offset) { return entityStateBlob + offset; }

    KingsFieldII::Tile& getTile(size_t line, size_t column, size_t layer)
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

    KingsFieldII::VFX& getVFXInstance(size_t instanceIndex)
    {
        if (instanceIndex >= vfxInstancesSize)
            KFMTError::outOfRange(instanceIndex, QStringLiteral("VFX instance declaration"));

        return vfxInstances[instanceIndex];
    }

    void saveChanges() override {}

    // Convenience methods
    std::vector<KingsFieldII::EntityInstance*> entitiesAt(byte x, byte y, byte layer);
    std::vector<KingsFieldII::ObjectInstance*> objectsAt(byte x, byte y, byte layer);
    std::vector<KingsFieldII::VFX*> vfxsAt(byte x, byte y, byte layer);

    static constexpr size_t entityClassesSize = 40;
    static constexpr size_t entityInstancesSize = 200;
    static constexpr size_t objectInstancesSize = 350;
    static constexpr size_t vfxInstancesSize = 128;

private:
    KingsFieldII::MetaTile* tileMap; ///< 2-layer 80x80 tilemap.
    KFMTFile& mapDB;
    KFMTFile& mapScript;
    KingsFieldII::EntityClass* entityClasses;
    KingsFieldII::EntityInstance* entityInstances;
    uint8_t* entityStateBlob;
    KingsFieldII::ObjectInstance* objectInstances;
    KingsFieldII::VFX* vfxInstances;

    // MapViewer needs access to the arrays
    friend class MapViewer;
};

#endif // MAP_H

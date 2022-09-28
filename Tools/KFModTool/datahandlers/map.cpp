#include "map.h"
#include "utilities.h"
#include <QDataStream>

Map::Map(KFMTFile& file1, KFMTFile& file2, KFMTFile& file3)
    : KFMTDataHandler(file1), mapDB(file2), mapScript(file3)
{
    tileMap = &Utilities::as<KF2::MetaTile>(file.rawData, 4);

    QDataStream mapDBStream(mapDB.rawData);
    mapDBStream.setByteOrder(QDataStream::LittleEndian);
    uint32_t sectionSize;

    mapDBStream >> sectionSize; // Read entity class declaration + state info section size
    entityClasses = &Utilities::as<KF2::EntityClass>(mapDB.rawData,
                                                              mapDBStream.device()->pos());
    mapDBStream.skipRawData(sectionSize);

    entityStateBlob = reinterpret_cast<uint8_t*>(entityClasses + entityClassesSize);

    mapDBStream >> sectionSize; // Read entity instance declaration section size
    entityInstances = &Utilities::as<KF2::EntityInstance>(mapDB.rawData,
                                                                   mapDBStream.device()->pos());
    mapDBStream.skipRawData(sectionSize);

    mapDBStream >> sectionSize; // Read object instance declaration section size
    objectInstances = &Utilities::as<KF2::ObjectInstance>(mapDB.rawData,
                                                                   mapDBStream.device()->pos());
    mapDBStream.skipRawData(sectionSize);

    mapDBStream >> sectionSize; // Read VFX instance declaration section size
    vfxInstances = &Utilities::as<KF2::VFX>(mapDB.rawData, mapDBStream.device()->pos());
    mapDBStream.skipRawData(sectionSize);
}

std::vector<KF2::EntityInstance*> Map::entitiesAt(uint8_t x, uint8_t y, uint8_t layer)
{
    std::vector<KF2::EntityInstance*> entities;

    for (size_t i = 0; i < Map::entityInstancesSize; i++)
    {
        auto& entity = entityInstances[i];

        if (x == entity.WEXTilePos && y == entity.NSYTilePos && entity.Layer == layer)
            entities.push_back(&entity);
    }

    return entities;
}

std::vector<KF2::ObjectInstance*> Map::objectsAt(uint8_t x, uint8_t y, uint8_t layer)
{
    std::vector<KF2::ObjectInstance*> objects;

    for (size_t i = 0; i < Map::objectInstancesSize; i++)
    {
        auto& object = objectInstances[i];

        if (x == object.WEXTilePos && y == object.NSYTilePos && object.TileLayer == layer)
            objects.push_back(&object);
    }

    return objects;
}

std::vector<KF2::VFX*> Map::vfxsAt(uint8_t x, uint8_t y, uint8_t layer)
{
    std::vector<KF2::VFX*> vfxs;

    for (size_t i = 0; i < Map::vfxInstancesSize; i++)
    {
        auto& vfx = vfxInstances[i];

        if (x == vfx.TileWEX && y == vfx.TileNSY && vfx.TileLayer == layer) vfxs.push_back(&vfx);
    }

    return vfxs;
}

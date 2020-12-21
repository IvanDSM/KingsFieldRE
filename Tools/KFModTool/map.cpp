#include "map.h"
#include <QDataStream>

Map::Map(QByteArray & file1, QByteArray & file2, QByteArray & file3):
    map1(file1),
    map2(file2),
    map3(file3)
{
    QDataStream map1Stream(map1);
    map1Stream.skipRawData(4);
    for (auto line = 0; line < 80; line++)
    {
        for (auto column = 0; column < 80; column++)
        {
            map1Stream >> tileMap[line][column];
        }
    }

    QDataStream map2Stream(map2);
    map2Stream.setByteOrder(QDataStream::LittleEndian);

    uint32_t entityClassSectionSize;
    map2Stream >> entityClassSectionSize; // Read entity class declaration + state info section size
    for (auto &declaration : entityClassDeclarations)
        map2Stream >> declaration;
    
    const uint32_t entityStateBlobSize = entityClassSectionSize + 4 - map2Stream.device()->pos();
    entityStateBlob.resize(entityStateBlobSize);
    map2Stream.readRawData(entityStateBlob.data(), entityStateBlobSize);
    
    map2Stream.skipRawData(4); // Skip entity instance declaration section size
    for (auto &instance : entityInstances)
        map2Stream >> instance;

    map2Stream.skipRawData(4); // Skip object instance declaration section size
    for (auto &objectInstance : objInstances)
        map2Stream >> objectInstance;

    map2Stream.skipRawData(4); // Skip VFX instance declaration section size
    for (auto &vfx : vfxInstances)
        map2Stream >> vfx;
}

void Map::writeChanges()
{
    QDataStream map1Stream(&map1, QIODevice::ReadWrite);
    map1Stream.setByteOrder(QDataStream::LittleEndian);

    map1Stream.skipRawData(4);
    for (auto line = 0; line < 80; line++)
    {
        for (auto column = 0; column < 80; column++)
            map1Stream << tileMap[line][column];
    }

    QDataStream map2Stream(&map2, QIODevice::ReadWrite);
    map2Stream.setByteOrder(QDataStream::LittleEndian);

    map2Stream.skipRawData(4); // Skip entity class declaration + state info section size
    for (const auto &entityCD : entityClassDeclarations)
        map2Stream << entityCD;

    map2Stream.writeRawData(entityStateBlob.data(), entityStateBlob.size());
    
    map2Stream.skipRawData(4); // Skip entity instance declaration section size
    for (const auto &entityInstance : entityInstances)
        map2Stream << entityInstance;

    map2Stream.skipRawData(4); // Skip object instance declaration section size
    for (const auto &objInstance : objInstances)
        map2Stream << objInstance;

    map2Stream.skipRawData(4); // Skip VFX instance declaration section size
    for (const auto &vfx : vfxInstances)
        map2Stream << vfx;

    Checksum::calculateAndWriteChecksum(map1);
    Checksum::calculateAndWriteChecksum(map2);
    Checksum::calculateAndWriteChecksum(map3);
}

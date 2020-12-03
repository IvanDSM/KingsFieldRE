#include "map.h"
#include <QDataStream>

Map::Map(TFile &tFile_, unsigned int index): tFile(tFile_),  fileIndex(index),
    map1(tFile_.getFile(index)),
    map2(tFile_.getFile(index + 1)),
    map3(tFile_.getFile(index + 2))
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

    map2Stream.skipRawData(4); // Skip entity class declaration + state info section size
    for (auto &declaration : entityClassDeclarations)
        map2Stream >> declaration;

    KFMTError::log("Map: entity state info at 0x" + QString::number(map2Stream.device()->pos(), 16));
    
    map2Stream.device()->seek(0x32C8); // Skip state info section and entity instance declaration section size
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

    map2Stream.device()->seek(0x32C8); // Skip state info section and entity instance declaration section size
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

    tFile.writeFile(map1, static_cast<int>(fileIndex));
    tFile.writeFile(map2, static_cast<int>(fileIndex) + 1);
    tFile.writeFile(map3, static_cast<int>(fileIndex) + 2);
}

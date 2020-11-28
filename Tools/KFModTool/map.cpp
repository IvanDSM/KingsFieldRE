#include "map.h"
#include <QDataStream>

Map::Map(TFile &fdatTFile, unsigned int index, const QString &name): fdat(fdatTFile),  mapIndex(index),
    map1(fdat.getFile(index * 3)),
    map2(fdat.getFile(index * 3 + 1)),
    map3(fdat.getFile(index * 3 + 2)),
    mapName(name)
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
    for (auto entityCD = 0; entityCD < 40; entityCD++)
    {
        KingsField::EntityClassDeclaration declaration{};
        map2Stream >> declaration;
        entityClassDeclarations.at(entityCD) = declaration;
    }

    map2Stream.device()->seek(0x32C8); // Skip state info section and entity instance declaration section size
    for(auto entityInstance = 0; entityInstance < 200; entityInstance++)
    {
        KingsField::EntityInstance instance{};
        map2Stream >> instance;
        entityInstances.at(entityInstance) = instance;
    }

    map2Stream.skipRawData(4); // Skip object instance declaration section size
    for (auto objectInstance = 0; objectInstance < 350; objectInstance++)
    {
        KingsField::ObjectInstanceDeclaration objInstance{};
        map2Stream >> objInstance;
        objInstances.at(objectInstance) = objInstance;
    }

    map2Stream.skipRawData(4); // Skip VFX instance declaration section size
    for (KingsField::VFXInstanceDeclaration &vfx : vfxInstances)
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
    for (auto entityCD : entityClassDeclarations)
        map2Stream << entityCD;

    map2Stream.device()->seek(0x32C8); // Skip state info section and entity instance declaration section size
    for (auto entityInstance : entityInstances)
        map2Stream << entityInstance;

    map2Stream.skipRawData(4); // Skip object instance declaration section size
    for (auto objInstance : objInstances)
        map2Stream << objInstance;

    map2Stream.skipRawData(4); // Skip VFX instance declaration section size
    for (auto vfx : vfxInstances)
        map2Stream << vfx;

    Checksum::calculateAndWriteChecksum(map1);
    Checksum::calculateAndWriteChecksum(map2);
    Checksum::calculateAndWriteChecksum(map3);

    fdat.writeFile(map1, static_cast<int>(mapIndex * 3));
    fdat.writeFile(map2, static_cast<int>(mapIndex * 3) + 1);
    fdat.writeFile(map3, static_cast<int>(mapIndex * 3) + 2);
}

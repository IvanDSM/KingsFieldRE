#include "map.h"
#include <QDataStream>

Map::Map(TFile &fdatTFile, unsigned int index, QString name): fdat(fdatTFile),  mapIndex(index),
    map1(fdat.getFile(index * 3)),
    map2(fdat.getFile(index * 3 + 1)),
    map3(fdat.getFile(index * 3 + 2)),
    mapName(std::move(name))
{
    QDataStream map1Stream(map1);
    map1Stream.skipRawData(4);
    for (auto line = 0; line < 80; line++)
    {
        for (auto column = 0; column < 80; column++)
        {
            map1Stream >> tileMap[line][column].Layer1TileID;
            map1Stream >> tileMap[line][column].Layer1Elev;
            map1Stream >> tileMap[line][column].Layer1Rotation;
            map1Stream >> tileMap[line][column].Layer1CollisionSomething;
            map1Stream >> tileMap[line][column].Layer1ZoneDelimiter;
            map1Stream >> tileMap[line][column].Layer2TileID;
            map1Stream >> tileMap[line][column].Layer2Elev;
            map1Stream >> tileMap[line][column].Layer2Rotation;
            map1Stream >> tileMap[line][column].Layer2CollisionSomething;
            map1Stream >> tileMap[line][column].Layer2ZoneDelimiter;
        }
    }

    QDataStream map2Stream(map2);
    map2Stream.setByteOrder(QDataStream::LittleEndian);
    map2Stream.skipRawData(4);
    for (auto entityCD = 0; entityCD < 40; entityCD++)
    {
        KingsField::EntityClassDeclaration declaration{};
        map2Stream >> declaration;
        entityClassDeclarations.push_back(declaration);
    }

    map2Stream.device()->seek(0x32C8);
    for(auto entityInstance = 0; entityInstance < 200; entityInstance++)
    {
        KingsField::EntityInstance instance{};
        map2Stream >> instance;
        entityInstances.push_back(instance);
    }
    map2Stream.skipRawData(4);
    for (auto objectInstance = 0; objectInstance < 350; objectInstance++)
    {
        KingsField::ObjectInstanceDeclaration objInstance{};
        quint16 tempUShort;

        map2Stream >> objInstance.TileLayer;
        map2Stream >> objInstance.WEXTilePos;
        map2Stream >> objInstance.NSYTilePos;
        map2Stream >> objInstance.field_0x3;
        map2Stream >> tempUShort;
        objInstance.ObjectID = KingsField::getObjectIDFromUShort(tempUShort);
        map2Stream >> objInstance.ZRotation;
        map2Stream >> objInstance.FineWEXPos;
        map2Stream >> objInstance.FineNSYPos;
        map2Stream >> objInstance.FineZPos;
        for (unsigned char &Flag : objInstance.Flags)
            map2Stream >> Flag;

        objInstances.push_back(objInstance);
    }
}

void Map::writeChanges()
{
    QDataStream map1Stream(&map1, QIODevice::ReadWrite);
    map1Stream.setByteOrder(QDataStream::LittleEndian);

    map1Stream.skipRawData(4);
    for (auto line = 0; line < 80; line++)
    {
        for (auto column = 0; column < 80; column++)
        {
            map1Stream << tileMap[line][column].Layer1TileID;
            map1Stream << tileMap[line][column].Layer1Elev;
            map1Stream << tileMap[line][column].Layer1Rotation;
            map1Stream << tileMap[line][column].Layer1CollisionSomething;
            map1Stream << tileMap[line][column].Layer1ZoneDelimiter;
            map1Stream << tileMap[line][column].Layer2TileID;
            map1Stream << tileMap[line][column].Layer2Elev;
            map1Stream << tileMap[line][column].Layer2Rotation;
            map1Stream << tileMap[line][column].Layer2CollisionSomething;
            map1Stream << tileMap[line][column].Layer2ZoneDelimiter;
        }
    }

    QDataStream map2Stream(&map2, QIODevice::ReadWrite);

    map2Stream.setByteOrder(QDataStream::LittleEndian);
    map2Stream.skipRawData(4);

    for (auto entityCD : entityClassDeclarations)
    {
        QByteArray classDeclArray = entityCD;
        map2Stream.writeRawData(classDeclArray, classDeclArray.size());
    }

    map2Stream.device()->seek(0x32C8);

    for (auto entityInstance : entityInstances)
    {
        QByteArray instanceArray = entityInstance;
        map2Stream.writeRawData(instanceArray, instanceArray.size());
    }

    map2Stream.skipRawData(4);

    for (auto objInstance : objInstances)
    {
        QByteArray objInstanceArray = objInstance;
        map2Stream.writeRawData(objInstanceArray, objInstanceArray.size());
    }

    Checksum::calculateAndWriteChecksum(map1);
    Checksum::calculateAndWriteChecksum(map2);
    Checksum::calculateAndWriteChecksum(map3);

    fdat.writeFile(map1, static_cast<int>(mapIndex * 3));
    fdat.writeFile(map2, static_cast<int>(mapIndex * 3) + 1);
    fdat.writeFile(map3, static_cast<int>(mapIndex * 3) + 2);
}

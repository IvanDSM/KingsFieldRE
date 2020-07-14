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
        KingsField::EntityClassDeclaration declaration;
        quint8 tempByte;
        map2Stream >> tempByte;
        declaration.MeshID = KingsField::getEntityMeshIDFromByte(tempByte);
        map2Stream >> declaration.FourOrForty;
        map2Stream >> declaration.field_0x2;
        map2Stream >> declaration.field_0x3;
        map2Stream >> declaration.field_0x4;
        map2Stream >> declaration.field_0x5;
        map2Stream >> declaration.field_0x6;
        map2Stream >> declaration.field_0x7;
        map2Stream >> declaration.field_0x8;
        map2Stream >> declaration.field_0x9;
        map2Stream >> declaration.field_0xa;
        map2Stream >> declaration.field_0xb;
        map2Stream >> declaration.field_0xc;
        map2Stream >> declaration.field_0xd;
        map2Stream >> declaration.field_0xe;
        map2Stream >> declaration.field_0xf;
        map2Stream >> declaration.field_0x10;
        map2Stream >> declaration.field_0x11;
        map2Stream >> declaration.field_0x12;
        map2Stream >> declaration.field_0x13;
        map2Stream >> declaration.field_0x14;
        map2Stream >> declaration.field_0x15;
        map2Stream >> declaration.field_0x16;
        map2Stream >> declaration.field_0x17;
        map2Stream >> declaration.field_0x18;
        map2Stream >> declaration.field_0x19;
        map2Stream >> declaration.HP;
        map2Stream >> declaration.field_0x1c;
        map2Stream >> declaration.field_0x1d;
        map2Stream >> declaration.ExperienceGain;
        map2Stream >> declaration.DefSlash;
        map2Stream >> declaration.DefChop;
        map2Stream >> declaration.DefStab;
        map2Stream >> declaration.DefHolyMagic;
        map2Stream >> declaration.DefFireMagic;
        map2Stream >> declaration.DefEarthMagic;
        map2Stream >> declaration.DefWindMagic;
        map2Stream >> declaration.DefWaterMagic;
        map2Stream >> declaration.field_0x30;
        map2Stream >> declaration.field_0x31;
        map2Stream >> declaration.Scale;
        map2Stream >> declaration.field_0x34;
        map2Stream >> declaration.field_0x35;
        map2Stream >> declaration.field_0x36;
        map2Stream >> declaration.field_0x37;
        map2Stream >> declaration.SomePointers[0];
        map2Stream >> declaration.SomePointers[1];
        map2Stream >> declaration.SomePointers[2];
        map2Stream >> declaration.SomePointers[3];
        map2Stream >> declaration.SomePointers[4];
        map2Stream >> declaration.SomePointers[5];
        map2Stream >> declaration.SomePointers[6];
        map2Stream >> declaration.SomePointers[7];
        map2Stream >> declaration.SomePointers[8];
        map2Stream >> declaration.SomePointers[9];
        map2Stream >> declaration.SomePointers[10];
        map2Stream >> declaration.SomePointers[11];
        map2Stream >> declaration.SomePointers[12];
        map2Stream >> declaration.SomePointers[13];
        map2Stream >> declaration.SomePointers[14];
        map2Stream >> declaration.SomePointers[15];
        entityClassDeclarations.push_back(declaration);
    }

    map2Stream.device()->seek(0x32C8);
    for(auto entityInstance = 0; entityInstance < 200; entityInstance++)
    {
        KingsField::EntityInstance instance;
        quint8 tempByte;
        map2Stream >> instance.Enabled;
        map2Stream >> instance.EntityClass;
        map2Stream >> instance.field_0x2;
        map2Stream >> instance.WEXTilePos;

        map2Stream >> instance.NSYTilePos;
        map2Stream >> instance.field_0x5;
        map2Stream >> tempByte;
        instance.DroppedItem = KingsField::getItemIDFromByte(tempByte);
        map2Stream >> instance.Layer;

        map2Stream >> instance.field_0x8;
        map2Stream >> instance.field_0x9;
        map2Stream >> instance.field_0xa;
        map2Stream >> instance.field_0xb;

        map2Stream >> instance.field_0xc;
        map2Stream >> instance.field_0xd;
        map2Stream >> instance.field_0xe;
        map2Stream >> instance.field_0xf;
        entityInstances.push_back(instance);
    }
    map2Stream.skipRawData(4);
    for (auto objectInstance = 0; objectInstance < 350; objectInstance++)
    {
        KingsField::ObjectInstanceDeclaration objInstance;
        quint8 tempByte;

        map2Stream >> objInstance.TileLayer;
        map2Stream >> objInstance.WEXTilePos;
        map2Stream >> objInstance.NSYTilePos;
        map2Stream >> objInstance.field_0x3;
        map2Stream >> tempByte;
        objInstance.ItemID = KingsField::getItemIDFromByte(tempByte);
        map2Stream >> objInstance.field_0x5;
        map2Stream >> objInstance.field_0x6;
        map2Stream >> objInstance.field_0x7;
        map2Stream >> objInstance.field_0x8;
        map2Stream >> objInstance.field_0x9;
        map2Stream >> objInstance.field_0xa;
        map2Stream >> objInstance.field_0xb;
        map2Stream >> objInstance.field_0xc;
        map2Stream >> objInstance.field_0xd;
        map2Stream >> objInstance.field_0xe;
        map2Stream >> objInstance.field_0xf;
        map2Stream >> tempByte;
        objInstance.KeyID = KingsField::getItemIDFromByte(tempByte);
        map2Stream >> objInstance.field_0x11;
        map2Stream >> objInstance.InstanceContained;
        map2Stream >> objInstance.field_0x13;
        map2Stream >> objInstance.field_0x14;
        map2Stream >> objInstance.field_0x15;
        map2Stream >> objInstance.field_0x16;
        map2Stream >> objInstance.field_0x17;

        objInstances.push_back(objInstance);
    }
}

void Map::writeChanges()
{
    if (!changed)
        return;

    QDataStream map1Stream(&map1, QIODevice::ReadWrite);

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
        map2Stream << KingsField::getEntityMeshIDAsByte(entityCD.MeshID);
        map2Stream << entityCD.FourOrForty;
        map2Stream << entityCD.field_0x2;
        map2Stream << entityCD.field_0x3;
        map2Stream << entityCD.field_0x4;
        map2Stream << entityCD.field_0x5;
        map2Stream << entityCD.field_0x6;
        map2Stream << entityCD.field_0x7;
        map2Stream << entityCD.field_0x8;
        map2Stream << entityCD.field_0x9;
        map2Stream << entityCD.field_0xa;
        map2Stream << entityCD.field_0xb;
        map2Stream << entityCD.field_0xc;
        map2Stream << entityCD.field_0xd;
        map2Stream << entityCD.field_0xe;
        map2Stream << entityCD.field_0xf;
        map2Stream << entityCD.field_0x10;
        map2Stream << entityCD.field_0x11;
        map2Stream << entityCD.field_0x12;
        map2Stream << entityCD.field_0x13;
        map2Stream << entityCD.field_0x14;
        map2Stream << entityCD.field_0x15;
        map2Stream << entityCD.field_0x16;
        map2Stream << entityCD.field_0x17;
        map2Stream << entityCD.field_0x18;
        map2Stream << entityCD.field_0x19;
        map2Stream << entityCD.HP;
        map2Stream << entityCD.field_0x1c;
        map2Stream << entityCD.field_0x1d;
        map2Stream << entityCD.ExperienceGain;
        map2Stream << entityCD.DefSlash;
        map2Stream << entityCD.DefChop;
        map2Stream << entityCD.DefStab;
        map2Stream << entityCD.DefHolyMagic;
        map2Stream << entityCD.DefFireMagic;
        map2Stream << entityCD.DefEarthMagic;
        map2Stream << entityCD.DefWindMagic;
        map2Stream << entityCD.DefWaterMagic;
        map2Stream << entityCD.field_0x30;
        map2Stream << entityCD.field_0x31;
        map2Stream << entityCD.Scale;
        map2Stream << entityCD.field_0x34;
        map2Stream << entityCD.field_0x35;
        map2Stream << entityCD.field_0x36;
        map2Stream << entityCD.field_0x37;
        map2Stream << entityCD.SomePointers[0];
        map2Stream << entityCD.SomePointers[1];
        map2Stream << entityCD.SomePointers[2];
        map2Stream << entityCD.SomePointers[3];
        map2Stream << entityCD.SomePointers[4];
        map2Stream << entityCD.SomePointers[5];
        map2Stream << entityCD.SomePointers[6];
        map2Stream << entityCD.SomePointers[7];
        map2Stream << entityCD.SomePointers[8];
        map2Stream << entityCD.SomePointers[9];
        map2Stream << entityCD.SomePointers[10];
        map2Stream << entityCD.SomePointers[11];
        map2Stream << entityCD.SomePointers[12];
        map2Stream << entityCD.SomePointers[13];
        map2Stream << entityCD.SomePointers[14];
        map2Stream << entityCD.SomePointers[15];
    }

    map2Stream.device()->seek(0x32C8);

    for (auto entityInstance : entityInstances)
    {
        map2Stream << entityInstance.Enabled;
        map2Stream << entityInstance.EntityClass;
        map2Stream << entityInstance.field_0x2;
        map2Stream << entityInstance.WEXTilePos;

        map2Stream << entityInstance.NSYTilePos;
        map2Stream << entityInstance.field_0x5;
        map2Stream << KingsField::getItemIDAsByte(entityInstance.DroppedItem);
        map2Stream << entityInstance.Layer;

        map2Stream << entityInstance.field_0x8;
        map2Stream << entityInstance.field_0x9;
        map2Stream << entityInstance.field_0xa;
        map2Stream << entityInstance.field_0xb;

        map2Stream << entityInstance.field_0xc;
        map2Stream << entityInstance.field_0xd;
        map2Stream << entityInstance.field_0xe;
        map2Stream << entityInstance.field_0xf;
    }

    map2Stream.skipRawData(4);

    for (auto objInstance : objInstances)
    {
        map2Stream << objInstance.TileLayer;
        map2Stream << objInstance.WEXTilePos;
        map2Stream << objInstance.NSYTilePos;
        map2Stream << objInstance.field_0x3;
        map2Stream << KingsField::getItemIDAsByte(objInstance.ItemID);
        map2Stream << objInstance.field_0x5;
        map2Stream << objInstance.field_0x6;
        map2Stream << objInstance.field_0x7;
        map2Stream << objInstance.field_0x8;
        map2Stream << objInstance.field_0x9;
        map2Stream << objInstance.field_0xa;
        map2Stream << objInstance.field_0xb;
        map2Stream << objInstance.field_0xc;
        map2Stream << objInstance.field_0xd;
        map2Stream << objInstance.field_0xe;
        map2Stream << objInstance.field_0xf;
        map2Stream << KingsField::getItemIDAsByte(objInstance.KeyID);
        map2Stream << objInstance.field_0x11;
        map2Stream << objInstance.InstanceContained;
        map2Stream << objInstance.field_0x13;
        map2Stream << objInstance.field_0x14;
        map2Stream << objInstance.field_0x15;
        map2Stream << objInstance.field_0x16;
        map2Stream << objInstance.field_0x17;
    }

    Checksum::calculateAndWriteChecksum(map1);
    Checksum::calculateAndWriteChecksum(map2);
    Checksum::calculateAndWriteChecksum(map3);

    fdat.writeFile(map1, static_cast<int>(mapIndex * 3));
    fdat.writeFile(map2, static_cast<int>(mapIndex * 3) + 1);
    fdat.writeFile(map3, static_cast<int>(mapIndex * 3) + 2);

    setChanged(false);
}

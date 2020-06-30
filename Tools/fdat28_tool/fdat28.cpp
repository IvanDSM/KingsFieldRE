#include "fdat28.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

FDAT28::FDAT28()
{
    oddStructVector.reserve(oddStructVectorSize);
    lvlDataVector.reserve(lvlDataVectorSize);
    magicDataVector.reserve(magicDataVectorSize);
    weaponStatsVector.reserve(weaponStatsVectorSize);
}

KingsField80175914OddStruct FDAT28::getGodOnlyKnows(size_t index)
{
    if (index < oddStructVectorSize)
        return oddStructVector.at(index);
    else
        qDebug() << "Tried to get inexistent GOK struct.";
}

KingsFieldPlayerLvlData FDAT28::getLvlData(size_t level)
{
    if (level < 100)
    {
        auto s = lvlDataVector.at(level);
        if (level > 0)
            for (size_t i = 0; i < level; i++)
            {
                s.StrPowerPlus += lvlDataVector.at(i).StrPowerPlus;
                s.MagPowerPlus += lvlDataVector.at(i).MagPowerPlus;
            }
        return s;
    }
    else
        qDebug() << "Tried to get inexistent level data.";
}

KingsFieldMagicStructure FDAT28::getMagicData(size_t magicId)
{
    if (magicId < magicDataVectorSize)
        return magicDataVector.at(magicId);
    else
        qDebug() << "Tried to get inexistent magic data.";
}

KingsFieldWeaponStats FDAT28::getWeaponStats(size_t weaponId)
{
    if (weaponId < weaponStatsVectorSize)
        return weaponStatsVector.at(weaponId);
    else
        qDebug() << "Tried to get inexistent weapon stats.";
}

bool FDAT28::isLoaded()
{
    return loaded;
}

void FDAT28::loadFile(QString &fileName)
{
    QFile inFile(fileName);
    inFile.open(QIODevice::ReadOnly);

    QDataStream inStream(&inFile);
    inStream.setByteOrder(QDataStream::LittleEndian);

    quint32 sectionSize; ///< I just use this to skip crap

    // Reset the vectors
    oddStructVector.clear();
    lvlDataVector.clear();
    magicDataVector.clear();

    inStream >> sectionSize;
    qInfo() << "Section 1 (god only knows) size:" << sectionSize;

    // Read the odd structs (section 1)
    for (size_t i = 0; i < oddStructVectorSize; i++)
    {
        KingsField80175914OddStruct s;
        inStream >> s.field_0x0;
        inStream >> s.SomeType;
        inStream >> s.field_0x2;
        inStream >> s.field_0x3;
        inStream >> s.CollisionRadius;
        inStream >> s.field_0x6;
        inStream >> s.field_0x7;
        inStream >> s.field_0x8;
        inStream >> s.field_0x9;
        inStream >> s.field_0xa;
        inStream >> s.field_0xb;
        inStream >> s.field_0xc;
        inStream >> s.field_0xd;
        inStream >> s.field_0xe;
        inStream >> s.field_0xf;
        inStream >> s.field_0x10;
        inStream >> s.field_0x11;
        inStream >> s.field_0x12;
        inStream >> s.field_0x13;
        inStream >> s.field_0x14;
        inStream >> s.field_0x15;
        inStream >> s.field_0x16;
        inStream >> s.field_0x17;
        oddStructVector.push_back(s);
    }

    // Read the weapon stats (section 2)
    inStream >> sectionSize;
    qInfo() << "Section 2 (weapon stats) size:" << sectionSize;
    for (quint8 i = 0; i < 6; i++) // Ignore the weird header
    {
        quint8 temp;
        inStream >> temp;
    }
    for (size_t i = 0; i < weaponStatsVectorSize; i++)
    {
        KingsFieldWeaponStats s;
        inStream >> s.OffSlash;
        inStream >> s.OffChop;
        inStream >> s.OffStab;
        inStream >> s.OffHolyM;
        inStream >> s.OffFireM;
        inStream >> s.OffEarthM;
        inStream >> s.OffWindM;
        inStream >> s.OffWaterM;
        inStream >> s.field_0x10;
        inStream >> s.field_0x11;
        inStream >> s.field_0x12;
        inStream >> s.field_0x13;
        inStream >> s.field_0x14;
        inStream >> s.field_0x15;
        inStream >> s.field_0x16;
        inStream >> s.field_0x17;
        inStream >> s.field_0x18;
        inStream >> s.field_0x19;
        inStream >> s.field_0x1a;
        inStream >> s.field_0x1b;
        inStream >> s.field_0x1c;
        inStream >> s.field_0x1d;
        inStream >> s.field_0x1e;
        inStream >> s.field_0x1f;
        inStream >> s.field_0x20;
        inStream >> s.field_0x21;
        inStream >> s.field_0x22;
        inStream >> s.field_0x23;
        inStream >> s.field_0x24;
        inStream >> s.field_0x25;
        inStream >> s.field_0x26;
        inStream >> s.field_0x27;
        inStream >> s.field_0x28;
        inStream >> s.field_0x29;
        inStream >> s.field_0x2a;
        inStream >> s.field_0x2b;
        inStream >> s.field_0x2c;
        inStream >> s.field_0x2d;
        inStream >> s.field_0x2e;
        inStream >> s.field_0x2f;
        inStream >> s.field_0x30;
        inStream >> s.field_0x31;
        inStream >> s.field_0x32;
        inStream >> s.field_0x33;
        inStream >> s.field_0x34;
        inStream >> s.field_0x35;
        inStream >> s.field_0x36;
        inStream >> s.field_0x37;
        inStream >> s.field_0x38;
        inStream >> s.field_0x39;
        inStream >> s.field_0x3a;
        inStream >> s.field_0x3b;
        inStream >> s.field_0x3c;
        inStream >> s.field_0x3d;
        inStream >> s.field_0x3e;
        inStream >> s.field_0x3f;
        inStream >> s.field_0x40;
        inStream >> s.field_0x41;
        inStream >> s.field_0x42;
        inStream >> s.field_0x43;
        weaponStatsVector.push_back(s);
    }
    for (quint8 i = 0; i < 2; i++) // Ignore the weird footer
    {
        quint8 temp;
        inStream >> temp;
    }

    // Skip section 3
    inStream >> sectionSize;
    qInfo() << "Section 3 size:" << sectionSize;
    inStream.skipRawData(sectionSize);

    inStream >> sectionSize;
    qInfo() << "Section 4 (player level data) size:" << sectionSize;

    // Read player level data (section 4)
    for (size_t i = 0; i < lvlDataVectorSize; i++)
    {
        KingsFieldPlayerLvlData s;
        inStream >> s.BaseHP;
        inStream >> s.BaseMP;
        inStream >> s.StrPowerPlus;
        inStream >> s.MagPowerPlus;
        inStream >> s. ExpForNextLevel;
        lvlDataVector.push_back(s);
    }

    inStream >> sectionSize;
    qInfo() << "Section 5 (magic data) size:" << sectionSize;

    // Read magic data (section 5)
    for (size_t i = 0; i < magicDataVectorSize; i++)
    {
        KingsFieldMagicStructure s;
        inStream >> s.PlayerHas;
        inStream >> s.ChargeRecoveryTime;
        inStream >> s.field_0x2;
        inStream >> s.field_0x3;
        inStream >> s.field_0x4;
        inStream >> s.field_0x5;
        inStream >> s.field_0x6;
        inStream >> s.field_0x7;
        inStream >> s.SomeDmg1;
        inStream >> s.SomeDmg2;
        inStream >> s.SomeDmg3;
        inStream >> s.FireDmg;
        inStream >> s.EarthDmg;
        inStream >> s.WindDmg;
        inStream >> s.WaterDmg;
        inStream >> s.MPCost;
        inStream >> s.field_0x18;
        inStream >> s.field_0x19;
        magicDataVector.push_back(s);
    }

    // Skip section 6
    inStream >> sectionSize;
    qInfo() << "Section 6 size:" << sectionSize;
    inStream.skipRawData(sectionSize);

    // Skip section 7
    inStream >> sectionSize;
    qInfo() << "Section 7 size:" << sectionSize;
    inStream.skipRawData(sectionSize);

    // Skip section 8
    inStream >> sectionSize;
    qInfo() << "Section 8 size:" << sectionSize;
    inStream.skipRawData(sectionSize);

    // Skip section 9
    inStream >> sectionSize;
    qInfo() << "Section 9 size:" << sectionSize;
    inStream.skipRawData(sectionSize);

    inFile.close();

    loaded = true;
}

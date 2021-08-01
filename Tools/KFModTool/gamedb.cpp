#include "gamedb.h"
#include "checksum.h"

GameDB::GameDB(QByteArray &file) : database(file)
{

    QDataStream dbStream(database);
    dbStream.setByteOrder(QDataStream::LittleEndian);

    quint32 sectionSize; ///< I just use this to skip crap

    // Section 1 - Object Class Declarations
    dbStream >> sectionSize;

    for (size_t i = 0; i < objClassDeclarationsSize; i++)
    {
        KingsFieldII::ObjectClassDeclaration objClassDecl{};
        dbStream >> objClassDecl;
        objClassDeclarations.at(i) = objClassDecl;
    }

    // Section 2 - Weapon Stats
    dbStream >> sectionSize;

    for (size_t i = 0; i < weaponStatsSize; i++)
    {
        KingsFieldII::WeaponStats weaponStat{};
        dbStream >> weaponStat;
        weaponStats.at(i) = weaponStat;
    }

    // Skip 8 bytes after weapon stats array
    dbStream >> sectionSize;
    dbStream >> sectionSize;

    // Section 3 - Armor Stats
    dbStream >> sectionSize;

    for (auto &armor : armorStats)
        dbStream >> armor;

    // Section 4 - Player Level Data
    dbStream >> sectionSize;

    for (size_t i = 0; i < lvlDataSize; i++)
    {
        KingsFieldII::PlayerLvlData level{};
        dbStream >> level;
        lvlData.at(i) = level;
    }

    // Section 5 - Magic Data
    dbStream >> sectionSize;

    for (size_t i = 0; i < magicDataSize; i++)
    {
        KingsFieldII::Magic magic{};
        dbStream >> magic;
        magicData.at(i) = magic;
    }
}

void GameDB::writeChanges()
{
    QDataStream dbStream(&database, QIODevice::ReadWrite);
    dbStream.setByteOrder(QDataStream::LittleEndian);

    quint32 sectionSize; ///< I just use this to skip crap again

    dbStream >> sectionSize;

    for (size_t i = 0; i < objClassDeclarationsSize; i++)
        dbStream << objClassDeclarations.at(i);

    dbStream >> sectionSize;

    for (size_t i = 0; i < weaponStatsSize; i++)
    {
        dbStream << weaponStats.at(i);
    }

    // Skip 8 bytes after weapon stats array
    dbStream >> sectionSize;
    dbStream >> sectionSize;

    // Skip this unknown stuff (section 3)
    dbStream >> sectionSize;

    for (auto &armor : armorStats)
        dbStream << armor;

    dbStream >> sectionSize;

    for (size_t i = 0; i < lvlDataSize; i++)
        dbStream << lvlData.at(i);

    dbStream >> sectionSize;

    for (size_t i = 0; i < magicDataSize; i++)
        dbStream << magicData.at(i);

    Checksum::calculateAndWriteChecksum(database);
}

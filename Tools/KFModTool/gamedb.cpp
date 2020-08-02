#include "gamedb.h"
#include "checksum.h"

GameDB::GameDB(TFile &fdatTFile) : fdat(fdatTFile), database(fdat.getFile(28))
{

    QDataStream dbStream(database);
    dbStream.setByteOrder(QDataStream::LittleEndian);

    quint32 sectionSize; ///< I just use this to skip crap

    dbStream >> sectionSize;

    for (size_t i = 0; i < objClassDeclarationsSize; i++)
    {
        KingsField::ObjectClassDeclaration objClassDecl{};
        dbStream >> objClassDecl;
        objClassDeclarations.at(i) = objClassDecl;
    }

    for (size_t i = 0; i < weaponStatsSize; i++)
    {
        KingsField::WeaponStats weaponStat{};
        dbStream >> weaponStat;
        weaponStats.at(i) = weaponStat;
    }

    // Skip 8 bytes after weapon stats array
    dbStream >> sectionSize;
    dbStream >> sectionSize;

    // Skip this unknown stuff (section 3)
    dbStream >> sectionSize;
    dbStream.skipRawData(sectionSize);

    dbStream >> sectionSize;

    for (size_t i = 0; i < lvlDataSize; i++)
    {
        KingsField::PlayerLvlData level{};
        dbStream >> level;
        lvlData.at(i) = level;
    }

    dbStream >> sectionSize;

    for (size_t i = 0; i < magicDataSize; i++)
    {
        KingsField::Magic magic{};
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
        dbStream << weaponStats.at(i);


    // Skip this unknown stuff (section 3)
    dbStream >> sectionSize;
    dbStream.skipRawData(sectionSize);

    dbStream >> sectionSize;

    for (size_t i = 0; i < lvlDataSize; i++)
        dbStream << lvlData.at(i);

    dbStream >> sectionSize;

    for (size_t i = 0; i < magicDataSize; i++)
        dbStream << magicData.at(i);

    Checksum::calculateAndWriteChecksum(database);

    fdat.writeFile(database, 28);
}

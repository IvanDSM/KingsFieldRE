#include "gamedb.h"

GameDB::GameDB(TFile &fdatTFile) : fdat(fdatTFile), database(fdat.getFile(28))
{
    objClassDeclarations.reserve(objClassDeclarationsSize);
    lvlData.reserve(lvlDataSize);
    magicData.reserve(magicDataSize);
    weaponStats.reserve(weaponStatsSize);

    QDataStream dbStream(database);
    dbStream.setByteOrder(QDataStream::LittleEndian);

    quint32 sectionSize; ///< I just use this to skip crap

    dbStream >> sectionSize;

    for (size_t i = 0; i < objClassDeclarationsSize; i++)
    {
        KingsField::ObjectClassDeclaration objClassDecl;
        dbStream >> objClassDecl;
        objClassDeclarations.push_back(objClassDecl);
    }

    dbStream >> sectionSize;

    for (quint8 i = 0; i < 3; i++)
    {
        quint16 weirdHeaderTemporaryDumpster;
        dbStream >> weirdHeaderTemporaryDumpster;
    }

    for (size_t i = 0; i < weaponStatsSize; i++)
    {
        KingsField::WeaponStats weaponStat;
        dbStream >> weaponStat;
        weaponStats.push_back(weaponStat);
    }

    {
        quint16 weirdFooterTemporaryDumpster;
        dbStream >> weirdFooterTemporaryDumpster;
    }

    // Skip this unknown stuff (section 3)
    dbStream >> sectionSize;
    dbStream.skipRawData(sectionSize);

    dbStream >> sectionSize;

    for (size_t i = 0; i < lvlDataSize; i++)
    {
        KingsField::PlayerLvlData level;
        dbStream >> level;
        lvlData.push_back(level);
    }

    dbStream >> sectionSize;

    for (size_t i = 0; i < magicDataSize; i++)
    {
        KingsField::Magic magic;
        dbStream >> magic;
        magicData.push_back(magic);
    }
}

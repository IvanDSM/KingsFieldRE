#ifndef GAMEDB_H
#define GAMEDB_H

#include "tfile.h"
#include "kftypes.h"

class GameDB
{
public:
    explicit GameDB(TFile &fdatTFile);

    KingsField::PlayerLvlData &getLevel(byte levelIndex)
    {
        if (levelIndex < lvlDataSize)
            return lvlData.at(levelIndex);
    }

    KingsField::Magic &getMagic(byte magicIndex)
    {
        if (magicIndex < magicDataSize)
            return magicData.at(magicIndex);
    }

    KingsField::ObjectClassDeclaration &getObjClass(unsigned short objClassIndex)
    {
        if (objClassIndex < objClassDeclarationsSize)
            return objClassDeclarations.at(objClassIndex);
    }

    KingsField::WeaponStats &getWeaponStats(byte weaponIndex)
    {
        if (weaponIndex < weaponStatsSize)
            return weaponStats.at(weaponIndex);
    }

    void writeChanges();

    static const size_t objClassDeclarationsSize = 320;
    static const size_t lvlDataSize = 100;
    static const size_t magicDataSize = 64;
    static const size_t weaponStatsSize = 18;

private:
    TFile &fdat;

    QByteArray database;
    std::array<KingsField::ObjectClassDeclaration, objClassDeclarationsSize> objClassDeclarations;
    std::array<KingsField::PlayerLvlData, lvlDataSize> lvlData;
    std::array<KingsField::Magic, magicDataSize> magicData;
    std::array<KingsField::WeaponStats, weaponStatsSize> weaponStats;
};

#endif // GAMEDB_H

#ifndef GAMEDB_H
#define GAMEDB_H

#include "tfile.h"
#include "kftypes.h"

class GameDB
{
public:
    explicit GameDB(TFile &fdatTFile);

    KingsField::Magic &getMagic(byte magicIndex)
    {
        if (magicIndex < 63)
            return magicData.at(magicIndex);
    }

    void writeChanges();

private:
    TFile &fdat;

    QByteArray database;
    static const size_t objClassDeclarationsSize = 320;
    static const size_t lvlDataSize = 100;
    static const size_t magicDataSize = 64;
    static const size_t weaponStatsSize = 18;
    std::array<KingsField::ObjectClassDeclaration, objClassDeclarationsSize> objClassDeclarations;
    std::array<KingsField::PlayerLvlData, lvlDataSize> lvlData;
    std::array<KingsField::Magic, magicDataSize> magicData;
    std::array<KingsField::WeaponStats, weaponStatsSize> weaponStats;
};

#endif // GAMEDB_H

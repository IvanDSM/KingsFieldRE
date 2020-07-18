#ifndef GAMEDB_H
#define GAMEDB_H

#include "tfile.h"
#include "kftypes.h"

class GameDB
{
public:
    explicit GameDB(TFile &fdatTFile);

private:
    TFile &fdat;

    bool changed = false;
    QByteArray database;
    static const size_t objClassDeclarationsSize = 320;
    static const size_t lvlDataSize = 100;
    static const size_t magicDataSize = 64;
    static const size_t weaponStatsSize = 18;
    std::vector<KingsField::ObjectClassDeclaration> objClassDeclarations;
    std::vector<KingsField::PlayerLvlData> lvlData;
    std::vector<KingsField::Magic> magicData;
    std::vector<KingsField::WeaponStats> weaponStats;
};

#endif // GAMEDB_H

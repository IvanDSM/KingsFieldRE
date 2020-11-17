#ifndef GAMEDB_H
#define GAMEDB_H

#include "tfile.h"
#include "kftypes.h"
#include "kfmterror.h"

class GameDB
{
public:
    explicit GameDB(TFile &fdatTFile);

    KingsField::ArmorStats &getArmorStats(size_t armorIndex)
    {
        try
        {
            return armorStats.at(armorIndex);
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(armorIndex, "armor stats", exception.what());
        }
    }

    KingsField::PlayerLvlData &getLevel(byte levelIndex)
    {
        try
        {
            return lvlData.at(levelIndex);
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(levelIndex, "player level data", exception.what());
        }
    }

    KingsField::Magic &getMagic(byte magicIndex)
    {
        try
        {
            return magicData.at(magicIndex);
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(magicIndex, "magic data", exception.what());
        }
    }

    KingsField::ObjectClassDeclaration &getObjClass(unsigned short objClassIndex)
    {
        try
        {
            return objClassDeclarations.at(objClassIndex);
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(objClassIndex, "object class declaration", exception.what());
        }
    }

    KingsField::WeaponStats &getWeaponStats(byte weaponIndex)
    {
        try
        {
            return weaponStats.at(weaponIndex);
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(weaponIndex, "weapon stats", exception.what());
        }
    }

    void writeChanges();

    static constexpr size_t armorStatsSize = 64;
    static constexpr size_t objClassDeclarationsSize = 320;
    static constexpr size_t lvlDataSize = 100;
    static constexpr size_t magicDataSize = 64;
    static constexpr size_t weaponStatsSize = 18;

private:
    TFile &fdat;

    QByteArray database;
    std::array<KingsField::ArmorStats, armorStatsSize> armorStats {};
    std::array<KingsField::ObjectClassDeclaration, objClassDeclarationsSize> objClassDeclarations {};
    std::array<KingsField::PlayerLvlData, lvlDataSize> lvlData {};
    std::array<KingsField::Magic, magicDataSize> magicData {};
    std::array<KingsField::WeaponStats, weaponStatsSize> weaponStats {};
};

#endif // GAMEDB_H

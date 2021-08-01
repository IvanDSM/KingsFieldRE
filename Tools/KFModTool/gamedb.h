#ifndef GAMEDB_H
#define GAMEDB_H

#include "kf2types.h"
#include "kfmterror.h"
#include "tfile.h"

class GameDB
{
public:
    explicit GameDB(QByteArray &file);

    KingsFieldII::ArmorStats &getArmorStats(size_t armorIndex)
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

    KingsFieldII::PlayerLvlData &getLevel(size_t levelIndex)
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

    KingsFieldII::Magic &getMagic(size_t magicIndex)
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

    KingsFieldII::ObjectClassDeclaration &getObjClass(size_t objClassIndex)
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

    KingsFieldII::WeaponStats &getWeaponStats(size_t weaponIndex)
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
    QByteArray &database;
    
    
    std::array<KingsFieldII::ArmorStats, armorStatsSize> armorStats {};
    std::array<KingsFieldII::ObjectClassDeclaration, objClassDeclarationsSize> objClassDeclarations {};
    std::array<KingsFieldII::PlayerLvlData, lvlDataSize> lvlData {};
    std::array<KingsFieldII::Magic, magicDataSize> magicData {};
    std::array<KingsFieldII::WeaponStats, weaponStatsSize> weaponStats {};
};

#endif // GAMEDB_H

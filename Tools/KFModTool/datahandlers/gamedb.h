#ifndef GAMEDB_H
#define GAMEDB_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include "games/kf2.h"

class GameDB : public KFMTDataHandler
{
public:
    explicit GameDB(KFMTFile& file);

    KingsFieldII::ArmorStats& getArmorStat(size_t armorIndex)
    {
        if (armorIndex >= armorStatsSize)
            KFMTError::outOfRange(armorIndex, QStringLiteral("armor stats"));
        return armorStats[armorIndex];
    }

    KingsFieldII::PlayerLvlData &getLevel(size_t levelIndex)
    {
        if (levelIndex >= lvlDataSize)
            KFMTError::outOfRange(levelIndex, QStringLiteral("player level data"));
        return lvlData[levelIndex];
    }

    KingsFieldII::Magic &getMagic(size_t magicIndex)
    {
        if (magicIndex >= magicDataSize)
            KFMTError::outOfRange(magicIndex, QStringLiteral("magic data"));
        return magicData[magicIndex];
    }

    KingsFieldII::ObjectClass& getObjClass(size_t objClassIndex)
    {
        if (objClassIndex >= objClassesSize)
            KFMTError::outOfRange(objClassIndex, QStringLiteral("object class declaration"));
        return objClasses[objClassIndex];
    }

    KingsFieldII::WeaponStats &getWeaponStats(size_t weaponIndex)
    {
        if (weaponIndex >= weaponStatsSize)
            KFMTError::outOfRange(weaponIndex, QStringLiteral("weapon stats"));
        return weaponStats[weaponIndex];
    }

    void saveChanges() override {}

    static constexpr size_t armorStatsSize = 64;
    static constexpr size_t objClassesSize = 320;
    static constexpr size_t lvlDataSize = 100;
    static constexpr size_t magicDataSize = 64;
    static constexpr size_t weaponStatsSize = 18;

private:
    KingsFieldII::ArmorStats* armorStats;
    KingsFieldII::ObjectClass* objClasses;
    KingsFieldII::PlayerLvlData* lvlData;
    KingsFieldII::Magic* magicData;
    KingsFieldII::WeaponStats* weaponStats;
};

#endif // GAMEDB_H

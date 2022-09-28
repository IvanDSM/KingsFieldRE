#ifndef GAMEDB_H
#define GAMEDB_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include "kf2/armor.h"
#include "kf2/magic.h"
#include "kf2/object.h"
#include "kf2/playerlevel.h"
#include "kf2/weapon.h"

class GameDB : public KFMTDataHandler
{
public:
    explicit GameDB(KFMTFile& file);

    KF2::Armor& getArmorStat(size_t armorIndex)
    {
        if (armorIndex >= armorStatsSize)
            KFMTError::outOfRange(armorIndex, QStringLiteral("armor stats"));
        return armorStats[armorIndex];
    }

    KF2::PlayerLevel &getLevel(size_t levelIndex)
    {
        if (levelIndex >= lvlDataSize)
            KFMTError::outOfRange(levelIndex, QStringLiteral("player level data"));
        return lvlData[levelIndex];
    }

    KF2::Magic &getMagic(size_t magicIndex)
    {
        if (magicIndex >= magicDataSize)
            KFMTError::outOfRange(magicIndex, QStringLiteral("magic data"));
        return magicData[magicIndex];
    }

    KF2::ObjectClass& getObjClass(size_t objClassIndex)
    {
        if (objClassIndex >= objClassesSize)
            KFMTError::outOfRange(objClassIndex, QStringLiteral("object class declaration"));
        return objClasses[objClassIndex];
    }

    KF2::Weapon &getWeaponStats(size_t weaponIndex)
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
    KF2::Armor* armorStats;
    KF2::ObjectClass* objClasses;
    KF2::PlayerLevel* lvlData;
    KF2::Magic* magicData;
    KF2::Weapon* weaponStats;
};

#endif // GAMEDB_H

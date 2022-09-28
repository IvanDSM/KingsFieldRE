#include "weapon.h"
#include "core/kfmtcore.h"

QString KF2::getWeaponName(const uint8_t weaponIndex)
{
    switch (weaponIndex)
    {
        case 0: return QStringLiteral("Dagger");
        case 1: return QStringLiteral("Short Sword");
        case 2: return QStringLiteral("Knight Sword");
        case 3: return QStringLiteral("Morning Star");
        case 4: return QStringLiteral("Battle Hammer");
        case 5: return QStringLiteral("Bastard Sword");
        case 6: return QStringLiteral("Crescent Axe");
        case 7: return QStringLiteral("A");
        case 8: return QStringLiteral("A");
        case 9: return QStringLiteral("Flame Sword");
        case 10: return QStringLiteral("Shiden");
        case 11: return QStringLiteral("Spider");
        case 12: return QStringLiteral("Ice Blade");
        case 13: return QStringLiteral("Seath's Sword");
        case 14: return QStringLiteral("Moonlight Sword");
        case 15: return QStringLiteral("Dark Slayer");
        case 16: return QStringLiteral("Bow");
        case 17: return QStringLiteral("Arbalest");
        default: return unknownString;
    }
}

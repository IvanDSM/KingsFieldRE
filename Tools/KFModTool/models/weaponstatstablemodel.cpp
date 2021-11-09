#include "weaponstatstablemodel.h"
#include "utilities.h"

QVariant WeaponStatsTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    const auto& weaponStat = gameDB.getWeaponStats(curWeapon);

    switch (index.row())
    {
        case 0: return QString::number(weaponStat.SoundEffect);
        case 1: return QString::number(weaponStat.StrStaminaCost);
        case 2: return QString::number(weaponStat.Unknown_x02);
        case 3:
            return QString::number(KingsFieldII::getMagicIDAsByte(weaponStat.Spell1))
                   + QStringLiteral(" (") + KingsFieldII::getMagicIDName(weaponStat.Spell1) + ')';
        case 4:
            return QString::number(KingsFieldII::getMagicIDAsByte(weaponStat.Spell2))
                   + QStringLiteral(" (") + KingsFieldII::getMagicIDName(weaponStat.Spell2) + ')';
        case 5: return QString::number(weaponStat.Spell1ShotAmount);
        case 6: return QString::number(weaponStat.OffSlash);
        case 7: return QString::number(weaponStat.OffChop);
        case 8: return QString::number(weaponStat.OffStab);
        case 9: return QString::number(weaponStat.OffHolyM);
        case 10: return QString::number(weaponStat.OffFireM);
        case 11: return QString::number(weaponStat.OffEarthM);
        case 12: return QString::number(weaponStat.OffWindM);
        case 13: return QString::number(weaponStat.OffWaterM);
        case 14: return QString::number(weaponStat.HPRestoreTimer);
        case 15: return QString::number(weaponStat.MPRestoreTimer);
        case 16: return QString::number(weaponStat.AttackRange);
        case 17: return QString::number(weaponStat.SwingSpeed);
        case 18: return QString::number(weaponStat.SwingDamageStartTime);
        case 19: return QString::number(weaponStat.Spell1CastStartTime);
        case 20: return QString::number(weaponStat.Spell1CastEndTime);
        case 21: return QString::number(weaponStat.Spell2AnimSpeed);
        case 22: return QString::number(weaponStat.Unknown_x26);
        case 23: return QString::number(weaponStat.Spell2DamageStartTime);
        case 24: return QString::number(weaponStat.Unknown_x2a);
        case 25: return QString::number(weaponStat.Unknown_x2c);
        case 26: return QString::number(weaponStat.Unknown_x2e);
        case 27: return QString::number(weaponStat.Unknown_x30);
        case 28: return QString::number(weaponStat.Unknown_x32);
        case 29: return QString::number(weaponStat.Position.vx);
        case 30: return QString::number(weaponStat.Position.vy);
        case 31: return QString::number(weaponStat.Position.vz);
        case 32: return QString::number(weaponStat.Position.pad);
        case 33: return QString::number(weaponStat.SomeVec.vx);
        case 34: return QString::number(weaponStat.SomeVec.vy);
        case 35: return QString::number(weaponStat.SomeVec.vz);
        case 36: return QString::number(weaponStat.SomeVec.pad);
        default: return {};
    }
}

QVariant WeaponStatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):
    switch (section)
    {
        case 0: return QStringLiteral("Sound Effect");
        case 1: return QStringLiteral("Str Stamina Cost");
        case 2: return QStringLiteral("Unknown 02");
        case 3: return QStringLiteral("Spell 1");
        case 4: return QStringLiteral("Spell 2");
        case 5: return QStringLiteral("Spell 1 Shot Amount");
        case 6: return QStringLiteral("Slash Offense");
        case 7: return QStringLiteral("Chop Offense");
        case 8: return QStringLiteral("Stab Offense");
        case 9: return QStringLiteral("Holy Magic Offense");
        case 10: return QStringLiteral("Fire Magic Offense");
        case 11: return QStringLiteral("Earth Magic Offense");
        case 12: return QStringLiteral("Wind Magic Offense");
        case 13: return QStringLiteral("Water Magic Offense");
        case 14: return QStringLiteral("HP Restore Timer");
        case 15: return QStringLiteral("MP Restore Timer");
        case 16: return QStringLiteral("Attack Range");
        case 17: return QStringLiteral("Swing Speed");
        case 18: return QStringLiteral("Swing Damage Start Time");
        case 19: return QStringLiteral("Spell 1 Cast Start Time");
        case 20: return QStringLiteral("Spell 1 Cast End Time");
        case 21: return QStringLiteral("Spell 2 Animation Speed");
        case 22: return QStringLiteral("Unknown 26");
        case 23: return QStringLiteral("Spell 2 Damage Start Time?");
        case 24: return QStringLiteral("Unknown 2A");
        case 25: return QStringLiteral("Unknown 2C");
        case 26: return QStringLiteral("Unknown 2E");
        case 27: return QStringLiteral("Unknown 30");
        case 28: return QStringLiteral("Unknown 32");
        case 29: return QStringLiteral("Position?.vx");
        case 30: return QStringLiteral("Position?.vy");
        case 31: return QStringLiteral("Position?.vz");
        case 32: return QStringLiteral("Position?.pad");
        case 33: return QStringLiteral("SomeVec.vx");
        case 34: return QStringLiteral("SomeVec.vy");
        case 35: return QStringLiteral("SomeVec.vz");
        case 36: return QStringLiteral("SomeVec.pad");
        default: return {};
    }
}

bool WeaponStatsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    auto& weaponStat = gameDB.getWeaponStats(curWeapon);

    int intValue = value.toInt();
    unsigned int uIntValue = value.toUInt();
    switch (index.row())
    {
        case 0: weaponStat.SoundEffect = Utilities::clampToByte(uIntValue); break;
        case 1: weaponStat.StrStaminaCost = Utilities::clampToByte(uIntValue); break;
        case 2: weaponStat.Unknown_x02 = Utilities::clampToByte(uIntValue); break;
        case 3:
            weaponStat.Spell1 = KingsFieldII::getMagicIDFromByte(Utilities::clampToByte(uIntValue));
            break;
        case 4:
            weaponStat.Spell2 = KingsFieldII::getMagicIDFromByte(Utilities::clampToByte(uIntValue));
            break;
        case 5: weaponStat.Spell1ShotAmount = Utilities::clampToByte(uIntValue); break;
        case 6: weaponStat.OffSlash = Utilities::clampToUShort(uIntValue); break;
        case 7: weaponStat.OffChop = Utilities::clampToUShort(uIntValue); break;
        case 8: weaponStat.OffStab = Utilities::clampToUShort(uIntValue); break;
        case 9: weaponStat.OffHolyM = Utilities::clampToUShort(uIntValue); break;
        case 10: weaponStat.OffFireM = Utilities::clampToUShort(uIntValue); break;
        case 11: weaponStat.OffEarthM = Utilities::clampToUShort(uIntValue); break;
        case 12: weaponStat.OffWindM = Utilities::clampToUShort(uIntValue); break;
        case 13: weaponStat.OffWaterM = Utilities::clampToUShort(uIntValue); break;
        case 14: weaponStat.HPRestoreTimer = Utilities::clampToUShort(uIntValue); break;
        case 15: weaponStat.MPRestoreTimer = Utilities::clampToUShort(uIntValue); break;
        case 16: weaponStat.AttackRange = Utilities::clampToShort(intValue); break;
        case 17: weaponStat.SwingSpeed = Utilities::clampToUShort(uIntValue); break;
        case 18: weaponStat.SwingDamageStartTime = Utilities::clampToUShort(uIntValue); break;
        case 19: weaponStat.Spell1CastStartTime = Utilities::clampToUShort(uIntValue); break;
        case 20: weaponStat.Spell1CastEndTime = Utilities::clampToUShort(uIntValue); break;
        case 21: weaponStat.Spell2AnimSpeed = Utilities::clampToShort(intValue); break;
        case 22: weaponStat.Unknown_x26 = Utilities::clampToUShort(uIntValue); break;
        case 23: weaponStat.Spell2DamageStartTime = Utilities::clampToUShort(uIntValue); break;
        case 24: weaponStat.Unknown_x2a = Utilities::clampToUShort(uIntValue); break;
        case 25: weaponStat.Unknown_x2c = Utilities::clampToUShort(uIntValue); break;
        case 26: weaponStat.Unknown_x2e = Utilities::clampToUShort(uIntValue); break;
        case 27: weaponStat.Unknown_x30 = Utilities::clampToUShort(uIntValue); break;
        case 28: weaponStat.Unknown_x32 = Utilities::clampToShort(intValue); break;
        case 29: weaponStat.Position.vx = Utilities::clampToShort(intValue); break;
        case 30: weaponStat.Position.vy = Utilities::clampToShort(intValue); break;
        case 31: weaponStat.Position.vz = Utilities::clampToShort(intValue); break;
        case 32: weaponStat.Position.pad = Utilities::clampToShort(intValue); break;
        case 33: weaponStat.SomeVec.vx = Utilities::clampToShort(intValue); break;
        case 34: weaponStat.SomeVec.vy = Utilities::clampToShort(intValue); break;
        case 35: weaponStat.SomeVec.vz = Utilities::clampToShort(intValue); break;
        case 36: weaponStat.SomeVec.pad = Utilities::clampToShort(intValue); break;
        default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

#include "weaponstatstablemodel.h"
#include "utilities.h"

QVariant WeaponStatsTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(weaponStats.SoundEffect)); break;
            case 1: result.setValue(QString::number(weaponStats.StrStaminaCost)); break;
            case 2: result.setValue(QString::number(weaponStats.Unknown_x02)); break;
            case 3: result.setValue(QString::number(KingsField::getMagicIDAsByte(weaponStats.Spell1)) +
                                    " (" +
                                    KingsField::getMagicIDName(weaponStats.Spell1) +
                                    ')'); break;
            case 4: result.setValue(QString::number(KingsField::getMagicIDAsByte(weaponStats.Spell2)) +
                                    " (" +
                                    KingsField::getMagicIDName(weaponStats.Spell2) +
                                    ')'); break;
            case 5: result.setValue(QString::number(weaponStats.Spell1ShotAmount)); break;
            case 6: result.setValue(QString::number(weaponStats.OffSlash)); break;
            case 7: result.setValue(QString::number(weaponStats.OffChop)); break;
            case 8: result.setValue(QString::number(weaponStats.OffStab)); break;
            case 9: result.setValue(QString::number(weaponStats.OffHolyM)); break;
            case 10: result.setValue(QString::number(weaponStats.OffFireM)); break;
            case 11: result.setValue(QString::number(weaponStats.OffEarthM)); break;
            case 12: result.setValue(QString::number(weaponStats.OffWindM)); break;
            case 13: result.setValue(QString::number(weaponStats.OffWaterM)); break;
            case 14: result.setValue(QString::number(weaponStats.HPRestoreTimer)); break;
            case 15: result.setValue(QString::number(weaponStats.MPRestoreTimer)); break;
            case 16: result.setValue(QString::number(weaponStats.AttackRange)); break;
            case 17: result.setValue(QString::number(weaponStats.SwingSpeed)); break;
            case 18: result.setValue(QString::number(weaponStats.SwingDamageStartTime)); break;
            case 19: result.setValue(QString::number(weaponStats.Spell1CastStartTime)); break;
            case 20: result.setValue(QString::number(weaponStats.Spell1CastEndTime)); break;
            case 21: result.setValue(QString::number(weaponStats.Spell2AnimSpeed)); break;
            case 22: result.setValue(QString::number(weaponStats.Unknown_x26)); break;
            case 23: result.setValue(QString::number(weaponStats.Spell2DamageStartTime)); break;
            case 24: result.setValue(QString::number(weaponStats.Unknown_x2a)); break;
            case 25: result.setValue(QString::number(weaponStats.Unknown_x2c)); break;
            case 26: result.setValue(QString::number(weaponStats.Unknown_x2e)); break;
            case 27: result.setValue(QString::number(weaponStats.Unknown_x30)); break;
            case 28: result.setValue(QString::number(weaponStats.Unknown_x32)); break;
            case 29: result.setValue(QString::number(weaponStats.Position.vx)); break;
            case 30: result.setValue(QString::number(weaponStats.Position.vy)); break;
            case 31: result.setValue(QString::number(weaponStats.Position.vz)); break;
            case 32: result.setValue(QString::number(weaponStats.Position.pad)); break;
            case 33: result.setValue(QString::number(weaponStats.SomeVec.vx)); break;
            case 34: result.setValue(QString::number(weaponStats.SomeVec.vy)); break;
            case 35: result.setValue(QString::number(weaponStats.SomeVec.vz)); break;
            case 36: result.setValue(QString::number(weaponStats.SomeVec.pad)); break;
        }
    }
    return result;
}

QVariant WeaponStatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Sound Effect";
                case 1: return "Str Stamina Cost";
                case 2: return "Unknown 02";
                case 3: return "Spell 1";
                case 4: return "Spell 2";
                case 5: return "Spell 1 Shot Amount";
                case 6: return "Slash Offense";
                case 7: return "Chop Offense";
                case 8: return "Stab Offense";
                case 9: return "Holy Magic Offense";
                case 10: return "Fire Magic Offense";
                case 11: return "Earth Magic Offense";
                case 12: return "Wind Magic Offense";
                case 13: return "Water Magic Offense";
                case 14: return "HP Restore Timer";
                case 15: return "MP Restore Timer";
                case 16: return "Attack Range";
                case 17: return "Swing Speed";
                case 18: return "Swing Damage Start Time";
                case 19: return "Spell 1 Cast Start Time";
                case 20: return "Spell 1 Cast End Time";
                case 21: return "Spell 2 Animation Speed";
                case 22: return "Unknown 26";
                case 23: return "Spell 2 Damage Start Time?";
                case 24: return "Unknown 2A";
                case 25: return "Unknown 2C";
                case 26: return "Unknown 2E";
                case 27: return "Unknown 30";
                case 28: return "Unknown 32";
                case 29: return "Position?.vx";
                case 30: return "Position?.vy";
                case 31: return "Position?.vz";
                case 32: return "Position?.pad";
                case 33: return "SomeVec.vx";
                case 34: return "SomeVec.vy";
                case 35: return "SomeVec.vz";
                case 36: return "SomeVec.pad";
                default: break;
            }
        }
    }
    return QVariant();
}

bool WeaponStatsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        int intValue = value.toInt();
        unsigned int uIntValue = value.toUInt();
        switch (index.row())
        {
            case 0: weaponStats.SoundEffect = Utilities::clampToByte(uIntValue); break;
            case 1: weaponStats.StrStaminaCost = Utilities::clampToByte(uIntValue); break;
            case 2: weaponStats.Unknown_x02 = Utilities::clampToByte(uIntValue); break;
            case 3: weaponStats.Spell1 = KingsField::getMagicIDFromByte(Utilities::clampToByte(uIntValue)); break;
            case 4: weaponStats.Spell2 = KingsField::getMagicIDFromByte(Utilities::clampToByte(uIntValue)); break;
            case 5: weaponStats.Spell1ShotAmount = Utilities::clampToByte(uIntValue); break;
            case 6: weaponStats.OffSlash = Utilities::clampToUShort(uIntValue); break;
            case 7: weaponStats.OffChop = Utilities::clampToUShort(uIntValue); break;
            case 8: weaponStats.OffStab = Utilities::clampToUShort(uIntValue); break;
            case 9: weaponStats.OffHolyM = Utilities::clampToUShort(uIntValue); break;
            case 10: weaponStats.OffFireM = Utilities::clampToUShort(uIntValue); break;
            case 11: weaponStats.OffEarthM = Utilities::clampToUShort(uIntValue); break;
            case 12: weaponStats.OffWindM = Utilities::clampToUShort(uIntValue); break;
            case 13: weaponStats.OffWaterM = Utilities::clampToUShort(uIntValue); break;
            case 14: weaponStats.HPRestoreTimer = Utilities::clampToUShort(uIntValue); break;
            case 15: weaponStats.MPRestoreTimer = Utilities::clampToUShort(uIntValue); break;
            case 16: weaponStats.AttackRange = Utilities::clampToShort(intValue); break;
            case 17: weaponStats.SwingSpeed = Utilities::clampToUShort(uIntValue); break;
            case 18: weaponStats.SwingDamageStartTime = Utilities::clampToUShort(uIntValue); break;
            case 19: weaponStats.Spell1CastStartTime = Utilities::clampToUShort(uIntValue); break;
            case 20: weaponStats.Spell1CastEndTime = Utilities::clampToUShort(uIntValue); break;
            case 21: weaponStats.Spell2AnimSpeed = Utilities::clampToShort(intValue); break;
            case 22: weaponStats.Unknown_x26 = Utilities::clampToUShort(uIntValue); break;
            case 23: weaponStats.Spell2DamageStartTime = Utilities::clampToUShort(uIntValue); break;
            case 24: weaponStats.Unknown_x2a = Utilities::clampToUShort(uIntValue); break;
            case 25: weaponStats.Unknown_x2c = Utilities::clampToUShort(uIntValue); break;
            case 26: weaponStats.Unknown_x2e = Utilities::clampToUShort(uIntValue); break;
            case 27: weaponStats.Unknown_x30 = Utilities::clampToUShort(uIntValue); break;
            case 28: weaponStats.Unknown_x32 = Utilities::clampToShort(intValue); break;
            case 29: weaponStats.Position.vx = Utilities::clampToShort(intValue); break;
            case 30: weaponStats.Position.vy = Utilities::clampToShort(intValue); break;
            case 31: weaponStats.Position.vz = Utilities::clampToShort(intValue); break;
            case 32: weaponStats.Position.pad = Utilities::clampToShort(intValue); break;
            case 33: weaponStats.SomeVec.vx = Utilities::clampToShort(intValue); break;
            case 34: weaponStats.SomeVec.vy = Utilities::clampToShort(intValue); break;
            case 35: weaponStats.SomeVec.vz = Utilities::clampToShort(intValue); break;
            case 36: weaponStats.SomeVec.pad = Utilities::clampToShort(intValue); break;
        }
    }

    emit dataChanged(index, index);

    return true;
}

#include "weaponstatstablemodel.h"

QVariant WeaponStatsTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        if (index.row() < 14)
        {
            switch (index.row())
            {
                case 0: result.setValue(QString::number(weaponStats.Unknown_x00)); break;
                case 1: result.setValue(QString::number(weaponStats.Unknown_x01)); break;
                case 2: result.setValue(QString::number(weaponStats.Unknown_x02)); break;
                case 3: result.setValue(QString::number(weaponStats.Unknown_x03)); break;
                case 4: result.setValue(QString::number(weaponStats.Unknown_x04)); break;
                case 5: result.setValue(QString::number(weaponStats.Unknown_x05)); break;
                case 6: result.setValue(QString::number(weaponStats.OffSlash)); break;
                case 7: result.setValue(QString::number(weaponStats.OffChop)); break;
                case 8: result.setValue(QString::number(weaponStats.OffStab)); break;
                case 9: result.setValue(QString::number(weaponStats.OffHolyM)); break;
                case 10: result.setValue(QString::number(weaponStats.OffFireM)); break;
                case 11: result.setValue(QString::number(weaponStats.OffEarthM)); break;
                case 12: result.setValue(QString::number(weaponStats.OffWindM)); break;
                case 13: result.setValue(QString::number(weaponStats.OffWaterM)); break;
            }
        }
        else
            result.setValue(QString::number(weaponStats.UnknownStuff[index.row() - 14]));
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
            if (section < 14)
            {
                switch (section)
                {
                    case 0: return "Unknown 00";
                    case 1: return "Unknown 01";
                    case 2: return "Unknown 02";
                    case 3: return "Unknown 03";
                    case 4: return "Unknown 04";
                    case 5: return "Unknown 05";
                    case 6: return "Slash Offense";
                    case 7: return "Chop Offense";
                    case 8: return "Stab Offense";
                    case 9: return "Holy Magic Offense";
                    case 10: return "Fire Magic Offense";
                    case 11: return "Earth Magic Offense";
                    case 12: return "Wind Magic Offense";
                    case 13: return "Water Magic Offense";
                    default: break;
                }
            }
            else
            {
                return QString("Unknown Stuff[0x" + QString::number(section - 14, 16) + ']');
            }
        }
    }
    return QVariant();
}

bool WeaponStatsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        unsigned int uIntValue = value.toUInt();
        if (index.row() < 14)
        {
            switch (index.row())
            {
                case 0: weaponStats.Unknown_x00 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 1: weaponStats.Unknown_x01 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 2: weaponStats.Unknown_x02 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 3: weaponStats.Unknown_x03 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 4: weaponStats.Unknown_x04 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 5: weaponStats.Unknown_x05 = static_cast<quint8>(qMin(static_cast<unsigned int>(255), uIntValue)); break;
                case 6:  weaponStats.OffSlash = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 7:  weaponStats.OffChop = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 8:  weaponStats.OffStab = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 9:  weaponStats.OffHolyM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 10:  weaponStats.OffFireM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 11:  weaponStats.OffEarthM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 12:  weaponStats.OffWindM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 13:  weaponStats.OffWaterM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
            }
        }
        else
        {
            weaponStats.UnknownStuff[index.row() - 14] = static_cast<undefined>(qMin(static_cast<unsigned int>(255), uIntValue));
        }
    }

    emit dataChanged(index, index);

    return true;
}

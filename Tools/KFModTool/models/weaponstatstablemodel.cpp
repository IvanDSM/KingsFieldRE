#include "weaponstatstablemodel.h"

QVariant WeaponStatsTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        if (index.row() < 8)
        {
            switch (index.row())
            {
                case 0: result.setValue(QString::number(weaponStats.OffSlash)); break;
                case 1: result.setValue(QString::number(weaponStats.OffChop)); break;
                case 2: result.setValue(QString::number(weaponStats.OffStab)); break;
                case 3: result.setValue(QString::number(weaponStats.OffHolyM)); break;
                case 4: result.setValue(QString::number(weaponStats.OffFireM)); break;
                case 5: result.setValue(QString::number(weaponStats.OffEarthM)); break;
                case 6: result.setValue(QString::number(weaponStats.OffWindM)); break;
                case 7: result.setValue(QString::number(weaponStats.OffWaterM)); break;
            }
        }
        else
            result.setValue(QString::number(weaponStats.UnknownStuff[index.row() - 8]));
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
            if (section < 8)
            {
                switch (section)
                {
                    case 0: return "Slash Offense";
                    case 1: return "Chop Offense";
                    case 2: return "Stab Offense";
                    case 3: return "Holy Magic Offense";
                    case 4: return "Fire Magic Offense";
                    case 5: return "Earth Magic Offense";
                    case 6: return "Wind Magic Offense";
                    case 7: return "Water Magic Offense";
                    default: break;
                }
            }
            else
            {
                return QString("Unknown Stuff[0x" + QString::number(section - 8, 16) + ']');
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
        if (index.row() < 8)
        {
            switch (index.row())
            {
                case 0:  weaponStats.OffSlash = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 1:  weaponStats.OffChop = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 2:  weaponStats.OffStab = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 3:  weaponStats.OffHolyM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 4:  weaponStats.OffFireM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 5:  weaponStats.OffEarthM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 6:  weaponStats.OffWindM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
                case 7:  weaponStats.OffWaterM = static_cast<quint16>(qMin(static_cast<unsigned int>(65535), uIntValue)); break;
            }
        }
        else
        {
            weaponStats.UnknownStuff[index.row() - 8] = static_cast<undefined>(qMin(static_cast<unsigned int>(255), uIntValue));
        }
    }

    emit dataChanged(index, index);

    return true;
}

#include "armorstatstablemodel.h"
#include "utilities.h"

QVariant ArmorStatsTableModel::data(const QModelIndex & index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(armorStats.Thingie)); break;
            case 1: result.setValue(QString::number(armorStats.DefSlash)); break;
            case 2: result.setValue(QString::number(armorStats.DefChop)); break;
            case 3: result.setValue(QString::number(armorStats.DefStab)); break;
            case 4: result.setValue(QString::number(armorStats.DefPoison)); break;
            case 5: result.setValue(QString::number(armorStats.DefDarkM)); break;
            case 6: result.setValue(QString::number(armorStats.DefFireM)); break;
            case 7: result.setValue(QString::number(armorStats.DefEarthM)); break;
            case 8: result.setValue(QString::number(armorStats.DefWindM)); break;
            case 9: result.setValue(QString::number(armorStats.DefWaterM)); break;
            case 10: result.setValue(QString::number(armorStats.field_0x14)); break;
            case 11: result.setValue(QString::number(armorStats.field_0x16)); break;
            case 12: result.setValue(QString::number(armorStats.field_0x18)); break;
            case 13: result.setValue(QString::number(armorStats.field_0x1a)); break;
            case 14: result.setValue(QString::number(armorStats.field_0x1c)); break;
            case 15: result.setValue(QString::number(armorStats.field_0x1e)); break;
        }
    }

    return result;
}

QVariant ArmorStatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Unknown 00"; break;
                case 1: return "Slash Defense"; break;
                case 2: return "Chop Defense"; break;
                case 3: return "Stab Defense"; break;
                case 4: return "Poison Defense"; break;
                case 5: return "Dark Magic Defense"; break;
                case 6: return "Fire Magic Defense"; break;
                case 7: return "Earth Magic Defense"; break;
                case 8: return "Wind Magic Defense"; break;
                case 9: return "Water Magic Defense"; break;
                case 10: return "Unknown 14"; break;
                case 11: return "Unknown 16"; break;
                case 12: return "Unknown 18"; break;
                case 13: return "Unknown 1A"; break;
                case 14: return "Unknown 1C"; break;
                case 15: return "Unknown 1E"; break;
            }
        }
    }

    return QVariant();
}

bool ArmorStatsTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    bool result = false;

    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        auto uShortValue = Utilities::clampToUShort(value.toUInt());

        switch (index.row())
        {
            case 0: armorStats.Thingie = uShortValue; break;
            case 1: armorStats.DefSlash = uShortValue; break;
            case 2: armorStats.DefChop = uShortValue; break;
            case 3: armorStats.DefStab = uShortValue; break;
            case 4: armorStats.DefPoison = uShortValue; break;
            case 5: armorStats.DefDarkM = uShortValue; break;
            case 6: armorStats.DefFireM = uShortValue; break;
            case 7: armorStats.DefEarthM = uShortValue; break;
            case 8: armorStats.DefWindM = uShortValue; break;
            case 9: armorStats.DefWaterM = uShortValue; break;
            case 10: armorStats.field_0x14 = uShortValue; break;
            case 11: armorStats.field_0x16 = uShortValue; break;
            case 12: armorStats.field_0x18 = uShortValue; break;
            case 13: armorStats.field_0x1a = uShortValue; break;
            case 14: armorStats.field_0x1c = uShortValue; break;
            case 15: armorStats.field_0x1e = uShortValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

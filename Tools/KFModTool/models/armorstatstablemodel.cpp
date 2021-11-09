#include "armorstatstablemodel.h"
#include "utilities.h"

QVariant ArmorStatsTableModel::data(const QModelIndex & index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    const auto& armorStat = gameDB.getArmorStat(curArmorStat);

    switch (index.row())
    {
        case 0: return QString::number(armorStat.Thingie);
        case 1: return QString::number(armorStat.DefSlash);
        case 2: return QString::number(armorStat.DefChop);
        case 3: return QString::number(armorStat.DefStab);
        case 4: return QString::number(armorStat.DefPoison);
        case 5: return QString::number(armorStat.DefDarkM);
        case 6: return QString::number(armorStat.DefFireM);
        case 7: return QString::number(armorStat.DefEarthM);
        case 8: return QString::number(armorStat.DefWindM);
        case 9: return QString::number(armorStat.DefWaterM);
        case 10: return QString::number(armorStat.field_0x14);
        case 11: return QString::number(armorStat.field_0x16);
        case 12: return QString::number(armorStat.field_0x18);
        case 13: return QString::number(armorStat.field_0x1a);
        case 14: return QString::number(armorStat.field_0x1c);
        case 15: return QString::number(armorStat.field_0x1e);
        default: return {};
    }
}

QVariant ArmorStatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):
    switch (section)
    {
        case 0: return QStringLiteral("Unknown 00");
        case 1: return QStringLiteral("Slash Defense");
        case 2: return QStringLiteral("Chop Defense");
        case 3: return QStringLiteral("Stab Defense");
        case 4: return QStringLiteral("Poison Defense");
        case 5: return QStringLiteral("Dark Magic Defense");
        case 6: return QStringLiteral("Fire Magic Defense");
        case 7: return QStringLiteral("Earth Magic Defense");
        case 8: return QStringLiteral("Wind Magic Defense");
        case 9: return QStringLiteral("Water Magic Defense");
        case 10: return QStringLiteral("Unknown 14");
        case 11: return QStringLiteral("Unknown 16");
        case 12: return QStringLiteral("Unknown 18");
        case 13: return QStringLiteral("Unknown 1A");
        case 14: return QStringLiteral("Unknown 1C");
        case 15: return QStringLiteral("Unknown 1E");
        default: return {};
    }
}

bool ArmorStatsTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;
    auto& armorStat = gameDB.getArmorStat(curArmorStat);

    auto uShortValue = Utilities::clampToUShort(value.toUInt());

    switch (index.row())
    {
        case 0: armorStat.Thingie = uShortValue; break;
        case 1: armorStat.DefSlash = uShortValue; break;
        case 2: armorStat.DefChop = uShortValue; break;
        case 3: armorStat.DefStab = uShortValue; break;
        case 4: armorStat.DefPoison = uShortValue; break;
        case 5: armorStat.DefDarkM = uShortValue; break;
        case 6: armorStat.DefFireM = uShortValue; break;
        case 7: armorStat.DefEarthM = uShortValue; break;
        case 8: armorStat.DefWindM = uShortValue; break;
        case 9: armorStat.DefWaterM = uShortValue; break;
        case 10: armorStat.field_0x14 = uShortValue; break;
        case 11: armorStat.field_0x16 = uShortValue; break;
        case 12: armorStat.field_0x18 = uShortValue; break;
        case 13: armorStat.field_0x1a = uShortValue; break;
        case 14: armorStat.field_0x1c = uShortValue; break;
        case 15: armorStat.field_0x1e = uShortValue; break;
        default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

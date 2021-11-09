#include "magictablemodel.h"

QVariant MagicTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    const auto& magic = gameDB.getMagic(curMagic);

    switch (index.row())
    {
        case 0: return QString::number(magic.PlayerHas);
        case 1: return QString::number(magic.ChargeRecoveryTime);
        case 2: return QString::number(magic.field_0x2);
        case 3: return QString::number(magic.field_0x3);
        case 4: return QString::number(magic.StatusEffect);
        case 5: return QString::number(magic.field_0x5);
        case 6: return QString::number(magic.field_0x6);
        case 7: return QString::number(magic.field_0x7);
        case 8: return QString::number(magic.SomeDmg1);
        case 9: return QString::number(magic.SomeDmg2);
        case 10: return QString::number(magic.SomeDmg3);
        case 11: return QString::number(magic.FireDmg);
        case 12: return QString::number(magic.EarthDmg);
        case 13: return QString::number(magic.WindDmg);
        case 14: return QString::number(magic.WaterDmg);
        case 15: return QString::number(magic.MPCost);
        case 16: return QString::number(magic.field_0x18);
        case 17: return QString::number(magic.field_0x19);
        default: return {};
    }
}

QVariant MagicTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):
    switch (section)
    {
        case 0: return QStringLiteral("Player Has");
        case 1: return QStringLiteral("Mag Stamina Cost");
        case 2: return QStringLiteral("Unknown 02");
        case 3: return QStringLiteral("Unknown 03");
        case 4: return QStringLiteral("Status Effect");
        case 5: return QStringLiteral("Unknown 05");
        case 6: return QStringLiteral("Unknown 06");
        case 7: return QStringLiteral("Unknown 07");
        case 8: return QStringLiteral("Some Damage 1");
        case 9: return QStringLiteral("Some Damage 2");
        case 10: return QStringLiteral("Some Damage 3");
        case 11: return QStringLiteral("Fire Damage");
        case 12: return QStringLiteral("Earth Damage");
        case 13: return QStringLiteral("Wind Damage");
        case 14: return QStringLiteral("Water Damage");
        case 15: return QStringLiteral("MP Cost");
        case 16: return QStringLiteral("Unknown 18");
        case 17: return QStringLiteral("Unknown 19");
        default: return {};
    }
}

bool MagicTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;

    auto& magic = gameDB.getMagic(curMagic);

    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    unsigned int uIntValue = 0;
    switch (index.row())
    {
        case 0:
            uIntValue = value.toUInt();
            if (uIntValue < 1)
            {
                magic.PlayerHas = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 1:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.ChargeRecoveryTime = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 2:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x2 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 3:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x3 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 4:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.StatusEffect = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 5:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x5 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 6:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x6 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 7:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x7 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;
        case 8:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.SomeDmg1 = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 9:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.SomeDmg2 = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 10:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.SomeDmg3 = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 11:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.FireDmg = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 12:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.EarthDmg = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 13:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.WindDmg = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 14:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.WaterDmg = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;

        case 15:
            uIntValue = value.toUInt();
            if (uIntValue < 65536)
            {
                magic.MPCost = static_cast<quint16>(uIntValue);
                result = true;
            }
            break;
        case 16:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x18 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;

        case 17:
            uIntValue = value.toUInt();
            if (uIntValue < 256)
            {
                magic.field_0x19 = static_cast<quint8>(uIntValue);
                result = true;
            }
            break;
    }

    if (result) emit dataChanged(index, index);

    return result;
}

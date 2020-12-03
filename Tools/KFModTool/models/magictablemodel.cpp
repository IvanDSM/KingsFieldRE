#include "magictablemodel.h"

QVariant MagicTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(spell.PlayerHas)); break;
            case 1: result.setValue(QString::number(spell.ChargeRecoveryTime)); break;
            case 2: result.setValue(QString::number(spell.field_0x2)); break;
            case 3: result.setValue(QString::number(spell.field_0x3)); break;
            case 4: result.setValue(QString::number(spell.StatusEffect)); break;
            case 5: result.setValue(QString::number(spell.field_0x5)); break;
            case 6: result.setValue(QString::number(spell.field_0x6)); break;
            case 7: result.setValue(QString::number(spell.field_0x7)); break;
            case 8: result.setValue(QString::number(spell.SomeDmg1)); break;
            case 9: result.setValue(QString::number(spell.SomeDmg2)); break;
            case 10: result.setValue(QString::number(spell.SomeDmg3)); break;
            case 11: result.setValue(QString::number(spell.FireDmg)); break;
            case 12: result.setValue(QString::number(spell.EarthDmg)); break;
            case 13: result.setValue(QString::number(spell.WindDmg)); break;
            case 14: result.setValue(QString::number(spell.WaterDmg)); break;
            case 15: result.setValue(QString::number(spell.MPCost)); break;
            case 16: result.setValue(QString::number(spell.field_0x18)); break;
            case 17: result.setValue(QString::number(spell.field_0x19)); break;
        }
    }
    return result;
}

QVariant MagicTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Player Has";
                case 1: return "Mag Stamina Cost";
                case 2: return "Unknown 02";
                case 3: return "Unknown 03";
                case 4: return "Status Effect";
                case 5: return "Unknown 05";
                case 6: return "Unknown 06";
                case 7: return "Unknown 07";
                case 8: return "Some Damage 1";
                case 9: return "Some Damage 2";
                case 10: return "Some Damage 3";
                case 11: return "Fire Damage";
                case 12: return "Earth Damage";
                case 13: return "Wind Damage";
                case 14: return "Water Damage";
                case 15: return "MP Cost";
                case 16: return "Unknown 18";
                case 17: return "Unknown 19";
            }
        }
    }
    return QVariant();
}

bool MagicTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        unsigned int uIntValue = 0;
        switch (index.row())
        {
            case 0:
                uIntValue = value.toUInt();
                if (uIntValue < 1)
                {
                    spell.PlayerHas = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 1:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.ChargeRecoveryTime = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 2:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x2 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 3:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x3 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 4:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.StatusEffect = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 5:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x5 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 6:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x6 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 7:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x7 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 8:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.SomeDmg1 = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 9:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.SomeDmg2 = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 10:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.SomeDmg3 = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 11:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.FireDmg = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 12:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.EarthDmg = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 13:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.WindDmg = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 14:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.WaterDmg = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 15:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    spell.MPCost = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;
            case 16:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x18 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 17:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    spell.field_0x19 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
        }
    }
    return result;
}

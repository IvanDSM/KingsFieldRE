#include "objectclasstablemodel.h"

QVariant ObjectClassTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(objClass.field_0x0)); break;
            case 1: result.setValue(QString::number(objClass.SomeType)); break;
            case 2: result.setValue(QString::number(objClass.field_0x2)); break;
            case 3: result.setValue(QString::number(objClass.field_0x3)); break;
            case 4: result.setValue(QString::number(objClass.CollisionRadius)); break;
            case 5: result.setValue(QString::number(objClass.field_0x6)); break;
            case 6: result.setValue(QString::number(objClass.field_0x7)); break;
            case 7: result.setValue(QString::number(objClass.field_0x8)); break;
            case 8: result.setValue(QString::number(objClass.field_0x9)); break;
            case 9: result.setValue(QString::number(objClass.field_0xa)); break;
            case 10: result.setValue(QString::number(objClass.field_0xb)); break;
            case 11: result.setValue(QString::number(objClass.field_0xc)); break;
            case 12: result.setValue(QString::number(objClass.field_0xd)); break;
            case 13: result.setValue(QString::number(objClass.field_0xe)); break;
            case 14: result.setValue(QString::number(objClass.field_0xf)); break;
            case 15: result.setValue(QString::number(objClass.field_0x10)); break;
            case 16: result.setValue(QString::number(objClass.field_0x11)); break;
            case 17: result.setValue(QString::number(objClass.field_0x12)); break;
            case 18: result.setValue(QString::number(objClass.field_0x13)); break;
            case 19: result.setValue(QString::number(objClass.field_0x14)); break;
            case 20: result.setValue(QString::number(objClass.field_0x15)); break;
            case 21: result.setValue(QString::number(objClass.field_0x16)); break;
            case 22: result.setValue(QString::number(objClass.field_0x17)); break;
        }
    }

    return result;
}

QVariant ObjectClassTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Unknown 00";
                case 1: return "Some Type";
                case 2: return "Unknown 02";
                case 3: return "Unknown 03";
                case 4: return "Collision Radius";
                case 5: return "Unknown 06";
                case 6: return "Unknown 07";
                case 7: return "Unknown 08";
                case 8: return "Unknown 09";
                case 9: return "Unknown 0A";
                case 10: return "Unknown 0B";
                case 11: return "Unknown 0C";
                case 12: return "Unknown 0D";
                case 13: return "Unknown 0E";
                case 14: return "Unknown 0F";
                case 15: return "Unknown 10";
                case 16: return "Unknown 11";
                case 17: return "Unknown 12";
                case 18: return "Unknown 13";
                case 19: return "Unknown 14";
                case 20: return "Unknown 15";
                case 21: return "Sound Effect";
                case 22: return "Unknown 17";
                default: break;
            }
        }
    }

    return QVariant();
}

bool ObjectClassTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        byte byteValue = static_cast<byte>(qMin(255u, value.toUInt()));
        u_short uShortValue = static_cast<u_short>(qMin(65535u, value.toUInt()));
        switch (index.row())
        {
            case 0: objClass.field_0x0 = byteValue; break;
            case 1: objClass.SomeType = byteValue; break;
            case 2: objClass.field_0x2 = byteValue; break;
            case 3: objClass.field_0x3 = byteValue; break;
            case 4: objClass.CollisionRadius = uShortValue; break;
            case 5: objClass.field_0x6 = byteValue; break;
            case 6: objClass.field_0x7 = byteValue; break;
            case 7: objClass.field_0x8 = byteValue; break;
            case 8: objClass.field_0x9 = byteValue; break;
            case 9: objClass.field_0xa = byteValue; break;
            case 10: objClass.field_0xb = byteValue; break;
            case 11: objClass.field_0xc = byteValue; break;
            case 12: objClass.field_0xd = byteValue; break;
            case 13: objClass.field_0xe = byteValue; break;
            case 14: objClass.field_0xf = byteValue; break;
            case 15: objClass.field_0x10 = byteValue; break;
            case 16: objClass.field_0x11 = byteValue; break;
            case 17: objClass.field_0x12 = byteValue; break;
            case 18: objClass.field_0x13 = byteValue; break;
            case 19: objClass.field_0x14 = byteValue; break;
            case 20: objClass.field_0x15 = byteValue; break;
            case 21: objClass.field_0x16 = byteValue; break;
            case 22: objClass.field_0x17 = byteValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

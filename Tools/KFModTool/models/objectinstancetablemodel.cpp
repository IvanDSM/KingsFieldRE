#include "objectinstancetablemodel.h"

QVariant ObjectInstanceTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(objInstance.TileLayer)); break;
            case 1: result.setValue(QString::number(objInstance.WEXTilePos)); break;
            case 2: result.setValue(QString::number(objInstance.NSYTilePos)); break;
            case 3: result.setValue(QString::number(objInstance.field_0x3)); break;
            case 4: result.setValue(QString::number(KingsField::getObjectIDAsByte(objInstance.ObjectID))
                                    + " ("
                                    + KingsField::getObjectName(objInstance.ObjectID) + ")"); break;
            case 5: result.setValue(QString::number(objInstance.ZRotation) + " (" +
                                    QString::number(objInstance.ZRotation * 90) + "°)"); break;
            case 6: result.setValue(QString::number(objInstance.FineWEXPos)); break;
            case 7: result.setValue(QString::number(objInstance.FineNSYPos)); break;
            case 8: result.setValue(QString::number(objInstance.FineZPos)); break;
            case 9: result.setValue(QString::number(objInstance.Flags[0])); break;
            case 10: result.setValue(QString::number(objInstance.Flags[1])); break;
            case 11: result.setValue(QString::number(objInstance.Flags[2])); break;
            case 12: result.setValue(QString::number(objInstance.Flags[3])); break;
            case 13: result.setValue(QString::number(objInstance.Flags[4])); break;
            case 14: result.setValue(QString::number(objInstance.Flags[5])); break;
            case 15: result.setValue(QString::number(objInstance.Flags[6])); break;
            case 16: result.setValue(QString::number(objInstance.Flags[7])); break;
            case 17: result.setValue(QString::number(objInstance.Flags[8])); break;
            case 18: result.setValue(QString::number(objInstance.Flags[9])); break;
        }
    }
    return result;
}

QVariant ObjectInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Tile Layer";
                case 1: return "X Tile Position";
                case 2: return "Y Tile Position";
                case 3: return "Unknown 03";
                case 4: return "Object ID";
                case 5: return "Z Rotation";
                case 6: return "Fine X Position";
                case 7: return "Fine Y Position";
                case 8: return "Fine Z Position";
                case 9: return "Flags[0]";
                case 10: return "Flags[1]";
                case 11: return "Flags[2]";
                case 12: return "Flags[3]";
                case 13: return "Flags[4]";
                case 14: return "Flags[5]";
                case 15: return "Flags[6]";
                case 16: return "Flags[7]";
                case 17: return "Flags[8]";
                case 18: return "Flags[9]";
                default: break;
            }
        }
    }

    return QVariant();
}

bool ObjectInstanceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        int intValue = 0;
        unsigned int uIntValue = 0;
        switch (index.row())
        {
            case 0:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.TileLayer = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 1:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.WEXTilePos = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 2:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.NSYTilePos = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 3:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.field_0x3 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 4:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    objInstance.ObjectID = KingsField::getObjectIDFromUShort(static_cast<unsigned short>(uIntValue));
                    result = true;
                }
                break;
            case 5:
                intValue = value.toInt();
                if (intValue > -32768 && intValue < 32767)
                {
                    objInstance.ZRotation = static_cast<short>(intValue);
                    result = true;
                }
                break;

            case 6:
                intValue = value.toInt();
                if (intValue > -32768 && intValue < 32767)
                {
                    objInstance.FineWEXPos = static_cast<short>(intValue);
                    result = true;
                }
                break;

            case 7:
                intValue = value.toInt();
                if (intValue > -32768 && intValue < 32767)
                {
                    objInstance.FineNSYPos = static_cast<short>(intValue);
                    result = true;
                }
                break;

            case 8:
                intValue = value.toInt();
                if (intValue > -32768 && intValue < 32767)
                {
                    objInstance.FineZPos = static_cast<short>(intValue);
                    result = true;
                }
                break;
            case 9:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[0] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 10:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[1] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 11:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[2] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 12:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[3] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 13:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[4] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 14:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[5] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 15:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[6] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 16:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[7] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 17:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[8] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 18:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    objInstance.Flags[9] = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
        }
    }
    return result;
}

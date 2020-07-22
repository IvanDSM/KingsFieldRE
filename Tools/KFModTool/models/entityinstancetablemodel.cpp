#include "entityinstancetablemodel.h"

QVariant EntityInstanceTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(entityInstance.field_0x0)); break;
            case 1: result.setValue(QString::number(entityInstance.EntityClass)); break;
            case 2: result.setValue(QString::number(entityInstance.field_0x2)); break;
            case 3: result.setValue(QString::number(entityInstance.WEXTilePos)); break;
            case 4: result.setValue(QString::number(entityInstance.NSYTilePos)); break;
            case 5: result.setValue(QString::number(entityInstance.field_0x5)); break;
            case 6: result.setValue(QString::number(KingsField::getObjectIDAsByte(entityInstance.DroppedItem)) + " ("
                                + KingsField::getObjectName(entityInstance.DroppedItem) + ")");
                break;
            case 7: result.setValue(QString::number(entityInstance.Layer)); break;
            case 8: result.setValue(QString::number(entityInstance.TriggerObject)); break;
            case 9: result.setValue(QString::number(entityInstance.ZRotation) + " ("
                                + QString::number(entityInstance.ZRotation * 90)
                                + "°)"); break;
            case 10: result.setValue(QString::number(entityInstance.FineWEXPos)); break;
            case 11: result.setValue(QString::number(entityInstance.FineNSYPos)); break;
            case 12: result.setValue(QString::number(entityInstance.FineZPos)); break;
        }
    }

    return result;
}

QVariant EntityInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                case 1: return "Entity Class";
                case 2: return "Unknown 02";
                case 3: return "X Tile Position";
                case 4: return "Y Tile Position";
                case 5: return "Unknown 05";
                case 6: return "Dropped Item";
                case 7: return "Layer";
                case 8: return "Trigger Object";
                case 9: return "Z Rotation";
                case 10: return "Fine X Position";
                case 11: return "Fine Y Position";
                case 12: return "Fine Z Position";
            }
        }
    }

    return QVariant();
}

bool EntityInstanceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;

    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        unsigned int uIntValue = 0;
        int intValue = 0;
        switch (index.row())
        {
            case 0:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.field_0x0 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 1:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.EntityClass = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 2:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.field_0x2 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 3:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.WEXTilePos = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 4:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.NSYTilePos = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 5:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.field_0x5 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 6:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.DroppedItem = static_cast<KingsField::ObjectID>(uIntValue);
                    result = true;
                }
                break;
            case 7:
                uIntValue = value.toUInt();
                if (uIntValue == 1 || uIntValue == 2)
                {
                    entityInstance.Layer = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 8:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityInstance.TriggerObject = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 9:
                uIntValue = value.toUInt();
                if (uIntValue >= 90 && uIntValue <= 360)
                {
                    if (uIntValue == 360)
                        uIntValue = 0;
                    else
                        uIntValue /= 90;
                }
                if (uIntValue < 4)
                {
                    entityInstance.ZRotation = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 10:
                intValue = value.toInt();
                if (intValue < 65536)
                {
                    entityInstance.FineWEXPos = static_cast<short>(intValue);
                    result = true;
                }
                break;
            case 11:
                intValue = value.toInt();
                if (intValue < 65536)
                {
                    entityInstance.FineNSYPos = static_cast<short>(intValue);
                    result = true;
                }
                break;
            case 12:
                intValue = value.toInt();
                if (intValue < 65536)
                {
                    entityInstance.FineZPos = static_cast<short>(intValue);
                    result = true;
                }
                break;
        }
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

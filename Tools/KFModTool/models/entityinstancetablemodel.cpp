#include "entityinstancetablemodel.h"

QVariant EntityInstanceTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        static constexpr std::array<const char *, 2> nonRandomStr = {"Random", "Non-Random"};
        switch (index.row())
        {
            case 0: result.setValue(QString::number(entityInstance.RespawnMode)); break;
            case 1: result.setValue(QString::number(entityInstance.EntityClass)); break;
            case 2: result.setValue(QString::number(entityInstance.NonRandomRotation) + " ("
                                    + nonRandomStr.at(entityInstance.NonRandomRotation) + ")"); break;
            case 3: result.setValue(QString::number(entityInstance.WEXTilePos)); break;
            case 4: result.setValue(QString::number(entityInstance.NSYTilePos)); break;
            case 5: result.setValue(QString::number(entityInstance.RespawnChance)); break;
            case 6: result.setValue(QString::number(KingsField::getObjectIDAsByte(entityInstance.DroppedItem)) + " ("
                                + KingsField::getObjectName(entityInstance.DroppedItem) + ")");
                break;
            case 7: result.setValue(QString::number(entityInstance.Layer)); break;
            case 8: result.setValue(QString::number(entityInstance.ZRotation) + " ("
                                + QString::number(entityInstance.ZRotation * KingsField::rotationCoefficient)
                                + "°)"); break;
            case 9: result.setValue(QString::number(entityInstance.FineWEXPos)); break;
            case 10: result.setValue(QString::number(entityInstance.FineNSYPos)); break;
            case 11: result.setValue(QString::number(entityInstance.FineZPos)); break;
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
                case 0: return "Respawn Mode";
                case 1: return "Entity Class";
                case 2: return "Non-Random Z Rot.";
                case 3: return "X Tile Position";
                case 4: return "Y Tile Position";
                case 5: return "Respawn Chance";
                case 6: return "Dropped Item";
                case 7: return "Layer";
                case 8: return "Z Rotation";
                case 9: return "Fine X Position";
                case 10: return "Fine Y Position";
                case 11: return "Fine Z Position";
                default: break;
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
        short shortValue = qMax(-32767, qMin(32767, value.toInt()));
        u_short uShortValue = qMin(65535u, value.toUInt());
        byte byteValue = qMin(255u, value.toUInt());
        bool boolValue = qMin(1u, value.toUInt());
        switch (index.row())
        {
            case 0: entityInstance.RespawnMode = byteValue; break;
            case 1: entityInstance.EntityClass = byteValue; break;
            case 2: entityInstance.NonRandomRotation = boolValue; break;
            case 3: entityInstance.WEXTilePos = byteValue; break;
            case 4: entityInstance.NSYTilePos = byteValue; break;
            case 5: entityInstance.RespawnChance = byteValue; break;
            case 6: entityInstance.DroppedItem = static_cast<KingsField::ObjectID>(uShortValue); break;
            case 7: entityInstance.Layer = byteValue; break;
            case 8:
                if (value.toString().right(1) == "°" || value.toString().right(1) == "º" ||
                    value.toString().right(1) == "ª")
                    uShortValue = value.toString().chopped(1).toUInt() / KingsField::rotationCoefficient;
                else
                    uShortValue = value.toUInt() % 4096;
                entityInstance.ZRotation = uShortValue;
                break;
            case 9: entityInstance.FineWEXPos = shortValue; break;
            case 10: entityInstance.FineNSYPos = shortValue; break;
            case 11: entityInstance.FineZPos = shortValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

#include "vfxinstancetablemodel.h"
#include "utilities.h"

QVariant VFXInstanceTableModel::data(const QModelIndex & index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(vfxInstance.field_0x0)); break;
            case 1: result.setValue(QString::number(vfxInstance.field_0x1)); break;
            case 2: result.setValue(QString::number(vfxInstance.field_0x2)); break;
            case 3: result.setValue(QString::number(vfxInstance.field_0x3)); break;
            case 4: result.setValue(QString::number(vfxInstance.TileLayer)); break;
            case 5: result.setValue(QString::number(vfxInstance.TileWEX)); break;
            case 6: result.setValue(QString::number(vfxInstance.TileNSY)); break;
            case 7: result.setValue(QString::number(vfxInstance.field_0x7)); break;
            case 8: result.setValue(QString::number(vfxInstance.field_0x8)); break;
            case 9: result.setValue(QString::number(vfxInstance.field_0x9)); break;
            case 10: result.setValue(QString::number(vfxInstance.FineXPos)); break;
            case 11: result.setValue(QString::number(vfxInstance.FineYPos)); break;
            case 12: result.setValue(QString::number(vfxInstance.FineZPos)); break;
        }
    }

    return result;
}

QVariant VFXInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                case 1: return "Unknown 01";
                case 2: return "Unknown 02";
                case 3: return "Unknown 03";
                case 4: return "Tile Layer";
                case 5: return "X Tile Position";
                case 6: return "Y Tile Position";
                case 7: return "Unknown 07";
                case 8: return "Unknown 08";
                case 9: return "Unknown 09";
                case 10: return "Fine X Position";
                case 11: return "Fine Y Position";
                case 12: return "Fine Z Position";
            }
        }
    }

    return QVariant();
}

bool VFXInstanceTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    bool result = false;

    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        short shortValue = Utilities::clampToShort(value.toInt());
        byte byteValue = Utilities::clampToByte(value.toUInt());

        switch (index.row())
        {
            case 0: vfxInstance.field_0x0 = byteValue; break;
            case 1: vfxInstance.field_0x1 = byteValue; break;
            case 2: vfxInstance.field_0x2 = byteValue; break;
            case 3: vfxInstance.field_0x3 = byteValue; break;
            case 4: vfxInstance.TileLayer = byteValue; break;
            case 5: vfxInstance.TileWEX = byteValue; break;
            case 6: vfxInstance.TileNSY = byteValue; break;
            case 7: vfxInstance.field_0x7 = byteValue; break;
            case 8: vfxInstance.field_0x8 = byteValue; break;
            case 9: vfxInstance.field_0x9 = byteValue; break;
            case 10: vfxInstance.FineXPos = shortValue; break;
            case 11: vfxInstance.FineYPos = shortValue; break;
            case 12: vfxInstance.FineZPos = shortValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

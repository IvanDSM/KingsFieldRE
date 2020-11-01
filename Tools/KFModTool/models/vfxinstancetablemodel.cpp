#include "vfxinstancetablemodel.h"
#include "utilities.h"

QVariant VFXInstanceTableModel::data(const QModelIndex & index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(vfxInstance.VFXID)); break;
            case 1: result.setValue(QString::number(vfxInstance.AnimFrameCount)); break;
            case 2: result.setValue(QString::number(vfxInstance.AnimSpeed)); break;
            case 3: result.setValue(QString::number(vfxInstance.TileLayer)); break;
            case 4: result.setValue(QString::number(vfxInstance.TileWEX)); break;
            case 5: result.setValue(QString::number(vfxInstance.TileNSY)); break;
            case 6: result.setValue(QString::number(vfxInstance.field_0x7)); break;
            case 7: result.setValue(QString::number(vfxInstance.field_0x8)); break;
            case 8: result.setValue(QString::number(vfxInstance.field_0x9)); break;
            case 9: result.setValue(QString::number(vfxInstance.FineXPos)); break;
            case 10: result.setValue(QString::number(vfxInstance.FineYPos)); break;
            case 11: result.setValue(QString::number(vfxInstance.FineZPos)); break;
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
                case 0: return "VFX ID";
                case 1: return "Animation Frame Count";
                case 2: return "Animation Speed";
                case 3: return "Tile Layer";
                case 4: return "X Tile Position";
                case 5: return "Y Tile Position";
                case 6: return "Unknown 07";
                case 7: return "Unknown 08";
                case 8: return "Unknown 09";
                case 9: return "Fine X Position";
                case 10: return "Fine Y Position";
                case 11: return "Fine Z Position";
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
        auto uShortValue = Utilities::clampToUShort(value.toUInt());
        auto shortValue = Utilities::clampToShort(value.toInt());
        auto byteValue = Utilities::clampToByte(value.toUInt());

        switch (index.row())
        {
            case 0: vfxInstance.VFXID = uShortValue; break;
            case 1: vfxInstance.AnimFrameCount = byteValue; break;
            case 2: vfxInstance.AnimSpeed = byteValue; break;
            case 3: vfxInstance.TileLayer = byteValue; break;
            case 4: vfxInstance.TileWEX = byteValue; break;
            case 5: vfxInstance.TileNSY = byteValue; break;
            case 6: vfxInstance.field_0x7 = byteValue; break;
            case 7: vfxInstance.field_0x8 = byteValue; break;
            case 8: vfxInstance.field_0x9 = byteValue; break;
            case 9: vfxInstance.FineXPos = shortValue; break;
            case 10: vfxInstance.FineYPos = shortValue; break;
            case 11: vfxInstance.FineZPos = shortValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

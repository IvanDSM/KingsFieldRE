#include "entitystatetablemodel.h"

QVariant EntityStateTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "State ID";
                case 1: return "Animation?";
                case 8: return "Look At Margin? Low Byte";
                case 9: return "Look At Margin? High Byte";
                case 10: return "Tick Something? Low Byte";
                case 11: return "Tick Something? Low Byte";
                case 12: 
                    if (*statePointer == 0x70)
                        return "Dialogue Base Low Byte";
                    return "Walk Speed Low Byte";
                case 13: 
                    if (*statePointer == 0x70)
                        return "Dialogue Base High Byte";
                    return "Walk Speed High Byte";
                case 14: return "Turn Speed Low Byte";
                case 15: return "Turn Speed High Byte";
                default:
                    return QString::asprintf("Unknown %x", section);
            }
        }
    }

    return QVariant();
}

int EntityStateTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    switch (*statePointer)
    {
        case 0x00:
            return 12;
        case 0x01:
        case 0x0A:
            return 18;
        case 0x02:
        case 0x03:
        case 0x0E:
            return 14;
        case 0x04:
            return 28;
        case 0x05:
        case 0x0D:
            return 26;
        case 0x0C:
            return 20;
        case 0x17:
            return 44;
        case 0x70:
            return 66;
        case 0x80:
            return 32;
        default:
            return 28;
    }
}

QVariant EntityStateTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || statePointer == nullptr || role != Qt::DisplayRole)
        return QVariant();
    
    return QString::asprintf("%02x", *(statePointer + index.row()));
}

bool EntityStateTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (statePointer != nullptr && data(index, role) != value) 
    {
        *(statePointer + index.row()) = static_cast<uint8_t>(value.toUInt());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}


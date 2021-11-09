#include "entitystatetablemodel.h"
#include "games/kf2.h"

QVariant EntityStateTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) return QStringLiteral("Value");

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return QStringLiteral("State ID");
                case 1: return QStringLiteral("Animation");
                case 4: return QStringLiteral("Entity Sound Effect");
                case 8: return QStringLiteral("Look At Margin? Low Byte");
                case 9: return QStringLiteral("Look At Margin? High Byte");
                case 10: return QStringLiteral("Tick Something? Low Byte");
                case 11: return QStringLiteral("Tick Something? High Byte");
                case 12:
                    if (*statePointer == 0x70) return QStringLiteral("Dialogue Base Low Byte");
                    return QStringLiteral("Walk Speed Low Byte");
                case 13:
                    if (*statePointer == 0x70) return QStringLiteral("Dialogue Base High Byte");
                    return QStringLiteral("Walk Speed High Byte");
                case 14: return QStringLiteral("Turn Speed Low Byte");
                case 15: return QStringLiteral("Turn Speed High Byte");
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
    
    if (index.row() == 0)
    {
        auto stateId = KingsFieldII::getEntityStateIDFromByte(*statePointer);
        auto stateName = KingsFieldII::getEntityStateIDName(stateId).toStdString();
        return QString::asprintf("%02x (%s)", *statePointer, stateName.c_str());
    }
                
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


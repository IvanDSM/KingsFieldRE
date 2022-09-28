#include "entityinstancetablemodel.h"
#include "platform/psx.h"

static const auto random_ = QStringLiteral(" (Random)");
static const auto nonrandom_ = QStringLiteral(" (Non-Random)");
static const auto invalid_ = QStringLiteral(" (Invalid Value)");

inline const QString& getNonRandomStr(const uint8_t& value)
{
    switch (value)
    {
        case 0: return random_;
        case 1: return nonrandom_;
        default: return invalid_;
    }
}

QVariant EntityInstanceTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    switch (index.row())
    {
        case 0: return QString::number(entity->RespawnMode); break;
        case 1: return QString::number(entity->EntityClass); break;
        case 2:
            return QString::number(entity->NonRandomRotation)
                   + getNonRandomStr(entity->NonRandomRotation);
            break;
        case 3: return QString::number(entity->WEXTilePos); break;
        case 4: return QString::number(entity->NSYTilePos); break;
        case 5: return QString::number(entity->RespawnChance); break;
        case 6:
            return QString::number(static_cast<uint16_t>(entity->DroppedItem)) + " ("
                   + KF2::getObjectName(entity->DroppedItem) + ")";
            break;
        case 7: return QString::number(entity->Layer); break;
        case 8:
            return QString::number(entity->ZRotation) + " ("
                   + QString::number(PSX::fromAngle(entity->ZRotation)) + "°)";
            break;
        case 9: return QString::number(entity->FineWEXPos); break;
        case 10: return QString::number(entity->FineNSYPos); break;
        case 11: return QString::number(entity->FineZPos); break;
    }

    return {};
}

QVariant EntityInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) return QStringLiteral("Value");

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return QStringLiteral("Respawn Mode");
                case 1: return QStringLiteral("Entity Class");
                case 2: return QStringLiteral("Non-Random Z Rot.");
                case 3: return QStringLiteral("X Tile Position");
                case 4: return QStringLiteral("Y Tile Position");
                case 5: return QStringLiteral("Respawn Chance");
                case 6: return QStringLiteral("Dropped Item");
                case 7: return QStringLiteral("Layer");
                case 8: return QStringLiteral("Z Rotation");
                case 9: return QStringLiteral("Fine X Position");
                case 10: return QStringLiteral("Fine Y Position");
                case 11: return QStringLiteral("Fine Z Position");
                default: break;
            }
        }
    }

    return QVariant();
}

bool EntityInstanceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    short shortValue = qMax(-32767, qMin(32767, value.toInt()));
    uint16_t uShortValue = qMin(65535u, value.toUInt());
    uint8_t byteValue = qMin(255u, value.toUInt());
    bool boolValue = qMin(1u, value.toUInt());

    switch (index.row())
    {
        case 0: entity->RespawnMode = byteValue; break;
        case 1: entity->EntityClass = byteValue; break;
        case 2: entity->NonRandomRotation = boolValue; break;
        case 3: entity->WEXTilePos = byteValue; break;
        case 4: entity->NSYTilePos = byteValue; break;
        case 5: entity->RespawnChance = byteValue; break;
        case 6: entity->DroppedItem = static_cast<KF2::ObjectID>(uShortValue); break;
        case 7: entity->Layer = byteValue; break;
        case 8:
            if (value.toString().right(1) == "°" || value.toString().right(1) == "º"
                || value.toString().right(1) == "ª")
                uShortValue = PSX::toAngle(value.toString().chopped(1).toUInt());
            else
                uShortValue = value.toUInt() % 4096;
            entity->ZRotation = uShortValue;
            break;
        case 9: entity->FineWEXPos = shortValue; break;
        case 10: entity->FineNSYPos = shortValue; break;
        case 11: entity->FineZPos = shortValue; break;
    }

    emit dataChanged(index, index);

    return true;
}

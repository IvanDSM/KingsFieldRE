#include "objectinstancetablemodel.h"
#include "platform/psx.h"
#include "utilities.h"

QVariant ObjectInstanceTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) return {};
    if (!index.isValid()) return {};

    switch (index.row())
    {
        case 0: return QString::number(object->TileLayer);
        case 1: return QString::number(object->WEXTilePos);
        case 2: return QString::number(object->NSYTilePos);
        case 3: return QString::number(object->field_0x3);
        case 4:
            return QString::number(static_cast<uint8_t>(object->ID)) + " ("
                   + KF2::getObjectName(object->ID) + ")";
        case 5:
            return QString::number(object->ZRotation) + " ("
                   + QString::number(PSX::fromAngle(object->ZRotation)) + "°)";
        case 6: return QString::number(object->FineWEXPos);
        case 7: return QString::number(object->FineNSYPos);
        case 8: return QString::number(object->FineZPos);
        case 9: return QString::number(object->Flags[0]);
        case 10: return QString::number(object->Flags[1]);
        case 11: return QString::number(object->Flags[2]);
        case 12: return QString::number(object->Flags[3]);
        case 13: return QString::number(object->Flags[4]);
        case 14: return QString::number(object->Flags[5]);
        case 15: return QString::number(object->Flags[6]);
        case 16: return QString::number(object->Flags[7]);
        case 17: return QString::number(object->Flags[8]);
        case 18: return QString::number(object->Flags[9]);
        default: return {};
    }
}

QVariant ObjectInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    // if (orientation == Qt::Vertical):
    if (section > 8 && section < 19) return getFlagLabel(section - 9);
    switch (section)
    {
        case 0: return QStringLiteral("Tile Layer");
        case 1: return QStringLiteral("X Tile Position");
        case 2: return QStringLiteral("Y Tile Position");
        case 3: return QStringLiteral("Unknown 03");
        case 4: return QStringLiteral("Object ID");
        case 5: return QStringLiteral("Z Rotation");
        case 6: return QStringLiteral("Fine X Position");
        case 7: return QStringLiteral("Fine Y Position");
        case 8: return QStringLiteral("Fine Z Position");
        default: return {};
    }
}

bool ObjectInstanceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    auto intValue = value.toInt();
    auto uShortValue = Utilities::clampToUShort(value.toUInt());
    switch (index.row())
    {
        case 0: object->TileLayer = Utilities::clampToByte(value.toUInt()); break;
        case 1: object->WEXTilePos = Utilities::clampToByte(value.toUInt()); break;
        case 2: object->NSYTilePos = Utilities::clampToByte(value.toUInt()); break;
        case 3: object->field_0x3 = Utilities::clampToByte(value.toUInt()); break;
        case 4: object->ID = static_cast<KF2::ObjectID>(value.toUInt()); break;
        case 5:
            if (value.toString().right(1) == "°" || value.toString().right(1) == "º"
                || value.toString().right(1) == "ª")
                uShortValue = static_cast<uint16_t>(PSX::toAngle(value.toString().chopped(1).toUInt()));
            else
                uShortValue %= 4096;
            object->ZRotation = uShortValue;
            break;

        case 6: object->FineWEXPos = Utilities::clampToShort(intValue); break;
        case 7: object->FineNSYPos = Utilities::clampToShort(intValue); break;
        case 8: object->FineZPos = Utilities::clampToShort(intValue); break;
        case 9: object->Flags[0] = Utilities::clampToByte(value.toUInt()); break;
        case 10: object->Flags[1] = Utilities::clampToByte(value.toUInt()); break;
        case 11: object->Flags[2] = Utilities::clampToByte(value.toUInt()); break;
        case 12: object->Flags[3] = Utilities::clampToByte(value.toUInt()); break;
        case 13: object->Flags[4] = Utilities::clampToByte(value.toUInt()); break;
        case 14: object->Flags[5] = Utilities::clampToByte(value.toUInt()); break;
        case 15: object->Flags[6] = Utilities::clampToByte(value.toUInt()); break;
        case 16: object->Flags[7] = Utilities::clampToByte(value.toUInt()); break;
        case 17: object->Flags[8] = Utilities::clampToByte(value.toUInt()); break;
        case 18: object->Flags[9] = Utilities::clampToByte(value.toUInt()); break;
    }
    return true;
}

QString ObjectInstanceTableModel::getFlagLabel(unsigned int flagNo) const
{
    // TODO: Think about how to bring this back. This is hard because we don't receive the map
    // anymore.
    //switch (objClass.ClassType)
    //{
    //    case KF2::ObjectClassType::VerticalDoor2:
    //        if (flagNo < 2u || flagNo == 7) break;
    //        switch (flagNo)
    //        {
    //            case 2: return QStringLiteral("Key Item ID");
    //            case 3: return QStringLiteral("Some Tile A X");
    //            case 4: return QStringLiteral("Some Tile A Y");
    //            case 5: return QStringLiteral("Some Tile B X");
    //            case 6: return QStringLiteral("Some Tile B Y");
    //            case 8: return QStringLiteral("Message ID for Wrong Key");
    //            case 9: return QStringLiteral("Message ID when Locked");
    //        }

    //        default: break;
    //    }

    return QStringLiteral("Flag %1").arg(flagNo);
}

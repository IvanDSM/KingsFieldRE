#include "objectclasstablemodel.h"

QVariant ObjectClassTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    const auto& objectClass = gameDB.getObjClass(curObjectClass);

    switch (index.row())
    {
        case 0:
            return QString::number(objectClass.ClassType) + " ("
                   + KingsFieldII::getObjectClassTypeName(objectClass.ClassType) + ')';
        case 1: return QString::number(objectClass.TransformType);
        case 2: return QString::number(objectClass.field_0x2);
        case 3: return QString::number(objectClass.field_0x3);
        case 4: return QString::number(objectClass.CollisionRadius);
        case 5: return QString::number(objectClass.field_0x6);
        case 6: return QString::number(objectClass.field_0x7);
        case 7: return QString::number(objectClass.field_0x8);
        case 8: return QString::number(objectClass.field_0x9);
        case 9: return QString::number(objectClass.field_0xa);
        case 10: return QString::number(objectClass.field_0xb);
        case 11: return QString::number(objectClass.field_0xc);
        case 12: return QString::number(objectClass.field_0xd);
        case 13: return QString::number(objectClass.field_0xe);
        case 14: return QString::number(objectClass.field_0xf);
        case 15: return QString::number(objectClass.field_0x10);
        case 16: return QString::number(objectClass.field_0x11);
        case 17: return QString::number(objectClass.field_0x12);
        case 18: return QString::number(objectClass.field_0x13);
        case 19: return QString::number(objectClass.field_0x14);
        case 20: return QString::number(objectClass.field_0x15);
        case 21: return QString::number(objectClass.field_0x16);
        case 22: return QString::number(objectClass.field_0x17);
        default: return {};
    }
}

QVariant ObjectClassTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):
    switch (section)
    {
        case 0: return QStringLiteral("Class Type");
        case 1: return QStringLiteral("Transform Type");
        case 2: return QStringLiteral("Unknown 02");
        case 3: return QStringLiteral("Unknown 03");
        case 4: return QStringLiteral("Collision Radius");
        case 5: return QStringLiteral("Unknown 06");
        case 6: return QStringLiteral("Unknown 07");
        case 7: return QStringLiteral("Unknown 08");
        case 8: return QStringLiteral("Unknown 09");
        case 9: return QStringLiteral("Unknown 0A");
        case 10: return QStringLiteral("Unknown 0B");
        case 11: return QStringLiteral("Unknown 0C");
        case 12: return QStringLiteral("Unknown 0D");
        case 13: return QStringLiteral("Unknown 0E");
        case 14: return QStringLiteral("Unknown 0F");
        case 15: return QStringLiteral("Unknown 10");
        case 16: return QStringLiteral("Unknown 11");
        case 17: return QStringLiteral("Unknown 12");
        case 18: return QStringLiteral("Unknown 13");
        case 19: return QStringLiteral("Unknown 14");
        case 20: return QStringLiteral("Unknown 15");
        case 21: return QStringLiteral("Sound Effect");
        case 22: return QStringLiteral("Unknown 17");
        default: return {};
    }
}

bool ObjectClassTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    auto& objectClass = gameDB.getObjClass(curObjectClass);

    byte byteValue = static_cast<byte>(qMin(255u, value.toUInt()));
    u_short uShortValue = static_cast<u_short>(qMin(65535u, value.toUInt()));
    switch (index.row())
    {
        case 0:
            objectClass.ClassType = static_cast<KingsFieldII::ObjectClassType>(byteValue);
            break;
        case 1: objectClass.TransformType = byteValue; break;
        case 2: objectClass.field_0x2 = byteValue; break;
        case 3: objectClass.field_0x3 = byteValue; break;
        case 4: objectClass.CollisionRadius = uShortValue; break;
        case 5: objectClass.field_0x6 = byteValue; break;
        case 6: objectClass.field_0x7 = byteValue; break;
        case 7: objectClass.field_0x8 = byteValue; break;
        case 8: objectClass.field_0x9 = byteValue; break;
        case 9: objectClass.field_0xa = byteValue; break;
        case 10: objectClass.field_0xb = byteValue; break;
        case 11: objectClass.field_0xc = byteValue; break;
        case 12: objectClass.field_0xd = byteValue; break;
        case 13: objectClass.field_0xe = byteValue; break;
        case 14: objectClass.field_0xf = byteValue; break;
        case 15: objectClass.field_0x10 = byteValue; break;
        case 16: objectClass.field_0x11 = byteValue; break;
        case 17: objectClass.field_0x12 = byteValue; break;
        case 18: objectClass.field_0x13 = byteValue; break;
        case 19: objectClass.field_0x14 = byteValue; break;
        case 20: objectClass.field_0x15 = byteValue; break;
        case 21: objectClass.field_0x16 = byteValue; break;
        case 22: objectClass.field_0x17 = byteValue; break;
        default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

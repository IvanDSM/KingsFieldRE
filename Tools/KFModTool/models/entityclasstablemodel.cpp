#include "entityclasstablemodel.h"

const QString EntityClassTableModel::nullStr = QStringLiteral("Null");

QVariant EntityClassTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    switch (index.row())
    {
        case 0:
            return QString::number(static_cast<uint8_t>(entityClass->MeshID)) + " ("
                   + KF2::getEntityMeshName(entityClass->MeshID) + ')';
            break;
        case 1: return QString::number(entityClass->FourOrForty); break;
        case 2: return QString::number(entityClass->field_0x2); break;
        case 3: return QString::number(entityClass->KnockbackResistance); break;
        case 4: return QString::number(entityClass->field_0x5); break;
        case 5: return QString::number(entityClass->Unknown_x07); break;
        case 6: return QString::number(entityClass->Unknown_x08); break;
        case 7: return QString::number(entityClass->field_0x9); break;
        case 8: return QString::number(entityClass->SpawnDistance); break;
        case 9: return QString::number(entityClass->DespawnDistance); break;
        case 10: return QString::number(entityClass->SomethingX); break;
        case 11: return QString::number(entityClass->SomethingY); break;
        case 12: return QString::number(entityClass->SomethingZ); break;
        case 13: return QString::number(entityClass->Unknown_x12); break;
        case 14: return QString::number(entityClass->Unknown_x14); break;
        case 15: return QString::number(entityClass->LookingAtMargin1); break;
        case 16: return QString::number(entityClass->LookingAtMargin2); break;
        case 17: return QString::number(entityClass->HP); break;
        case 18: return QString::number(entityClass->Unknown_x1c); break;
        case 19: return QString::number(entityClass->ExperienceGain); break;
        case 20: return QString::number(entityClass->DefSlash); break;
        case 21: return QString::number(entityClass->DefChop); break;
        case 22: return QString::number(entityClass->DefStab); break;
        case 23: return QString::number(entityClass->DefHolyMagic); break;
        case 24: return QString::number(entityClass->DefFireMagic); break;
        case 25: return QString::number(entityClass->DefEarthMagic); break;
        case 26: return QString::number(entityClass->DefWindMagic); break;
        case 27: return QString::number(entityClass->DefWaterMagic); break;
        case 28: return QString::number(entityClass->GoldSomething); break;
        case 29: return QString::number(entityClass->Scale); break;
        case 30: return QString::number(entityClass->UknBitField34); break;
        case 31: return getSomePointer(0); break;
        case 32: return getSomePointer(1); break;
        case 33: return getSomePointer(2); break;
        case 34: return getSomePointer(3); break;
        case 35: return getSomePointer(4); break;
        case 36: return getSomePointer(5); break;
        case 37: return getSomePointer(6); break;
        case 38: return getSomePointer(7); break;
        case 39: return getSomePointer(8); break;
        case 40: return getSomePointer(9); break;
        case 41: return getSomePointer(10); break;
        case 42: return getSomePointer(11); break;
        case 43: return getSomePointer(12); break;
        case 44: return getSomePointer(13); break;
        case 45: return getSomePointer(14); break;
        case 46: return getSomePointer(15); break;
    }
    return {};
}

QVariant EntityClassTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) return QStringLiteral("Value");

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return QStringLiteral("Mesh ID");
                case 1: return QStringLiteral("Four Or Forty");
                case 2: return QStringLiteral("Unknown 02");
                case 3: return QStringLiteral("Knockback Resistance");
                case 4: return QStringLiteral("Unknown 05");
                case 5: return QStringLiteral("Unknown 07");
                case 6: return QStringLiteral("Unknown 08");
                case 7: return QStringLiteral("Unknown 09");
                case 8: return QStringLiteral("Spawn Distance");
                case 9: return QStringLiteral("Despawn Distance");
                case 10: return QStringLiteral("Something X");
                case 11: return QStringLiteral("Something Y");
                case 12: return QStringLiteral("Something Z");
                case 13: return QStringLiteral("Unknown 12");
                case 14: return QStringLiteral("Unknown 14");
                case 15: return QStringLiteral("\"Looking At\" Margin 1");
                case 16: return QStringLiteral("\"Looking At\" Margin 2");
                case 17: return QStringLiteral("HP");
                case 18: return QStringLiteral("Unknown 1C");
                case 19: return QStringLiteral("Experience Gain");
                case 20: return QStringLiteral("Slash Def");
                case 21: return QStringLiteral("Chop Def");
                case 22: return QStringLiteral("Stab Def");
                case 23: return QStringLiteral("Holy Magic Def");
                case 24: return QStringLiteral("Fire Magic Def");
                case 25: return QStringLiteral("Earth Magic Def");
                case 26: return QStringLiteral("Wind Magic Def");
                case 27: return QStringLiteral("Water Magic Def");
                case 28: return QStringLiteral("Gold Something");
                case 29: return QStringLiteral("Scale");
                case 30: return QStringLiteral("Unk. Bitfield 34");
                case 31: return QStringLiteral("SomePointers[0]");
                case 32: return QStringLiteral("SomePointers[1]");
                case 33: return QStringLiteral("SomePointers[2]");
                case 34: return QStringLiteral("SomePointers[3]");
                case 35: return QStringLiteral("SomePointers[4]");
                case 36: return QStringLiteral("SomePointers[5]");
                case 37: return QStringLiteral("SomePointers[6]");
                case 38: return QStringLiteral("SomePointers[7]");
                case 39: return QStringLiteral("SomePointers[8]");
                case 40: return QStringLiteral("SomePointers[9]");
                case 41: return QStringLiteral("SomePointers[10]");
                case 42: return QStringLiteral("SomePointers[11]");
                case 43: return QStringLiteral("SomePointers[12]");
                case 44: return QStringLiteral("SomePointers[13]");
                case 45: return QStringLiteral("SomePointers[14]");
                case 46: return QStringLiteral("SomePointers[15]");
                default: break;
            }
        }
    }
    return QVariant();
}

bool EntityClassTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    short shortValue = qMax(-32767, qMin(32767, value.toInt()));
    uint16_t uShortValue = qMin(65535u, value.toUInt());
    uint8_t byteValue = qMin(255u, value.toUInt());
    unsigned int uIntValue = value.toUInt();

    switch (index.row())
    {
        case 0: entityClass->MeshID = static_cast<KF2::EntityMeshID>(byteValue); break;
        case 1: entityClass->FourOrForty = byteValue; break;
        case 2: entityClass->field_0x2 = byteValue; break;
        case 3: entityClass->KnockbackResistance = uShortValue; break;
        case 4: entityClass->field_0x5 = uShortValue; break;
        case 5: entityClass->Unknown_x07 = byteValue; break;
        case 6: entityClass->Unknown_x08 = byteValue; break;
        case 7: entityClass->field_0x9 = byteValue; break;
        case 8: entityClass->SpawnDistance = byteValue; break;
        case 9: entityClass->DespawnDistance = byteValue; break;
        case 10: entityClass->SomethingX = shortValue; break;
        case 11: entityClass->SomethingY = shortValue; break;
        case 12: entityClass->SomethingZ = shortValue; break;
        case 13: entityClass->Unknown_x12 = uShortValue; break;
        case 14: entityClass->Unknown_x14 = uShortValue; break;
        case 15: entityClass->LookingAtMargin1 = shortValue; break;
        case 16: entityClass->LookingAtMargin2 = shortValue; break;
        case 17: entityClass->HP = uShortValue; break;
        case 18: entityClass->Unknown_x1c = uShortValue; break;
        case 19: entityClass->ExperienceGain = uShortValue; break;
        case 20: entityClass->DefSlash = uShortValue; break;
        case 21: entityClass->DefChop = uShortValue; break;
        case 22: entityClass->DefStab = uShortValue; break;
        case 23: entityClass->DefHolyMagic = uShortValue; break;
        case 24: entityClass->DefFireMagic = uShortValue; break;
        case 25: entityClass->DefEarthMagic = uShortValue; break;
        case 26: entityClass->DefWindMagic = uShortValue; break;
        case 27: entityClass->DefWaterMagic = uShortValue; break;
        case 28: entityClass->GoldSomething = uShortValue; break;
        case 29: entityClass->Scale = shortValue; break;
        case 30: entityClass->UknBitField34 = uIntValue; break;
        case 31: entityClass->SomePointers[0] = uIntValue; break;
        case 32: entityClass->SomePointers[1] = uIntValue; break;
        case 33: entityClass->SomePointers[2] = uIntValue; break;
        case 34: entityClass->SomePointers[3] = uIntValue; break;
        case 35: entityClass->SomePointers[4] = uIntValue; break;
        case 36: entityClass->SomePointers[5] = uIntValue; break;
        case 37: entityClass->SomePointers[6] = uIntValue; break;
        case 38: entityClass->SomePointers[7] = uIntValue; break;
        case 39: entityClass->SomePointers[8] = uIntValue; break;
        case 40: entityClass->SomePointers[9] = uIntValue; break;
        case 41: entityClass->SomePointers[10] = uIntValue; break;
        case 42: entityClass->SomePointers[11] = uIntValue; break;
        case 43: entityClass->SomePointers[12] = uIntValue; break;
        case 44: entityClass->SomePointers[13] = uIntValue; break;
        case 45: entityClass->SomePointers[14] = uIntValue; break;
        case 46: entityClass->SomePointers[15] = uIntValue; break;
    }

    emit dataChanged(index, index);
    return true;
}

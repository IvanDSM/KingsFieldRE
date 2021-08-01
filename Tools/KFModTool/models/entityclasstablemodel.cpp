#include "entityclasstablemodel.h"

QVariant EntityClassTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(KingsFieldII::getEntityMeshIDAsByte(entityClassDecl.MeshID)) +
                                    " (" +
                                    KingsFieldII::getEntityMeshName(entityClassDecl.MeshID) +
                                    ')'); break;
            case 1: result.setValue(QString::number(entityClassDecl.FourOrForty)); break;
            case 2: result.setValue(QString::number(entityClassDecl.field_0x2)); break;
            case 3: result.setValue(QString::number(entityClassDecl.KnockbackResistance)); break;
            case 4: result.setValue(QString::number(entityClassDecl.field_0x5)); break;
            case 5: result.setValue(QString::number(entityClassDecl.Unknown_x07)); break;
            case 6: result.setValue(QString::number(entityClassDecl.Unknown_x08)); break;
            case 7: result.setValue(QString::number(entityClassDecl.field_0x9)); break;
            case 8: result.setValue(QString::number(entityClassDecl.SpawnDistance)); break;
            case 9: result.setValue(QString::number(entityClassDecl.DespawnDistance)); break;
            case 10: result.setValue(QString::number(entityClassDecl.SomethingX)); break;
            case 11: result.setValue(QString::number(entityClassDecl.SomethingY)); break;
            case 12: result.setValue(QString::number(entityClassDecl.SomethingZ)); break;
            case 13: result.setValue(QString::number(entityClassDecl.Unknown_x12)); break;
            case 14: result.setValue(QString::number(entityClassDecl.Unknown_x14)); break;
            case 15: result.setValue(QString::number(entityClassDecl.LookingAtMargin1)); break;
            case 16: result.setValue(QString::number(entityClassDecl.LookingAtMargin2)); break;
            case 17: result.setValue(QString::number(entityClassDecl.HP)); break;
            case 18: result.setValue(QString::number(entityClassDecl.Unknown_x1c)); break;
            case 19: result.setValue(QString::number(entityClassDecl.ExperienceGain)); break;
            case 20: result.setValue(QString::number(entityClassDecl.DefSlash)); break;
            case 21: result.setValue(QString::number(entityClassDecl.DefChop)); break;
            case 22: result.setValue(QString::number(entityClassDecl.DefStab)); break;
            case 23: result.setValue(QString::number(entityClassDecl.DefHolyMagic)); break;
            case 24: result.setValue(QString::number(entityClassDecl.DefFireMagic)); break;
            case 25: result.setValue(QString::number(entityClassDecl.DefEarthMagic)); break;
            case 26: result.setValue(QString::number(entityClassDecl.DefWindMagic)); break;
            case 27: result.setValue(QString::number(entityClassDecl.DefWaterMagic)); break;
            case 28: result.setValue(QString::number(entityClassDecl.GoldSomething)); break;
            case 29: result.setValue(QString::number(entityClassDecl.Scale)); break;
            case 30: result.setValue(QString::number(entityClassDecl.UknBitField34)); break;
            case 31: result.setValue(getSomePointer(0)); break;
            case 32: result.setValue(getSomePointer(1)); break;
            case 33: result.setValue(getSomePointer(2)); break;
            case 34: result.setValue(getSomePointer(3)); break;
            case 35: result.setValue(getSomePointer(4)); break;
            case 36: result.setValue(getSomePointer(5)); break;
            case 37: result.setValue(getSomePointer(6)); break;
            case 38: result.setValue(getSomePointer(7)); break;
            case 39: result.setValue(getSomePointer(8)); break;
            case 40: result.setValue(getSomePointer(9)); break;
            case 41: result.setValue(getSomePointer(10)); break;
            case 42: result.setValue(getSomePointer(11)); break;
            case 43: result.setValue(getSomePointer(12)); break;
            case 44: result.setValue(getSomePointer(13)); break;
            case 45: result.setValue(getSomePointer(14)); break;
            case 46: result.setValue(getSomePointer(15)); break;
        }
    }
    return result;
}

QVariant EntityClassTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
                case 0: return "Mesh ID";
                case 1: return "Four Or Forty";
                case 2: return "Unknown 02";
                case 3: return "Knockback Resistance";
                case 4: return "Unknown 05";
                case 5: return "Unknown 07";
                case 6: return "Unknown 08";
                case 7: return "Unknown 09";
                case 8: return "Spawn Distance";
                case 9: return "Despawn Distance";
                case 10: return "Something X";
                case 11: return "Something Y";
                case 12: return "Something Z";
                case 13: return "Unknown 12";
                case 14: return "Unknown 14";
                case 15: return "\"Looking At\" Margin 1";
                case 16: return "\"Looking At\" Margin 2";
                case 17: return "HP";
                case 18: return "Unknown 1C";
                case 19: return "Experience Gain";
                case 20: return "Slash Def";
                case 21: return "Chop Def";
                case 22: return "Stab Def";
                case 23: return "Holy Magic Def";
                case 24: return "Fire Magic Def";
                case 25: return "Earth Magic Def";
                case 26: return "Wind Magic Def";
                case 27: return "Water Magic Def";
                case 28: return "Gold Something";
                case 29: return "Scale";
                case 30: return "Unk. Bitfield 34";
                case 31: return "SomePointers[0]";
                case 32: return "SomePointers[1]";
                case 33: return "SomePointers[2]";
                case 34: return "SomePointers[3]";
                case 35: return "SomePointers[4]";
                case 36: return "SomePointers[5]";
                case 37: return "SomePointers[6]";
                case 38: return "SomePointers[7]";
                case 39: return "SomePointers[8]";
                case 40: return "SomePointers[9]";
                case 41: return "SomePointers[10]";
                case 42: return "SomePointers[11]";
                case 43: return "SomePointers[12]";
                case 44: return "SomePointers[13]";
                case 45: return "SomePointers[14]";
                case 46: return "SomePointers[15]";
                default: break;
            }
        }
    }
    return QVariant();
}

bool EntityClassTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;

    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        short shortValue = qMax(-32767, qMin(32767, value.toInt()));
        u_short uShortValue = qMin(65535u, value.toUInt());
        byte byteValue = qMin(255u, value.toUInt());
        unsigned int uIntValue = value.toUInt();

        switch (index.row())
        {
            case 0: entityClassDecl.MeshID = KingsFieldII::getEntityMeshIDFromByte(byteValue); break;
            case 1: entityClassDecl.FourOrForty = byteValue; break;
            case 2: entityClassDecl.field_0x2 = byteValue; break;
            case 3: entityClassDecl.KnockbackResistance = uShortValue; break;
            case 4: entityClassDecl.field_0x5 = uShortValue; break;
            case 5: entityClassDecl.Unknown_x07 = byteValue; break;
            case 6: entityClassDecl.Unknown_x08 = byteValue; break;
            case 7: entityClassDecl.field_0x9 = byteValue; break;
            case 8: entityClassDecl.SpawnDistance = byteValue; break;
            case 9: entityClassDecl.DespawnDistance = byteValue; break;
            case 10: entityClassDecl.SomethingX = shortValue; break;
            case 11: entityClassDecl.SomethingY = shortValue; break;
            case 12: entityClassDecl.SomethingZ = shortValue; break;
            case 13: entityClassDecl.Unknown_x12 = uShortValue; break;
            case 14: entityClassDecl.Unknown_x14 = uShortValue; break;
            case 15: entityClassDecl.LookingAtMargin1 = shortValue; break;
            case 16: entityClassDecl.LookingAtMargin2 = shortValue; break;
            case 17: entityClassDecl.HP = uShortValue; break;
            case 18: entityClassDecl.Unknown_x1c = uShortValue; break;
            case 19: entityClassDecl.ExperienceGain = uShortValue; break;
            case 20: entityClassDecl.DefSlash = uShortValue; break;
            case 21: entityClassDecl.DefChop = uShortValue; break;
            case 22: entityClassDecl.DefStab = uShortValue; break;
            case 23: entityClassDecl.DefHolyMagic = uShortValue; break;
            case 24: entityClassDecl.DefFireMagic = uShortValue; break;
            case 25: entityClassDecl.DefEarthMagic = uShortValue; break;
            case 26: entityClassDecl.DefWindMagic = uShortValue; break;
            case 27: entityClassDecl.DefWaterMagic = uShortValue; break;
            case 28: entityClassDecl.GoldSomething = uShortValue; break;
            case 29: entityClassDecl.Scale = shortValue; break;
            case 30: entityClassDecl.UknBitField34 = uIntValue; break;
            case 31: entityClassDecl.SomePointers[0] = uIntValue; break;
            case 32: entityClassDecl.SomePointers[1] = uIntValue; break;
            case 33: entityClassDecl.SomePointers[2] = uIntValue; break;
            case 34: entityClassDecl.SomePointers[3] = uIntValue; break;
            case 35: entityClassDecl.SomePointers[4] = uIntValue; break;
            case 36: entityClassDecl.SomePointers[5] = uIntValue; break;
            case 37: entityClassDecl.SomePointers[6] = uIntValue; break;
            case 38: entityClassDecl.SomePointers[7] = uIntValue; break;
            case 39: entityClassDecl.SomePointers[8] = uIntValue; break;
            case 40: entityClassDecl.SomePointers[9] = uIntValue; break;
            case 41: entityClassDecl.SomePointers[10] = uIntValue; break;
            case 42: entityClassDecl.SomePointers[11] = uIntValue; break;
            case 43: entityClassDecl.SomePointers[12] = uIntValue; break;
            case 44: entityClassDecl.SomePointers[13] = uIntValue; break;
            case 45: entityClassDecl.SomePointers[14] = uIntValue; break;
            case 46: entityClassDecl.SomePointers[15] = uIntValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

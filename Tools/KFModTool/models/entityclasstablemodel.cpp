#include "entityclasstablemodel.h"

QVariant EntityClassTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(KingsField::getEntityMeshIDAsByte(entityClassDecl.MeshID)) +
                                    " (" +
                                    KingsField::getEntityMeshName(entityClassDecl.MeshID) +
                                    ')'); break;
            case 1: result.setValue(QString::number(entityClassDecl.FourOrForty)); break;
            case 2: result.setValue(QString::number(entityClassDecl.field_0x2)); break;
            case 3: result.setValue(QString::number(entityClassDecl.field_0x3)); break;
            case 4: result.setValue(QString::number(entityClassDecl.field_0x4)); break;
            case 5: result.setValue(QString::number(entityClassDecl.field_0x5)); break;
            case 6: result.setValue(QString::number(entityClassDecl.field_0x6)); break;
            case 7: result.setValue(QString::number(entityClassDecl.Unknown_x07)); break;
            case 8: result.setValue(QString::number(entityClassDecl.Unknown_x08)); break;
            case 9: result.setValue(QString::number(entityClassDecl.field_0x9)); break;
            case 10: result.setValue(QString::number(entityClassDecl.SpawnDistance)); break;
            case 11: result.setValue(QString::number(entityClassDecl.DespawnDistance)); break;
            case 12: result.setValue(QString::number(entityClassDecl.field_0xc)); break;
            case 13: result.setValue(QString::number(entityClassDecl.field_0xd)); break;
            case 14: result.setValue(QString::number(entityClassDecl.field_0xe)); break;
            case 15: result.setValue(QString::number(entityClassDecl.field_0xf)); break;
            case 16: result.setValue(QString::number(entityClassDecl.field_0x10)); break;
            case 17: result.setValue(QString::number(entityClassDecl.field_0x11)); break;
            case 18: result.setValue(QString::number(entityClassDecl.Unknown_x12)); break;
            case 19: result.setValue(QString::number(entityClassDecl.Unknown_x14)); break;
            case 20: result.setValue(QString::number(entityClassDecl.field_0x16)); break;
            case 21: result.setValue(QString::number(entityClassDecl.field_0x17)); break;
            case 22: result.setValue(QString::number(entityClassDecl.field_0x18)); break;
            case 23: result.setValue(QString::number(entityClassDecl.field_0x19)); break;
            case 24: result.setValue(QString::number(entityClassDecl.HP)); break;
            case 25: result.setValue(QString::number(entityClassDecl.Unknown_x1c)); break;
            case 26: result.setValue(QString::number(entityClassDecl.ExperienceGain)); break;
            case 27: result.setValue(QString::number(entityClassDecl.DefSlash)); break;
            case 28: result.setValue(QString::number(entityClassDecl.DefChop)); break;
            case 29: result.setValue(QString::number(entityClassDecl.DefStab)); break;
            case 30: result.setValue(QString::number(entityClassDecl.DefHolyMagic)); break;
            case 31: result.setValue(QString::number(entityClassDecl.DefFireMagic)); break;
            case 32: result.setValue(QString::number(entityClassDecl.DefEarthMagic)); break;
            case 33: result.setValue(QString::number(entityClassDecl.DefWindMagic)); break;
            case 34: result.setValue(QString::number(entityClassDecl.DefWaterMagic)); break;
            case 35: result.setValue(QString::number(entityClassDecl.GoldSomething)); break;
            case 36: result.setValue(QString::number(entityClassDecl.Scale)); break;
            case 37: result.setValue(QString::number(entityClassDecl.UknBitField34)); break;
            case 38: result.setValue(getSomePointer(0)); break;
            case 39: result.setValue(getSomePointer(1)); break;
            case 40: result.setValue(getSomePointer(2)); break;
            case 41: result.setValue(getSomePointer(3)); break;
            case 42: result.setValue(getSomePointer(4)); break;
            case 43: result.setValue(getSomePointer(5)); break;
            case 44: result.setValue(getSomePointer(6)); break;
            case 45: result.setValue(getSomePointer(7)); break;
            case 46: result.setValue(getSomePointer(8)); break;
            case 47: result.setValue(getSomePointer(9)); break;
            case 48: result.setValue(getSomePointer(10)); break;
            case 49: result.setValue(getSomePointer(11)); break;
            case 50: result.setValue(getSomePointer(12)); break;
            case 51: result.setValue(getSomePointer(13)); break;
            case 52: result.setValue(getSomePointer(14)); break;
            case 53: result.setValue(getSomePointer(15)); break;
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
                case 3: return "Unknown 03";
                case 4: return "Unknown 04";
                case 5: return "Unknown 05";
                case 6: return "Unknown 06";
                case 7: return "Unknown 07";
                case 8: return "Unknown 08";
                case 9: return "Unknown 09";
                case 10: return "Spawn Distance";
                case 11: return "Despawn Distance";
                case 12: return "Unknown 0C";
                case 13: return "Unknown 0D";
                case 14: return "Unknown 0E";
                case 15: return "Unknown 0F";
                case 16: return "Unknown 10";
                case 17: return "Unknown 11";
                case 18: return "Unknown 12";
                case 19: return "Unknown 14";
                case 20: return "Unknown 16";
                case 21: return "Unknown 17";
                case 22: return "Unknown 18";
                case 23: return "Unknown 19";
                case 24: return "HP";
                case 25: return "Unknown 1C";
                case 26: return "Experience Gain";
                case 27: return "Slash Def";
                case 28: return "Chop Def";
                case 29: return "Stab Def";
                case 30: return "Holy Magic Def";
                case 31: return "Fire Magic Def";
                case 32: return "Earth Magic Def";
                case 33: return "Wind Magic Def";
                case 34: return "Water Magic Def";
                case 35: return "Gold Something";
                case 36: return "Scale";
                case 37: return "Unk. Bitfield 34";
                case 38: return "SomePointers[0]";
                case 39: return "SomePointers[1]";
                case 40: return "SomePointers[2]";
                case 41: return "SomePointers[3]";
                case 42: return "SomePointers[4]";
                case 43: return "SomePointers[5]";
                case 44: return "SomePointers[6]";
                case 45: return "SomePointers[7]";
                case 46: return "SomePointers[8]";
                case 47: return "SomePointers[9]";
                case 48: return "SomePointers[10]";
                case 49: return "SomePointers[11]";
                case 50: return "SomePointers[12]";
                case 51: return "SomePointers[13]";
                case 52: return "SomePointers[14]";
                case 53: return "SomePointers[15]";
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
            case 0: entityClassDecl.MeshID = KingsField::getEntityMeshIDFromByte(byteValue); break;
            case 1: entityClassDecl.FourOrForty = byteValue; break;
            case 2: entityClassDecl.field_0x2 = byteValue; break;
            case 3: entityClassDecl.field_0x3 = byteValue; break;
            case 4: entityClassDecl.field_0x4 = byteValue; break;
            case 5: entityClassDecl.field_0x5 = byteValue; break;
            case 6: entityClassDecl.field_0x6 = byteValue; break;
            case 7: entityClassDecl.Unknown_x07 = byteValue; break;
            case 8: entityClassDecl.Unknown_x08 = byteValue; break;
            case 9: entityClassDecl.field_0x9 = byteValue; break;
            case 10: entityClassDecl.SpawnDistance = byteValue; break;
            case 11: entityClassDecl.DespawnDistance = byteValue; break;
            case 12: entityClassDecl.field_0xc = byteValue; break;
            case 13: entityClassDecl.field_0xd = byteValue; break;
            case 14: entityClassDecl.field_0xe = byteValue; break;
            case 15: entityClassDecl.field_0xf = byteValue; break;
            case 16: entityClassDecl.field_0x10 = byteValue; break;
            case 17: entityClassDecl.field_0x11 = byteValue; break;
            case 18: entityClassDecl.Unknown_x12 = uShortValue; break;
            case 19: entityClassDecl.Unknown_x14 = uShortValue; break;
            case 20: entityClassDecl.field_0x16 = byteValue; break;
            case 21: entityClassDecl.field_0x17 = byteValue; break;
            case 22: entityClassDecl.field_0x18 = byteValue; break;
            case 23: entityClassDecl.field_0x19 = byteValue; break;
            case 24: entityClassDecl.HP = uShortValue; break;
            case 25: entityClassDecl.Unknown_x1c = uShortValue; break;
            case 26: entityClassDecl.ExperienceGain = uShortValue; break;
            case 27: entityClassDecl.DefSlash = uShortValue; break;
            case 28: entityClassDecl.DefChop = uShortValue; break;
            case 29: entityClassDecl.DefStab = uShortValue; break;
            case 30: entityClassDecl.DefHolyMagic = uShortValue; break;
            case 31: entityClassDecl.DefFireMagic = uShortValue; break;
            case 32: entityClassDecl.DefEarthMagic = uShortValue; break;
            case 33: entityClassDecl.DefWindMagic = uShortValue; break;
            case 34: entityClassDecl.DefWaterMagic = uShortValue; break;
            case 35: entityClassDecl.GoldSomething = uShortValue; break;
            case 36: entityClassDecl.Scale = shortValue; break;
            case 37: entityClassDecl.UknBitField34 = uIntValue; break;
            case 38: entityClassDecl.SomePointers[0] = uIntValue; break;
            case 39: entityClassDecl.SomePointers[1] = uIntValue; break;
            case 40: entityClassDecl.SomePointers[2] = uIntValue; break;
            case 41: entityClassDecl.SomePointers[3] = uIntValue; break;
            case 42: entityClassDecl.SomePointers[4] = uIntValue; break;
            case 43: entityClassDecl.SomePointers[5] = uIntValue; break;
            case 44: entityClassDecl.SomePointers[6] = uIntValue; break;
            case 45: entityClassDecl.SomePointers[7] = uIntValue; break;
            case 46: entityClassDecl.SomePointers[8] = uIntValue; break;
            case 47: entityClassDecl.SomePointers[9] = uIntValue; break;
            case 48: entityClassDecl.SomePointers[10] = uIntValue; break;
            case 49: entityClassDecl.SomePointers[11] = uIntValue; break;
            case 50: entityClassDecl.SomePointers[12] = uIntValue; break;
            case 51: entityClassDecl.SomePointers[13] = uIntValue; break;
            case 52: entityClassDecl.SomePointers[14] = uIntValue; break;
            case 53: entityClassDecl.SomePointers[15] = uIntValue; break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

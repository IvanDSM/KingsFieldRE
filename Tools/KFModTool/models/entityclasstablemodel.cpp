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
            case 7: result.setValue(QString::number(entityClassDecl.field_0x7)); break;
            case 8: result.setValue(QString::number(entityClassDecl.field_0x8)); break;
            case 9: result.setValue(QString::number(entityClassDecl.field_0x9)); break;
            case 10: result.setValue(QString::number(entityClassDecl.field_0xa)); break;
            case 11: result.setValue(QString::number(entityClassDecl.field_0xb)); break;
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
            case 25: result.setValue(QString::number(entityClassDecl.field_0x1c)); break;
            case 26: result.setValue(QString::number(entityClassDecl.field_0x1d)); break;
            case 27: result.setValue(QString::number(entityClassDecl.ExperienceGain)); break;
            case 28: result.setValue(QString::number(entityClassDecl.DefSlash)); break;
            case 29: result.setValue(QString::number(entityClassDecl.DefChop)); break;
            case 30: result.setValue(QString::number(entityClassDecl.DefStab)); break;
            case 31: result.setValue(QString::number(entityClassDecl.DefHolyMagic)); break;
            case 32: result.setValue(QString::number(entityClassDecl.DefFireMagic)); break;
            case 33: result.setValue(QString::number(entityClassDecl.DefEarthMagic)); break;
            case 34: result.setValue(QString::number(entityClassDecl.DefWindMagic)); break;
            case 35: result.setValue(QString::number(entityClassDecl.DefWaterMagic)); break;
            case 36: result.setValue(QString::number(entityClassDecl.field_0x30)); break;
            case 37: result.setValue(QString::number(entityClassDecl.field_0x31)); break;
            case 38: result.setValue(QString::number(entityClassDecl.Scale)); break;
            case 39: result.setValue(QString::number(entityClassDecl.Unknown_x34)); break;
            case 40: result.setValue(getSomePointer(0)); break;
            case 41: result.setValue(getSomePointer(1)); break;
            case 42: result.setValue(getSomePointer(2)); break;
            case 43: result.setValue(getSomePointer(3)); break;
            case 44: result.setValue(getSomePointer(4)); break;
            case 45: result.setValue(getSomePointer(5)); break;
            case 46: result.setValue(getSomePointer(6)); break;
            case 47: result.setValue(getSomePointer(7)); break;
            case 48: result.setValue(getSomePointer(8)); break;
            case 49: result.setValue(getSomePointer(9)); break;
            case 50: result.setValue(getSomePointer(10)); break;
            case 51: result.setValue(getSomePointer(11)); break;
            case 52: result.setValue(getSomePointer(12)); break;
            case 53: result.setValue(getSomePointer(13)); break;
            case 54: result.setValue(getSomePointer(14)); break;
            case 55: result.setValue(getSomePointer(15)); break;
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
                case 10: return "Unknown 0A";
                case 11: return "Unknown 0B";
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
                case 26: return "Unknown 1D";
                case 27: return "Experience Gain";
                case 28: return "Slash Def";
                case 29: return "Chop Def";
                case 30: return "Stab Def";
                case 31: return "Holy Magic Def";
                case 32: return "Fire Magic Def";
                case 33: return "Earth Magic Def";
                case 34: return "Wind Magic Def";
                case 35: return "Water Magic Def";
                case 36: return "Unknown 30";
                case 37: return "Unknown 31";
                case 38: return "Scale";
                case 39: return "Unknown 34";
                case 40: return "SomePointers[0]";
                case 41: return "SomePointers[1]";
                case 42: return "SomePointers[2]";
                case 43: return "SomePointers[3]";
                case 44: return "SomePointers[4]";
                case 45: return "SomePointers[5]";
                case 46: return "SomePointers[6]";
                case 47: return "SomePointers[7]";
                case 48: return "SomePointers[8]";
                case 49: return "SomePointers[9]";
                case 50: return "SomePointers[10]";
                case 51: return "SomePointers[11]";
                case 52: return "SomePointers[12]";
                case 53: return "SomePointers[13]";
                case 54: return "SomePointers[14]";
                case 55: return "SomePointers[15]";
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
        int intValue = 0;
        unsigned int uIntValue = 0;

        switch (index.row())
        {
            case 0:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityClassDecl.MeshID = KingsField::getEntityMeshIDFromByte(static_cast<quint8>(uIntValue));
                    result = true;
                }
                break;
            case 1:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityClassDecl.FourOrForty = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 2:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x2 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 3:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x3 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 4:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x4 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 5:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x5 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 6:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x6 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 7:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x7 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 8:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x8 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 9:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x9 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 10:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xa = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 11:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xb = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 12:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xc = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 13:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xd = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 14:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xe = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 15:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0xf = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 16:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x10 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 17:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x11 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 18:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.Unknown_x12 = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;
            case 19:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.Unknown_x14 = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;
            case 20:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x16 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 21:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x17 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 22:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x18 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 23:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x19 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 24:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.HP = static_cast<quint16>(uIntValue);
                }
                break;

            case 25:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x1c = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 26:
                uIntValue = value.toUInt();
                if(uIntValue < 256)
                {
                    entityClassDecl.field_0x1d = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 27:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.ExperienceGain = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 28:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefSlash = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 29:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefChop = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 30:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefStab = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 31:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefHolyMagic = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 32:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefFireMagic = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 33:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefEarthMagic = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 34:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefWindMagic = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;

            case 35:
                uIntValue = value.toUInt();
                if (uIntValue < 65536)
                {
                    entityClassDecl.DefWaterMagic = static_cast<quint16>(uIntValue);
                    result = true;
                }
                break;
            case 36:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityClassDecl.field_0x30 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;

            case 37:
                uIntValue = value.toUInt();
                if (uIntValue < 256)
                {
                    entityClassDecl.field_0x31 = static_cast<quint8>(uIntValue);
                    result = true;
                }
                break;
            case 38:
                intValue = value.toInt();
                if (intValue > -32768 && intValue < 32767)
                {
                    entityClassDecl.Scale = static_cast<short>(intValue);
                    result = true;
                }
                break;
            case 39:
                entityClassDecl.Unknown_x34 = value.toUInt();
                result = true;
                break;
            case 40:
                entityClassDecl.SomePointers[0] = value.toUInt();
                result = true;
                break;
            case 41:
                entityClassDecl.SomePointers[1] = value.toUInt();
                result = true;
                break;
            case 42:
                entityClassDecl.SomePointers[2] = value.toUInt();
                result = true;
                break;
            case 43:
                entityClassDecl.SomePointers[3] = value.toUInt();
                result = true;
                break;
            case 44:
                entityClassDecl.SomePointers[4] = value.toUInt();
                result = true;
                break;
            case 45:
                entityClassDecl.SomePointers[5] = value.toUInt();
                result = true;
                break;
            case 46:
                entityClassDecl.SomePointers[6] = value.toUInt();
                result = true;
                break;
            case 47:
                entityClassDecl.SomePointers[7] = value.toUInt();
                result = true;
                break;
            case 48:
                entityClassDecl.SomePointers[8] = value.toUInt();
                result = true;
                break;
            case 49:
                entityClassDecl.SomePointers[9] = value.toUInt();
                result = true;
                break;
            case 50:
                entityClassDecl.SomePointers[10] = value.toUInt();
                result = true;
                break;
            case 51:
                entityClassDecl.SomePointers[11] = value.toUInt();
                result = true;
                break;
            case 52:
                entityClassDecl.SomePointers[12] = value.toUInt();
                result = true;
                break;
            case 53:
                entityClassDecl.SomePointers[13] = value.toUInt();
                result = true;
                break;
            case 54:
                entityClassDecl.SomePointers[14] = value.toUInt();
                result = true;
                break;
            case 55:
                entityClassDecl.SomePointers[15] = value.toUInt();
                result = true;
                break;
        }
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

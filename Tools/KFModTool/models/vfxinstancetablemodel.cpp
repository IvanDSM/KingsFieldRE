#include "vfxinstancetablemodel.h"
#include "utilities.h"

QVariant VFXInstanceTableModel::data(const QModelIndex & index, int role) const
{
    if (role != Qt::DisplayRole) return {};
    if (!index.isValid()) return {};

    switch (index.row())
    {
        case 0: return QString::number(vfx->VFXID);
        case 1: return QString::number(vfx->AnimFrameCount);
        case 2: return QString::number(vfx->AnimSpeed);
        case 3: return QString::number(vfx->TileLayer);
        case 4: return QString::number(vfx->TileWEX);
        case 5: return QString::number(vfx->TileNSY);
        case 6: return QString::number(vfx->field_0x7);
        case 7: return QString::number(vfx->field_0x8);
        case 8: return QString::number(vfx->field_0x9);
        case 9: return QString::number(vfx->FineXPos);
        case 10: return QString::number(vfx->FineYPos);
        case 11: return QString::number(vfx->FineZPos);
        default: return {};
    }
}

QVariant VFXInstanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):
    switch (section)
    {
        case 0: return QStringLiteral("VFX ID");
        case 1: return QStringLiteral("Animation Frame Count");
        case 2: return QStringLiteral("Animation Speed");
        case 3: return QStringLiteral("Tile Layer");
        case 4: return QStringLiteral("X Tile Position");
        case 5: return QStringLiteral("Y Tile Position");
        case 6: return QStringLiteral("Unknown 07");
        case 7: return QStringLiteral("Unknown 08");
        case 8: return QStringLiteral("Unknown 09");
        case 9: return QStringLiteral("Fine X Position");
        case 10: return QStringLiteral("Fine Y Position");
        case 11: return QStringLiteral("Fine Z Position");
        default: return {};
    }
}

bool VFXInstanceTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (value.toString().isEmpty() || !value.isValid() || role != Qt::EditRole || !index.isValid())
        return false;

    auto uShortValue = Utilities::clampToUShort(value.toUInt());
    auto shortValue = Utilities::clampToShort(value.toInt());
    auto byteValue = Utilities::clampToByte(value.toUInt());

    switch (index.row())
    {
        case 0: vfx->VFXID = uShortValue; break;
        case 1: vfx->AnimFrameCount = byteValue; break;
        case 2: vfx->AnimSpeed = byteValue; break;
        case 3: vfx->TileLayer = byteValue; break;
        case 4: vfx->TileWEX = byteValue; break;
        case 5: vfx->TileNSY = byteValue; break;
        case 6: vfx->field_0x7 = byteValue; break;
        case 7: vfx->field_0x8 = byteValue; break;
        case 8: vfx->field_0x9 = byteValue; break;
        case 9: vfx->FineXPos = shortValue; break;
        case 10: vfx->FineYPos = shortValue; break;
        case 11: vfx->FineZPos = shortValue; break;
    }

    emit dataChanged(index, index);

    return true;
}

#include "acblockvertextablemodel.h"

void ACBlockVertexTableModel::setTarget(ACMission* missionPtr, size_t blockIdx, size_t subIdx)
{
    beginResetModel();
    mission = missionPtr;
    blockIndex = blockIdx;
    subIndex = subIdx;
    endResetModel();
}

void ACBlockVertexTableModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int ACBlockVertexTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    if (!mission || blockIndex >= mission->blockCount()) return 0;
    const auto& subs = mission->getBlockInfo(blockIndex).subObjects;
    if (subIndex >= subs.size()) return 0;
    return static_cast<int>(subs.at(subIndex).vtxCount);
}

QVariant ACBlockVertexTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section)
    {
        case 0: return QStringLiteral("Vtx");
        case 1: return QStringLiteral("X (4x)");
        case 2: return QStringLiteral("Y (4x)");
        case 3: return QStringLiteral("Z (4x)");
        default: return {};
    }
}

Qt::ItemFlags ACBlockVertexTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    if (index.column() >= 1 && index.column() <= 3)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ACBlockVertexTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !mission) return {};
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};

    if (index.column() == 0) return index.row();

    const auto xyz = mission->getSubObjectVertex(blockIndex, subIndex, static_cast<uint32_t>(index.row()));
    return xyz.at(index.column() - 1);
}

bool ACBlockVertexTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole || index.column() < 1 || index.column() > 3 || !mission)
        return false;

    bool ok = false;
    const int val = value.toInt(&ok);
    if (!ok) return false;

    const uint32_t vIdx = static_cast<uint32_t>(index.row());
    auto xyz = mission->getSubObjectVertex(blockIndex, subIndex, vIdx);
    xyz.at(index.column() - 1) = static_cast<int16_t>(val);
    mission->setSubObjectVertex(blockIndex, subIndex, vIdx, xyz.at(0), xyz.at(1), xyz.at(2));

    emit dataChanged(index, index);
    return true;
}

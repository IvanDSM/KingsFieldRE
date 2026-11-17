#include "acspawntablemodel.h"

void ACSpawnTableModel::setSpawn(AC1::SpawnRecord* record)
{
    beginResetModel();
    spawn = record;
    endResetModel();
}

int ACSpawnTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return spawn != nullptr ? 20 : 0;
}

QVariant ACSpawnTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    return section == 0 ? QStringLiteral("Field") : QStringLiteral("Value");
}

Qt::ItemFlags ACSpawnTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    if (index.column() == 1) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ACSpawnTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || spawn == nullptr) return {};
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};

    if (index.column() == 0)
    {
        switch (index.row())
        {
            case 0: return QStringLiteral("Pos X (hw0)");
            case 1: return QStringLiteral("Pos Y (hw1, +down)");
            case 2: return QStringLiteral("Pos Z (hw2)");
            case 3: return QStringLiteral("Block / Dispatch Type (hw3)");
            case 4: return QStringLiteral("hw4");
            case 5: return QStringLiteral("Rotation (hw5, 2048=180°)");
            case 6: return QStringLiteral("hw6");
            case 7: return QStringLiteral("Resource / Class ID (hw7)");
            case 8: return QStringLiteral("Param 8 (hw8)");
            case 9: return QStringLiteral("Param 9 (hw9)");
            case 10: return QStringLiteral("hw10");
            case 11: return QStringLiteral("HP (hw11)");
            case 12: return QStringLiteral("Param 12 (hw12)");
            case 13: return QStringLiteral("hw13");
            case 14: return QStringLiteral("hw14");
            case 15: return QStringLiteral("Param 15 (hw15)");
            case 16: return QStringLiteral("hw16");
            case 17: return QStringLiteral("hw17");
            case 18: return QStringLiteral("hw18");
            case 19: return QStringLiteral("Param 19 (hw19)");
            default: return {};
        }
    }

    const auto* hw = reinterpret_cast<const int16_t*>(spawn);
    return hw[index.row()];
}

bool ACSpawnTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole || index.column() != 1 || spawn == nullptr || index.row() < 0 || index.row() >= 20)
        return false;

    bool ok = false;
    const int val = value.toInt(&ok);
    if (!ok) return false;

    auto* hw = reinterpret_cast<int16_t*>(spawn);
    hw[index.row()] = static_cast<int16_t>(val);
    emit dataChanged(index, index);
    return true;
}

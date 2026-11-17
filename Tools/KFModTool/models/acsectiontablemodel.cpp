#include "acsectiontablemodel.h"
#include <QStringList>

void ACSectionTableModel::setSection(ACMission* missionPtr, size_t index)
{
    beginResetModel();
    mission = missionPtr;
    sectionIndex = index;
    endResetModel();
}

int ACSectionTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    if (!mission || sectionIndex >= mission->sectionCount()) return 0;
    return 11;
}

QVariant ACSectionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    return section == 0 ? QStringLiteral("Field") : QStringLiteral("Value");
}

Qt::ItemFlags ACSectionTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    if (index.column() == 1 && index.row() < 9)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ACSectionTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !mission || sectionIndex >= mission->sectionCount()) return {};
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};

    const auto& sec = mission->getSection(sectionIndex);

    if (index.column() == 0)
    {
        switch (index.row())
        {
            case 0:  return QStringLiteral("Translation X (+0x10)");
            case 1:  return QStringLiteral("Translation Y (+0x12)");
            case 2:  return QStringLiteral("Translation Z (+0x14)");
            case 3:  return QStringLiteral("Rotation Y (+0x16, 1024=90°)");
            case 4:  return QStringLiteral("Block Index (+0x1E)");
            case 5:  return QStringLiteral("Cell / PVS Index (+0x06)");
            case 6:  return QStringLiteral("Zone / Portal Index (+0x26)");
            case 7:  return QStringLiteral("Lighting Index (+0x28)");
            case 8:  return QStringLiteral("Flags (+0x2A)");
            case 9:  return QStringLiteral("BBox Min (+0x00)");
            case 10: return QStringLiteral("BBox Max (+0x08)");
            default: return {};
        }
    }

    switch (index.row())
    {
        case 0:  return sec.translation[0];
        case 1:  return sec.translation[1];
        case 2:  return sec.translation[2];
        case 3:  return sec.rotY;
        case 4:  return sec.blockIndex;
        case 5:  return sec.cellIndex;
        case 6:  return sec.zoneIndex;
        case 7:  return sec.lightingIndex;
        case 8:  return QStringLiteral("0x%1").arg(sec.flags, 4, 16, QLatin1Char('0'));
        case 9:  return QStringLiteral("%1, %2, %3").arg(sec.bboxMin[0]).arg(sec.bboxMin[1]).arg(sec.bboxMin[2]);
        case 10: return QStringLiteral("%1, %2, %3").arg(sec.bboxMax[0]).arg(sec.bboxMax[1]).arg(sec.bboxMax[2]);
        default: return {};
    }
}

bool ACSectionTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole || index.column() != 1 || !mission || sectionIndex >= mission->sectionCount())
        return false;

    bool ok = false;
    const int val = value.toString().toInt(&ok, 0);
    if (!ok) return false;

    auto& sec = mission->getSection(sectionIndex);
    switch (index.row())
    {
        case 0: sec.translation[0] = static_cast<int16_t>(val); break;
        case 1: sec.translation[1] = static_cast<int16_t>(val); break;
        case 2: sec.translation[2] = static_cast<int16_t>(val); break;
        case 3: sec.rotY = static_cast<int16_t>(val); break;
        case 4: sec.blockIndex = static_cast<int16_t>(val); break;
        case 5: sec.cellIndex = static_cast<int16_t>(val); break;
        case 6: sec.zoneIndex = static_cast<int16_t>(val); break;
        case 7: sec.lightingIndex = static_cast<uint8_t>(val); break;
        case 8: sec.flags = static_cast<uint16_t>(val); break;
        default: return false;
    }

    mission->rebuildAssembledLevel();
    emit dataChanged(index, index);
    return true;
}

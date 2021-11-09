#include "playerleveldatatablemodel.h"

QVariant PlayerLevelDataTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    const auto& level = gameDB.getLevel(curLevel);

    switch (index.row())
    {
        case 0: return QString::number(level.BaseHP);
        case 1: return QString::number(level.BaseMP);
        case 2: return QString::number(level.StrPowerPlus);
        case 3: return QString::number(level.MagPowerPlus);
        case 4: return QString::number(level.ExpForNextLevel);
        default: return {};
    }
}

QVariant PlayerLevelDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("Value");

    //if (orientation == Qt::Vertical):

    if (curLevel == 0)
    {
        switch (section)
        {
            case 0: return QStringLiteral("HP");
            case 1: return QStringLiteral("MP");
            case 2: return QStringLiteral("Strength Power");
            case 3: return QStringLiteral("Magic Power");
            case 4: return QStringLiteral("Exp. for the next level");
            default: return {};
        }
    }
    else
    {
        switch (section)
        {
            case 0: return QStringLiteral("HP");
            case 1: return QStringLiteral("MP");
            case 2: return QStringLiteral("Strength Power Increase");
            case 3: return QStringLiteral("Magic Power Increase");
            case 4: return QStringLiteral("Exp. for the next level");
            default: return {};
        }
    }
}

bool PlayerLevelDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto& level = gameDB.getLevel(curLevel);

    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    switch (index.row())
    {
        case 0:
            level.BaseHP = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
            break;
        case 1:
            level.BaseMP = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
            break;
        case 2:
            level.StrPowerPlus = qMin(static_cast<quint16>(65535),
                                      static_cast<quint16>(value.toUInt()));
            break;
        case 3:
            level.MagPowerPlus = qMin(static_cast<quint16>(65535),
                                      static_cast<quint16>(value.toUInt()));
            break;
        case 4:
            level.ExpForNextLevel = qMin(static_cast<quint16>(4294967295),
                                         static_cast<quint16>(value.toUInt()));
            break;
        default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

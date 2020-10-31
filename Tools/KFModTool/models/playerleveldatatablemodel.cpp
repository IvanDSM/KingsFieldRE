#include "playerleveldatatablemodel.h"

QVariant PlayerLevelDataTableModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
    {
        switch (index.row())
        {
            case 0: result.setValue(QString::number(playerLvl.BaseHP)); break;
            case 1: result.setValue(QString::number(playerLvl.BaseMP)); break;
            case 2: result.setValue(QString::number(playerLvl.StrPowerPlus)); break;
            case 3: result.setValue(QString::number(playerLvl.MagPowerPlus)); break;
            case 4: result.setValue(QString::number(playerLvl.ExpForNextLevel)); break;
        }
    }

    return result;
}

QVariant PlayerLevelDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return "Value";

        if (orientation == Qt::Vertical)
        {
            if (playerLvl.BaseHP == 50)
            {
                switch (section)
                {
                    case 0: return "HP";
                    case 1: return "MP";
                    case 2: return "Strength Power";
                    case 3: return "Magic Power";
                    case 4: return "Exp. for the next level";
                    default: break;
                }
            }
            else
            {
                switch (section)
                {
                    case 0: return "HP";
                    case 1: return "MP";
                    case 2: return "Strength Power Increase";
                    case 3: return "Magic Power Increase";
                    case 4: return "Exp. for the next level";
                    default: break;
                }
            }
        }
    }

    return QVariant();
}

bool PlayerLevelDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if (!value.toString().isEmpty() && value.isValid() && role == Qt::EditRole && index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0)
    {
        switch (index.row())
        {
            case 0:
                playerLvl.BaseHP = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
                break;
            case 1:
                playerLvl.BaseMP = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
                break;
            case 2:
                playerLvl.StrPowerPlus = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
                break;
            case 3:
                playerLvl.MagPowerPlus = qMin(static_cast<quint16>(65535), static_cast<quint16>(value.toUInt()));
                break;
            case 4:
                playerLvl.ExpForNextLevel = qMin(static_cast<quint16>(4294967295), static_cast<quint16>(value.toUInt()));
                break;
        }

        result = true;
    }

    if (result)
        emit dataChanged(index, index);

    return result;
}

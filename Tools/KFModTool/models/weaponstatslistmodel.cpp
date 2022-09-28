#include "weaponstatslistmodel.h"

WeaponStatsListModel::WeaponStatsListModel(GameDB gameDB_, QObject* parent)
    : QAbstractListModel(parent), gameDB(gameDB_)
{
}

int WeaponStatsListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return GameDB::weaponStatsSize;
}

QVariant WeaponStatsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    auto result = QStringLiteral("%1 (0x%2) %3")
                      .arg(QString::number(index.row()), QString::number(index.row(), 16));

    return result.arg(KF2::getWeaponName(index.row()));
}

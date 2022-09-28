#include "armorstatslistmodel.h"

ArmorStatsListModel::ArmorStatsListModel(GameDB& gameDB_, QObject* parent)
    : QAbstractListModel(parent), gameDB(gameDB_)
{
}

int ArmorStatsListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return GameDB::armorStatsSize;
}

QVariant ArmorStatsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    auto result = QStringLiteral("%1 (0x%2) %3")
                      .arg(QString::number(index.row()), QString::number(index.row(), 16));

    if (index.row() < 39)
        return result.arg(
            KF2::getObjectName(static_cast<KF2::ObjectID>(index.row() + 0x15)));
    else
        return result.arg(QStringLiteral("Unused"));
}

#include "entityclasslistmodel.h"

int EntityClassListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return Map::entityClassesSize;
}

QVariant EntityClassListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    const auto& entityClass = map.getEntityClassDeclaration(index.row());

    return QStringLiteral("%1: %2").arg(QString::number(index.row()),
                                        KF2::getEntityMeshName(entityClass.MeshID));
}

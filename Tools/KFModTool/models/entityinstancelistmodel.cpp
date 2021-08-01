#include "entityinstancelistmodel.h"

#include <utility>

EntityInstanceListModel::EntityInstanceListModel(QObject *parent, std::shared_ptr<Map> map_)
    : QAbstractListModel(parent), map(std::move(map_))
{
}

int EntityInstanceListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    
    return map->getEntityInstances().size();
}

QVariant EntityInstanceListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    
    const auto &entityClass = map->getEntityClassDeclaration(map->getEntityInstance(index.row()).EntityClass);
    
    return QString::number(index.row()) + ": " + KingsFieldII::getEntityMeshName(entityClass.MeshID) +
            " @ 0x" + QString::number(0x8016c544 + (index.row() * 0x7c), 16);
}

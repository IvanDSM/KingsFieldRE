#include "objectinstancelistmodel.h"

#include <utility>

ObjectInstanceListModel::ObjectInstanceListModel(QObject *parent, std::shared_ptr<Map> map_)
    : QAbstractListModel(parent), map(std::move(map_))
{
}

int ObjectInstanceListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    
    return map->getObjectInstanceDeclarations().size();
}

QVariant ObjectInstanceListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    
    return QString::number(index.row()) + ": " + 
           KingsFieldII::getObjectName(map->getObjectInstance(index.row()).ObjectID) + 
           " @ 0x" + QString::number(0x80177714 + (index.row() * 0x44), 16);
}

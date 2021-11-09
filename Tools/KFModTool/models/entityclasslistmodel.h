#ifndef ENTITYCLASSLISTMODEL_H
#define ENTITYCLASSLISTMODEL_H

#include "datahandlers/map.h"
#include <QAbstractListModel>

class EntityClassListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit EntityClassListModel(Map& map_, QObject* parent = nullptr)
        : QAbstractListModel(parent), map(map_)
    {}

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    Map& map;
};

#endif // ENTITYCLASSLISTMODEL_H

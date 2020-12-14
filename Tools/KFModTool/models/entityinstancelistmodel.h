#ifndef ENTITYINSTANCELISTMODEL_H
#define ENTITYINSTANCELISTMODEL_H

#include "map.h"
#include <QAbstractListModel>

class EntityInstanceListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit EntityInstanceListModel(QObject *parent = nullptr,
                                     std::shared_ptr<Map> map_ = nullptr);
    
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    std::shared_ptr<Map> map;
};

#endif // ENTITYINSTANCELISTMODEL_H

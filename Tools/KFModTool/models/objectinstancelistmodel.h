#ifndef OBJECTINSTANCELISTMODEL_H
#define OBJECTINSTANCELISTMODEL_H

#include "map.h"
#include <QAbstractListModel>

class ObjectInstanceListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit ObjectInstanceListModel(QObject *parent = nullptr,
                                     std::shared_ptr<Map> map_ = nullptr);
    
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    std::shared_ptr<Map> map;
};

#endif // OBJECTINSTANCELISTMODEL_H

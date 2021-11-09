#ifndef ARMORSTATSLISTMODEL_H
#define ARMORSTATSLISTMODEL_H

#include "datahandlers/gamedb.h"
#include <QAbstractListModel>

class ArmorStatsListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit ArmorStatsListModel(GameDB& gameDB_, QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    GameDB& gameDB;
};

#endif // ARMORSTATSLISTMODEL_H

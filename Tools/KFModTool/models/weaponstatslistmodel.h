#ifndef WEAPONSTATSLISTMODEL_H
#define WEAPONSTATSLISTMODEL_H

#include "datahandlers/gamedb.h"
#include <QAbstractListModel>

class WeaponStatsListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit WeaponStatsListModel(GameDB gameDB_, QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    GameDB& gameDB;
};

#endif // WEAPONSTATSLISTMODEL_H

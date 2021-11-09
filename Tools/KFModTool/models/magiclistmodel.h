#ifndef MAGICLISTMODEL_H
#define MAGICLISTMODEL_H

#include "datahandlers/gamedb.h"
#include <QAbstractListModel>

class MagicListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit MagicListModel(GameDB& gameDB_, QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    GameDB& gameDB;
};

#endif // MAGICLISTMODEL_H

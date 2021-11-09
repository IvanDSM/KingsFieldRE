#ifndef OBJECTCLASSLISTMODEL_H
#define OBJECTCLASSLISTMODEL_H

#include <datahandlers/gamedb.h>
#include <QAbstractListModel>

class ObjectClassListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit ObjectClassListModel(GameDB& gameDB_, QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    GameDB& gameDB;
};

#endif // OBJECTCLASSLISTMODEL_H

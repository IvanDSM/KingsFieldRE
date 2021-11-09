#ifndef SHOPTABLEMODEL_H
#define SHOPTABLEMODEL_H

#include "datahandlers/gameexe.h"
#include <QAbstractTableModel>

class ShopTableModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    explicit ShopTableModel(GameEXE& gameExe_, QObject* parent = nullptr)
        : QAbstractTableModel(parent), gameExe(gameExe_)
    {}

    void setShopIndex(int shopIndex_)
    {
        // FIXME: This if only applies to KF2, I'm lazy right now
        if (shopIndex_ > 5) return;

        shopIndex = shopIndex_;
        emit layoutChanged();
    }

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    GameEXE& gameExe;
    size_t shopIndex = 0;
};

#endif // SHOPTABLEMODEL_H

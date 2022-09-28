#ifndef TILECONTENTSLISTMODEL_H
#define TILECONTENTSLISTMODEL_H

#include "datahandlers/map.h"
#include <QAbstractListModel>

class TileContentsListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    enum ContentType
    {
        Entity,
        Object,
        VFX
    };

    explicit TileContentsListModel(Map& map_, QObject* parent = nullptr)
        : QAbstractListModel(parent), map(map_)
    {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    void setTile(uint8_t x, uint8_t y, uint8_t layer);

private:
    Map& map;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t layer = 2;

    std::vector<KF2::EntityInstance*> entities;
    std::vector<KF2::ObjectInstance*> objects;
    std::vector<KF2::VFX*> vfxs;
};

#endif // TILECONTENTSLISTMODEL_H

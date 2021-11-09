#ifndef VFXINSTANCETABLEMODEL_H
#define VFXINSTANCETABLEMODEL_H

#include "datahandlers/map.h"
#include "games/kf2.h"
#include <QAbstractTableModel>

class VFXInstanceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    VFXInstanceTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int columnCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent);
        return 1;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return createIndex(row, column);
    }

    int rowCount(const QModelIndex&) const override
    {
        if (vfx == nullptr) return 0;
        return 12;
    }

    void set(KingsFieldII::VFX& vfx_)
    {
        vfx = &vfx_;
        emit layoutChanged();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int, Qt::Orientation, const QVariant&, int) override { return false; }

private:
    KingsFieldII::VFX* vfx;
};

#endif // VFXINSTANCETABLEMODEL_H

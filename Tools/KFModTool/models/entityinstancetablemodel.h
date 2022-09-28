#ifndef ENTITYINSTANCETABLEMODEL_H
#define ENTITYINSTANCETABLEMODEL_H

#include "datahandlers/map.h"
#include "kf2/entity.h"
#include <QAbstractTableModel>

class EntityInstanceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EntityInstanceTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int columnCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
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

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        if (entity == nullptr) return 0;
        return 12;
    }

    void set(KF2::EntityInstance& entity_)
    {
        entity = &entity_;
        emit layoutChanged();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role) Q_UNUSED(orientation)
        return false;
    }

private:
    KF2::EntityInstance* entity = nullptr;
};

#endif // ENTITYINSTANCETABLEMODEL_H

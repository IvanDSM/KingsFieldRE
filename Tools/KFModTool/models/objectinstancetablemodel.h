#ifndef OBJECTINSTANCETABLEMODEL_H
#define OBJECTINSTANCETABLEMODEL_H

#include "datahandlers/map.h"
#include "games/kf2.h"
#include <QAbstractTableModel>

class ObjectInstanceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ObjectInstanceTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

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
        if (object == nullptr) return 0;
        return 19;
    }

    void set(KingsFieldII::ObjectInstance& object_)
    {
        object = &object_;
        emit layoutChanged();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role) Q_UNUSED(orientation)
        return false;
    }

private:
    KingsFieldII::ObjectInstance* object = nullptr;

    QString getFlagLabel(unsigned int flagNo) const;
};

#endif // OBJECTINSTANCETABLEMODEL_H

#ifndef OBJECTINSTANCETABLEMODEL_H
#define OBJECTINSTANCETABLEMODEL_H

#include <QAbstractTableModel>
#include <kftypes.h>

class ObjectInstanceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ObjectInstanceTableModel(QObject *parent,
                                      KingsField::ObjectInstanceDeclaration &objInstance_) :
        QAbstractTableModel(parent),
        objInstance(objInstance_) {}

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
        return 19;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role) Q_UNUSED(orientation)
        return false;
    }

private:
    KingsField::ObjectInstanceDeclaration &objInstance;
};

#endif // OBJECTINSTANCETABLEMODEL_H

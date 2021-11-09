#ifndef MODELOBJECTLISTMODEL_H
#define MODELOBJECTLISTMODEL_H

#include "datahandlers/model.h"
#include <QAbstractTableModel>

class ModelObjectTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelObjectTableModel(QObject* parent, Model& model_)
        : QAbstractTableModel(parent), model(model_)
    {}

    int columnCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return 2;
    }
    
    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;
        else if (index.column() == tickColumn) // Tickbox column
            return Qt::ItemIsUserCheckable | QAbstractItemModel::flags(index);
        
        // Text column
        return QAbstractItemModel::flags(index);
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        Q_UNUSED(section) Q_UNUSED(orientation) Q_UNUSED(role)
        return {};
    }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return createIndex(row, column);
    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        //if (parent.isValid()) return 0;

        return model.baseObjects.size();
    }
    
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role) Q_UNUSED(orientation)
        return false;
    }
        
private:
    Model& model;

    static constexpr int textColumn = 0;
    static constexpr int tickColumn = 1;
};

#endif // MODELOBJECTLISTMODEL_H

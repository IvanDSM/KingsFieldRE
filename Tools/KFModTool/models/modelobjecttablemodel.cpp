#include "modelobjecttablemodel.h"

QVariant ModelObjectTableModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < rowCount(index) && index.row() >= 0)
    {
        if (index.column() == textColumn && role == Qt::DisplayRole)
            return QStringLiteral("Object ") + QString::number(index.row());
        if (index.column() == tickColumn && role == Qt::CheckStateRole)
            return model.baseObjects.at(index.row()).visible ? Qt::Checked : Qt::Unchecked;
    }
    
    return {};
}

bool ModelObjectTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (value.isValid() && role == Qt::CheckStateRole && 
        index.row() < rowCount(index) && index.row() >= 0 
        && index.column() == tickColumn)
    {
        model.baseObjects.at(index.row()).visible = value.toBool();
        emit dataChanged(index, index);
        return true;
    }
    
    return false;
}

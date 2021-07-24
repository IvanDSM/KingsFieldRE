#include "modelanimationlistmodel.h"

QVariant ModelAnimationListModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
        return "Animation " + QString::number(index.row());
    
    return {};
}

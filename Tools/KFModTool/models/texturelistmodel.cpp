#include "texturelistmodel.h"

QVariant TextureListModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole && (index.row() < rowCount(index) && index.row() >= 0 && index.column() == 0))
        return "Texture " + QString::number(index.row());
    
    return {};
}

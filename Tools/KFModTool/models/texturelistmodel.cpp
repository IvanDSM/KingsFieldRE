#include "texturelistmodel.h"
#include <QIcon>

QVariant TextureListModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid()) return {};
    if (role == Qt::DisplayRole)
        return QStringLiteral("Texture ") + QString::number(index.row());
    else if (role == Qt::DecorationRole)
        return QIcon(QPixmap::fromImage(textureDB.getTexture(index.row()).image.scaledToWidth(16)));

    return {};
}

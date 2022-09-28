#include "tilecontentslistmodel.h"

int TileContentsListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return map.entitiesAt(x, y, layer).size() + map.objectsAt(x, y, layer).size()
           + map.vfxsAt(x, y, layer).size();
}

QVariant TileContentsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    // Janky stuff here but it works (?)
    if (index.row() < entities.size())
    {
        if (role == Qt::DisplayRole)
        {
            const auto* entity = entities[index.row()];
            const auto& entityClass = map.getEntityClassDeclaration(entity->EntityClass);
            const auto className = KF2::getEntityMeshName(entityClass.MeshID);
            return QStringLiteral("Entity: %1 (%2)")
                .arg(className, QString::number(entity->EntityClass));
        }
        else if (role == Qt::UserRole)
            return ContentType::Entity;
    }

    if (index.row() - entities.size() < objects.size())
    {
        if (role == Qt::DisplayRole)
        {
            const auto id = objects[index.row() - entities.size()]->ID;
            const auto name = KF2::getObjectName(id);
            return QStringLiteral("Object: %1 (%2)").arg(name).arg(static_cast<int>(id));
        }
        else if (role == Qt::UserRole)
            return ContentType::Object;
    }

    if (index.row() - entities.size() - objects.size() < vfxs.size())
    {
        if (role == Qt::DisplayRole)
        {
            const auto id = map.getVFXInstance(index.row() - entities.size() - objects.size()).VFXID;
            return QStringLiteral("VFX: Type %1").arg(id);
        }
        else if (role == Qt::UserRole)
            return ContentType::VFX;
    }

    return {};
}

QModelIndex TileContentsListModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) return {};

    void* dataPtr = nullptr;

    if (row < entities.size())
        dataPtr = entities[row];
    else if (row - entities.size() < objects.size())
        dataPtr = objects[row - entities.size()];
    else if (row - entities.size() - objects.size() < vfxs.size())
        dataPtr = vfxs[row - entities.size() - objects.size()];

    return createIndex(row, column, dataPtr);
}

void TileContentsListModel::setTile(uint8_t x_, uint8_t y_, uint8_t layer_)
{
    x = x_;
    y = y_;
    layer = layer_;

    entities = map.entitiesAt(x_, y_, layer_);
    objects = map.objectsAt(x_, y_, layer_);
    vfxs = map.vfxsAt(x_, y_, layer_);

    emit layoutChanged();
}

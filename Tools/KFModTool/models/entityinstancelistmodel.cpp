#include "entityinstancelistmodel.h"
#include "core/kfmtcore.h"
#include <utility>

int EntityInstanceListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return Map::entityInstancesSize;
}

QVariant EntityInstanceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    const auto& entity = map.getEntityInstance(index.row());
    auto meshID = KingsFieldII::EntityMeshID::None;
    if (entity.EntityClass < Map::entityClassesSize)
        meshID = map.getEntityClassDeclaration(entity.EntityClass).MeshID;

    // Variable for calculating the RAM address of this entity
    uint32_t ramAddress = 0;
    // Set correct entity array base address
    switch (core.currentVersionedGame())
    {
        case KFMTCore::VersionedGame::KF2U: ramAddress = 0x8016c544; break;
        default: break;
    }
    // FIXME: This still assumes KF2!! As we add support for more games' maps we will need to rework this.
    ramAddress += index.row() * 0x7c;

    auto res = QStringLiteral("%1: %2 instanced at 0x%3")
                   .arg(QString::number(index.row()),
                        KingsFieldII::getEntityMeshName(meshID),
                        QString::number(ramAddress, 16));

    return res;
}

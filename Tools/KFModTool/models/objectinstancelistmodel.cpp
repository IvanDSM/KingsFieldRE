#include "objectinstancelistmodel.h"
#include "core/kfmtcore.h"
#include <utility>

int ObjectInstanceListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return Map::objectInstancesSize;
}

QVariant ObjectInstanceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    const auto& object = map.getObjectInstance(index.row());

    // Variable for calculating the RAM address of this object
    uint32_t ramAddress = 0;
    // Set correct object array base address
    switch (core.currentVersionedGame())
    {
        case KFMTCore::VersionedGame::KF2U: ramAddress = 0x80177714; break;
        default: break;
    }
    // FIXME: This still assumes KF2!! As we add support for more games' maps we will need to rework this.
    ramAddress += index.row() * 0x44;

    return QStringLiteral("%1: %2 instanced at 0x%3")
        .arg(QString::number(index.row()),
             KF2::getObjectName(object.ID),
             QString::number(ramAddress, 16));
}

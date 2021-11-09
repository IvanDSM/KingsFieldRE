#include "shoplistmodel.h"
#include "core/kfmtcore.h"

const std::array<QString, 6> ShopListModel::kf2ShopNames{QStringLiteral(
                                                             "Celffy Foss (Central Village)"),
                                                         QStringLiteral("Raffy Foss"),
                                                         QStringLiteral("Al Hunt"),
                                                         QStringLiteral("Celffy Foss (Station)"),
                                                         QStringLiteral(
                                                             "Radd Bilheim (Crystal Artisan)"),
                                                         QStringLiteral("Mark Wozz (Locksmith)")};

int ShopListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    switch (core.currentVersionedGame())
    {
        case KFMTCore::VersionedGame::KF2E: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_0: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_7: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_8A: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_8B: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2U: return 6;
        default: return 0;
    }
}

QVariant ShopListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    switch (core.currentVersionedGame())
    {
        case KFMTCore::VersionedGame::KF2E: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_0: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_7: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_8A: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2Jv1_8B: [[fallthrough]];
        case KFMTCore::VersionedGame::KF2U: return kf2ShopNames.at(index.row());
        default: return {};
    }
}

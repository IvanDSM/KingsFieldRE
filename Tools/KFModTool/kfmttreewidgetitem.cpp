#include "kfmttreewidgetitem.h"

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Map> kfmtMap) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    mapPtr(std::move(kfmtMap))
{
    dataType = KFMTDataType::KFMT_MAP;
    setIcon(0, QIcon(":/map_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<GameDB> kfmtDB) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dbPtr(std::move(kfmtDB))
{
    dataType = KFMTDataType::KFMT_GAMEDB;
    setIcon(0, QIcon(":/db_icon.png"));
}

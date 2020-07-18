#include "kfmttreewidgetitem.h"

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, Map* kfmtMap) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    mapPtr(kfmtMap)
{
    dataType = KFMTDataType::KFMT_MAP;
    setIcon(0, QIcon(":/map_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, GameDB *kfmtDB) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dbPtr(kfmtDB)
{
    dataType = KFMTDataType::KFMT_GAMEDB;
    setIcon(0, QIcon(":/db_icon.png"));
}

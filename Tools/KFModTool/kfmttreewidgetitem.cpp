#include "kfmttreewidgetitem.h"

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, Map* kfmtMap) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    mapPtr(kfmtMap)
{
    dataType = KFMTDataType::KFMT_MAP;
    setIcon(0, QIcon(":/map_icon.png"));
}

std::shared_ptr<Map> KFMTTreeWidgetItem::getMap()
{
    return mapPtr;
}

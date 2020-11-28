#include "kfmttreewidgetitem.h"

#include <utility>

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<GameDB> kfmtDB) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_GAMEDB),
    dbPtr(std::move(kfmtDB))
{
    setIcon(0, QIcon(":/db_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Map> kfmtMap) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_MAP),
    mapPtr(std::move(kfmtMap))
{
    setIcon(0, QIcon(":/map_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Model> kfmtModel) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_MODEL),
    modelPtr(std::move(kfmtModel))
{
    setIcon(0, QIcon(":/3d_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Texture> kfmtTexture) : 
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_TEXTURE),
    texPtr(std::move(kfmtTexture))
{
    setIcon(0, QIcon(":/tex_icon.png"));
}

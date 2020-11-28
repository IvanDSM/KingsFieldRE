#include "kfmttreewidgetitem.h"

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<GameDB> kfmtDB) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_GAMEDB),
    dbPtr(kfmtDB)
{
    setIcon(0, QIcon(":/db_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Map> kfmtMap) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_MAP),
    mapPtr(kfmtMap)
{
    setIcon(0, QIcon(":/map_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Model> kfmtModel) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_MODEL),
    modelPtr(kfmtModel)
{
    setIcon(0, QIcon(":/3d_icon.png"));
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem *parent, std::shared_ptr<Texture> kfmtTexture) : 
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(KFMTDataType::KFMT_TEXTURE),
    texPtr(kfmtTexture)
{
    setIcon(0, QIcon(":/tex_icon.png"));
}

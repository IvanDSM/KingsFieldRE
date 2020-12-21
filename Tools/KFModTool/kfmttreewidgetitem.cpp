#include "kfmttreewidgetitem.h"
#include <utility>

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem * parent,
                                       QByteArray & file_, KFMTDataType type) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(type), file(file_)
{
    switch (type)
    {
        case KFMTDataType::KFMT_GAMEDB:
            setIcon(0, QIcon(":/db_icon.png"));
            break;
        case KFMTDataType::KFMT_MAP:
            KFMTError::error("KFMTTreeWidgetItem: Tried to build map widget the wrong way!");
            break;
        case KFMTDataType::KFMT_MODEL:
            setIcon(0, QIcon(":/3d_icon.png"));
            break;
        case KFMTDataType::KFMT_TEXTUREDB:
            setIcon(0, QIcon(":/tex_icon.png"));
            break;
        default:
            break;
    }
}

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem * parent, QByteArray & mapFile1, 
                                       QByteArray & mapFile2_, QByteArray & mapFile3_, 
                                       KFMTDataType type) : QTreeWidgetItem(parent, QTreeWidgetItem::UserType), 
                          dataType(type), file(mapFile1), mapFile2(&mapFile2_), mapFile3(&mapFile3_)
{
    setIcon(0, QIcon(":/map_icon.png"));
}

void KFMTTreeWidgetItem::build()
{
    if (getType() == KFMTDataType::KFMT_GAMEDB && dbPtr == nullptr)
        dbPtr.reset(new GameDB(file));
    else if (getType() == KFMTDataType::KFMT_MAP && mapPtr == nullptr)
        mapPtr.reset(new Map(file, *mapFile2, *mapFile3));
    else if (getType() == KFMTDataType::KFMT_MODEL && modelPtr == nullptr)
        modelPtr.reset(new Model(file));
    else if (getType() == KFMTDataType::KFMT_TEXTUREDB && texDBPtr == nullptr)
        texDBPtr.reset(new TextureDB(file));
}

void KFMTTreeWidgetItem::writeChanges()
{
    if (getType() == KFMTDataType::KFMT_GAMEDB && dbPtr != nullptr)
        dbPtr->writeChanges();
    else if (getType() == KFMTDataType::KFMT_MAP && mapPtr != nullptr)
        mapPtr->writeChanges();
//    else if (getType() == KFMTDataType::KFMT_MODEL && modelPtr != nullptr)
//        modelPtr->writeChanges();
    else if (getType() == KFMTDataType::KFMT_TEXTUREDB && texDBPtr != nullptr)
        texDBPtr->writeChanges();
}

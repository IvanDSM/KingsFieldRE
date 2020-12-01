#include "kfmttreewidgetitem.h"
#include <utility>

KFMTTreeWidgetItem::KFMTTreeWidgetItem(QTreeWidgetItem * parent,
                                       TFile & tFile_, unsigned int fileIndex, KFMTDataType type) :
    QTreeWidgetItem(parent, QTreeWidgetItem::UserType),
    dataType(type), tFile(tFile_), index(fileIndex)
{
    switch (type)
    {
        case KFMTDataType::KFMT_GAMEDB:
            setIcon(0, QIcon(":/db_icon.png"));
            break;
        case KFMTDataType::KFMT_MAP:
            setIcon(0, QIcon(":/map_icon.png"));
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

void KFMTTreeWidgetItem::build()
{
    if (getType() == KFMTDataType::KFMT_GAMEDB && dbPtr == nullptr)
        dbPtr.reset(new GameDB(tFile, index));
    else if (getType() == KFMTDataType::KFMT_MAP && mapPtr == nullptr)
        mapPtr.reset(new Map(tFile, index));
    else if (getType() == KFMTDataType::KFMT_MODEL && modelPtr == nullptr)
        modelPtr.reset(new Model(tFile, index));
    else if (getType() == KFMTDataType::KFMT_TEXTUREDB && texDBPtr == nullptr)
        texDBPtr.reset(new TextureDB(tFile, index));
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

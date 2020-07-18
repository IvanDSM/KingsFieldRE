#ifndef KFMTTREEWIDGETITEM_H
#define KFMTTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "gamedb.h"
#include "map.h"

enum class KFMTDataType
{
    KFMT_MAP,
    KFMT_GAMEDB
};

class KFMTTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit KFMTTreeWidgetItem(QTreeWidgetItem *parent, Map* kfmtMap);
    explicit KFMTTreeWidgetItem(QTreeWidgetItem *parent, GameDB* kfmtDB);

    std::shared_ptr<GameDB> getDB()
    {
        if (dataType == KFMTDataType::KFMT_GAMEDB)
            return dbPtr;
        else
            return nullptr;
    }

    std::shared_ptr<Map> getMap()
    {
        if (dataType == KFMTDataType::KFMT_MAP)
            return mapPtr;
        else
            return nullptr;
    }

    KFMTDataType getType()
    {
        return dataType;
    }

private:
    KFMTDataType dataType;
    std::shared_ptr<GameDB> dbPtr;
    std::shared_ptr<Map> mapPtr;
};

#endif // KFMTTREEWIDGETITEM_H

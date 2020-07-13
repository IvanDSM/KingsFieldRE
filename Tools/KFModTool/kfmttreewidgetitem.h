#ifndef KFMTTREEWIDGETITEM_H
#define KFMTTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "map.h"

enum class KFMTDataType
{
    KFMT_MAP
};

class KFMTTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit KFMTTreeWidgetItem(QTreeWidgetItem *parent, Map* kfmtMap);
    std::shared_ptr<Map> getMap();
    KFMTDataType getType()
    {
        return dataType;
    }

private:
    KFMTDataType dataType;
    std::shared_ptr<Map> mapPtr;
};

#endif // KFMTTREEWIDGETITEM_H

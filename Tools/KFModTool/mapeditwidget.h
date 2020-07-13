#ifndef MAPDOCKWIDGET_H
#define MAPDOCKWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include "map.h"

namespace Ui {
    class MapEditWidget;
}

class MapEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapEditWidget(QWidget *parent = nullptr);
    void setMap(std::shared_ptr<Map> map);
    ~MapEditWidget();

private slots:
    void on_layer1Radio_toggled(bool checked);

    void on_layer2Radio_toggled(bool checked);

    void on_entityCDCombo_currentIndexChanged(int index);

    void entityInstanceHovered(byte instanceIndex);

    void objectInstanceHovered(size_t instanceIndex);

    void on_zoneDelimCheck_stateChanged(int arg1);

    void on_entityInstanceTable_itemChanged(QTableWidgetItem *item);

    void on_entityCDTable_itemChanged(QTableWidgetItem *item);

    void on_objectInstanceTable_itemChanged(QTableWidgetItem *item);

private:
    void fillEntityCDCombo();
    byte currentEntityInstance = 255;
    size_t currentObjectInstance = 65536;
    std::shared_ptr<Map> curMap;
    Ui::MapEditWidget *ui;
};

#endif // MAPDOCKWIDGET_H

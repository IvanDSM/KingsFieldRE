#ifndef MAPDOCKWIDGET_H
#define MAPDOCKWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include "map.h"
#include "ui_mapeditwidget.h"

class MapEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapEditWidget(QWidget *parent = nullptr);
    void setMap(const std::shared_ptr<Map> &map);

private slots:
    void on_layer1Radio_toggled(bool checked);

    void on_layer2Radio_toggled(bool checked);

    void on_entityCDCombo_currentIndexChanged(int index);

    void entityInstanceHovered(byte instanceIndex);

    void hoveredTileInfo(byte elevation, byte rotation, byte collisionThing, byte zoneDelimiter,
                         byte tileId);

    void objectInstanceHovered(size_t instanceIndex);

    void on_zoneDelimCheck_stateChanged(int arg1);

    void on_entityInstanceTable_itemChanged(QTableWidgetItem *item)
    {
        Q_UNUSED(item)
        curMap->setChanged();
    }

    void on_entityCDTable_itemChanged(QTableWidgetItem *item)
    {
        Q_UNUSED(item)
        curMap->setChanged();
    }

    void on_objectInstanceTable_itemChanged(QTableWidgetItem *item)
    {
        Q_UNUSED(item)
        curMap->setChanged();
    }

    void on_elementCombo_currentIndexChanged(int index);

    void on_pokeModeButton_clicked();

    void on_paintModeButton_clicked();

    void on_brushSpin_valueChanged(int arg1);

    void on_brushElemCombo_currentIndexChanged(int index);

    void on_fillModeButton_clicked();

    void on_entityCDImport_clicked();

    void on_entityCDExport_clicked();

    void on_entityInstanceImport_clicked();

    void on_entityInstanceExport_clicked();

    void on_moveModeButton_clicked();

private:
    void fillEntityCDCombo();
    byte currentEntityInstance = 255;
    size_t currentObjectInstance = 65536;
    std::shared_ptr<Map> curMap;
    std::unique_ptr<Ui::MapEditWidget> ui;
};

#endif // MAPDOCKWIDGET_H

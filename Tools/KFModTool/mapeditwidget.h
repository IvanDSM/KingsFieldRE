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
    ~MapEditWidget() { delete ui; }
    
    void setMap(const std::shared_ptr<Map> &map);

private slots:
    // Current X changes
    
    void changeEntityInstance(int instanceIndex);
    
    void changeObjectInstance(int instanceIndex);

    void changeVFXInstance(int instanceIndex);

    // Other stuff    
    
    void on_layer1Radio_toggled(bool checked);

    void on_layer2Radio_toggled(bool checked);

    void on_entityCDCombo_currentIndexChanged(int index);

    void curMousePosChanged(qint8 x, qint8 y);

    void hoveredTileInfo(byte elevation, byte rotation, byte collisionThing, byte zoneDelimiter,
                         byte tileId);

    void on_zoneDelimCheck_stateChanged(int arg1);

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

    void on_entityCDTable_activated(const QModelIndex &index);
    
    void on_offsetSpin_valueChanged(int arg1);
    
private:
    void fillEntityCDCombo();
    void updateEntityInstanceTable();
    void updateObjectInstanceTable();
    void updateVFXInstanceTable();
    int curEntityInstance = -1;
    int curObjectInstance = -1;
    int curVFXInstance = -1;
    std::shared_ptr<Map> curMap;
    Ui::MapEditWidget *ui;
};

#endif // MAPDOCKWIDGET_H

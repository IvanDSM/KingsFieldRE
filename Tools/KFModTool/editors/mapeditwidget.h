#ifndef MAPDOCKWIDGET_H
#define MAPDOCKWIDGET_H

#include "editors/kfmteditor.h"
#include "models/entityclasstablemodel.h"
#include "models/entityinstancetablemodel.h"
#include "models/objectinstancetablemodel.h"
#include "models/tilecontentslistmodel.h"
#include "models/vfxinstancetablemodel.h"
#include "ui_mapeditwidget.h"
#include <QWidget>

class MapEditWidget : public KFMTEditor
{
    Q_OBJECT

public:
    explicit MapEditWidget(KFMTFile& tilemap,
                           KFMTFile& db,
                           KFMTFile& script,
                           QWidget* parent = nullptr);
    ~MapEditWidget() { delete ui; }

private:
    // Models
    std::unique_ptr<Model> tileset = nullptr;
    EntityClassTableModel entityClassModel{this};
    EntityInstanceTableModel entityModel{this};
    ObjectInstanceTableModel objectModel{this};
    std::unique_ptr<TileContentsListModel> tileContentsModel = nullptr;
    VFXInstanceTableModel vfxModel{this};

    void getTileset(size_t mapIndex);
    void setCurTile(size_t tileIndex);

    KF2::Tile* curTile = nullptr;
    Ui::MapEditWidget* ui;

private slots:
    void pickedTile(KF2::Tile& tile, uint8_t x, uint8_t y);

    void on_layerCombo_currentIndexChanged(int index);

    void on_tileIDSpin_valueChanged(int tileIndex) { setCurTile(tileIndex); }

    void on_layerChangeCheck_stateChanged(int arg1);

    void on_enemyPassCheck_stateChanged(int arg1);

    void on_rotationSpin_currentIndexChanged(int index);

    void on_elevationBtn_clicked();

    void on_collisionBtn_clicked();

    void on_tileIDBtn_clicked();
    void on_inTileList_clicked(const QModelIndex& index);
};

#endif // MAPDOCKWIDGET_H

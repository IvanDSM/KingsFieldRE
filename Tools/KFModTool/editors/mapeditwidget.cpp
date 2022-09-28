#include "mapeditwidget.h"
#include "core/kfmtcore.h"
#include "datahandlers/map.h"
#include <memory>
#include <QFileDialog>
#include <QMessageBox>

MapEditWidget::MapEditWidget(KFMTFile& tilemap, KFMTFile& db, KFMTFile& script, QWidget* parent)
    : KFMTEditor(tilemap, parent), ui(new Ui::MapEditWidget)
{
    handler = std::make_unique<Map>(tilemap, db, script);
    // Get a handy reference to the map
    auto& map = *reinterpret_cast<Map*>(handler.get());

    ui->setupUi(this);
    ui->entityClassContainer->setVisible(false);
    ui->mapViewWidget->setMap(map);
    ui->mapViewer3D->setMap(map);

    // Connect map viewer picked tile signal
    connect(ui->mapViewWidget, &MapViewer::pickedTile, this, &MapEditWidget::pickedTile);

    // Initialize models
    tileContentsModel = std::make_unique<TileContentsListModel>(map, this);

    // Set the tile contents list view to use the model we created
    ui->entityClassTable->setModel(&entityClassModel);
    ui->inTileList->setModel(tileContentsModel.get());

    // Fill Selected Tile with the info fram the first tile on the second layer
    pickedTile(map.getTile(0, 0, 2), 0, 0);

    // Fetches appropriate tileset for the tileViewer
    auto mapIndex = tilemap.filePath.midRef(tilemap.filePath.indexOf(QRegExp("[0-9]"))).toUInt();
    getTileset(mapIndex);
}

void MapEditWidget::getTileset(size_t mapIndex)
{
    switch (core.currentGame())
    {
        case KFMTCore::SimpleGame::KF2: [[fallthrough]];
        case KFMTCore::SimpleGame::KF3: [[fallthrough]];
        case KFMTCore::SimpleGame::KFPS:
            tileset = std::make_unique<Model>(*core.getFile("RTMD.T", mapIndex / 3));
            break;
        default: return;
    }
    ui->tileIDSpin->setMaximum(tileset->baseObjects.size() - 1);
    ui->tileViewer->setModel(*tileset);
}

void MapEditWidget::setCurTile(size_t tileIndex)
{
    if (tileset == nullptr) return;

    for (auto& m : tileset->baseObjects) m.visible = false;
    tileset->baseObjects[tileIndex].visible = true;
    ui->tileViewer->repaint();
}

void MapEditWidget::pickedTile(KF2::Tile& tile, uint8_t x, uint8_t y)
{
    curTile = &tile;

    ui->elevationSpin->setValue(tile.Elevation);
    ui->rotationSpin->setCurrentIndex(tile.Rotation);
    ui->collisionSpin->setValue(tile.CollisionIndex);
    ui->enemyPassCheck->setChecked(tile.getEnemyBlock());
    ui->layerChangeCheck->setChecked(tile.getSwitchLayer());

    ui->tileIDSpin->setValue(tile.TileID);
    tileContentsModel->setTile(x, y, ui->layerCombo->currentIndex() + 1);
}

void MapEditWidget::on_layerCombo_currentIndexChanged(int index)
{
    if (index != 0 && index != 1)
        KFMTError::fatalError(QStringLiteral("Layercombo didn't return 0 or 1"));
    ui->mapViewWidget->setLayer(static_cast<MapViewer::MapLayer>(index + 1));
}

void MapEditWidget::on_layerChangeCheck_stateChanged(int arg1)
{
    if (curTile == nullptr) return;

    curTile->setSwitchLayer(arg1 == Qt::Checked);
    ui->mapViewWidget->refreshMapViewer();
}

void MapEditWidget::on_enemyPassCheck_stateChanged(int arg1)
{
    if (curTile == nullptr) return;

    curTile->setEnemyBlock(arg1 == Qt::Checked);
    ui->mapViewWidget->refreshMapViewer();
}

void MapEditWidget::on_rotationSpin_currentIndexChanged(int index)
{
    if (curTile == nullptr) return;

    curTile->Rotation = static_cast<uint8_t>(index);
}

void MapEditWidget::on_elevationBtn_clicked()
{
    if (curTile == nullptr) return;

    curTile->Elevation = ui->elevationSpin->value();
}

void MapEditWidget::on_collisionBtn_clicked()
{
    if (curTile == nullptr) return;

    curTile->CollisionIndex = ui->collisionSpin->value();
}

void MapEditWidget::on_tileIDBtn_clicked()
{
    if (curTile == nullptr) return;

    curTile->TileID = ui->tileIDSpin->value();
}

void MapEditWidget::on_inTileList_clicked(const QModelIndex& index)
{
    switch (index.data(Qt::UserRole).toInt())
    {
        case TileContentsListModel::ContentType::Entity:
            ui->entityClassContainer->setVisible(true);
            entityModel.set(
                *reinterpret_cast<KF2::EntityInstance*>(index.internalPointer()));
            entityClassModel.setFromEntity(*reinterpret_cast<KF2::EntityInstance*>(
                                               index.internalPointer()),
                                           *reinterpret_cast<Map*>(handler.get()));

            ui->inTileTable->setModel(&entityModel);
            break;
        case TileContentsListModel::ContentType::Object:
            ui->entityClassContainer->setVisible(false);
            objectModel.set(
                *reinterpret_cast<KF2::ObjectInstance*>(index.internalPointer()));

            ui->inTileTable->setModel(&objectModel);
            break;
        case TileContentsListModel::ContentType::VFX:
            ui->entityClassContainer->setVisible(false);
            vfxModel.set(*reinterpret_cast<KF2::VFX*>(index.internalPointer()));

            ui->inTileTable->setModel(&vfxModel);
            break;
        default:
            KFMTError::warning(
                QStringLiteral("MapEditWidget::on_inTileList_clicked: Unhandled content type %1")
                    .arg(index.data(Qt::UserRole).toInt()));
    }
}

#include "mapeditwidget.h"
#include "models/entityclasstablemodel.h"
#include "models/entityinstancetablemodel.h"
#include "models/objectinstancetablemodel.h"
#include <QFileDialog>
#include <QMessageBox>

MapEditWidget::MapEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapEditWidget)
{
    ui->setupUi(this);
    ui->mapViewWidget->setMap(curMap);

    connect(ui->mapViewWidget, &MapViewer::entityInstanceHovered,
            this, &MapEditWidget::entityInstanceHovered);
    connect(ui->mapViewWidget, &MapViewer::hoveredTileInfo,
            this, &MapEditWidget::hoveredTileInfo);
    connect(ui->mapViewWidget, &MapViewer::objectInstanceHovered,
            this, &MapEditWidget::objectInstanceHovered);

    ui->entityCDTable->horizontalHeader()->show();
    ui->entityCDTable->verticalHeader()->show();

    ui->entityInstanceTable->horizontalHeader()->show();
    ui->entityInstanceTable->verticalHeader()->show();

    ui->objectInstanceTable->horizontalHeader()->show();
    ui->objectInstanceTable->verticalHeader()->show();
}

void MapEditWidget::setMap(const std::shared_ptr<Map> &map)
{
    curMap = map;
    ui->mapViewWidget->setMap(map);
    fillEntityCDCombo();
}

void MapEditWidget::on_layer1Radio_toggled(bool checked)
{
    if (checked)
        ui->mapViewWidget->setLayer(MapViewer::MapLayer::LAYER_1);
}

void MapEditWidget::on_layer2Radio_toggled(bool checked)
{
    if (checked)
        ui->mapViewWidget->setLayer(MapViewer::MapLayer::LAYER_2);
}

void MapEditWidget::fillEntityCDCombo()
{
    ui->entityCDCombo->clear();
    byte curEntityIndex = 0;
    for (auto entityCD : curMap->getEntityClassDeclarations())
    {
        ui->entityCDCombo->addItem(QString::number(curEntityIndex) + ": " + KingsField::getEntityMeshName(entityCD.MeshID));
        curEntityIndex++;
    }
}

void MapEditWidget::on_entityCDCombo_currentIndexChanged(int index)
{
    KingsField::EntityClassDeclaration &entityClassDecl = curMap->getClassDeclaration(index);

    ui->entityCDTable->setModel(new EntityClassTableModel(ui->entityCDTable, entityClassDecl));

}

void MapEditWidget::entityInstanceHovered(byte instanceIndex)
{
    KingsField::EntityInstance &instance = curMap->getInstance(instanceIndex);
    currentEntityInstance = instanceIndex;

    auto address = QString::number(0x8016c544 + (instanceIndex * 0x7c), 16);
    ui->entityInstanceAddrLabel->setText("Instance " + QString::number(instanceIndex) +
                                         ", at address " + address);

    ui->entityInstanceTable->setModel(new EntityInstanceTableModel(ui->entityInstanceTable,
                                                                   instance));

    ui->entityCDCombo->setCurrentIndex(instance.EntityClass);
}

void MapEditWidget::hoveredTileInfo(byte elevation, byte rotation, byte collisionThing,
                                    byte zoneDelimiter, byte tileId)
{
    ui->elevLabel->setText("Elevation: " + QString::number(elevation));
    ui->rotLabel->setText("Rotation: " + QString::number(rotation) + " (" + QString::number(rotation * 90) + "°)");
    ui->colThingLabel->setText("Collision Thing: " + QString::number(collisionThing));
    ui->zoneDelimLabel->setText("Zone Delimiter: " + QString::number(zoneDelimiter));
    ui->tileIdLabel->setText("Tile ID: " + QString::number(tileId));

}

void MapEditWidget::objectInstanceHovered(size_t instanceIndex)
{
    KingsField::ObjectInstanceDeclaration &instance = curMap->getObjectInstance(instanceIndex);
    currentObjectInstance = instanceIndex;

    auto address = QString::number(0x80177714 + (instanceIndex * 0x44), 16);
    ui->objectInstanceAddrLabel->setText("Instance " + QString::number(instanceIndex) +
                                         ", at address " + address);

    ui->objectInstanceTable->setModel(new ObjectInstanceTableModel(ui->entityInstanceTable,
                                                                   instance));
}

void MapEditWidget::on_zoneDelimCheck_stateChanged(int arg1)
{
    ui->mapViewWidget->setDrawZoneDelimiters((arg1 == Qt::Checked));
}

void MapEditWidget::on_elementCombo_currentIndexChanged(int index)
{
    auto elem = static_cast<MapViewer::MapElement>(index);
    ui->mapViewWidget->setElement(elem);
}

void MapEditWidget::on_pokeModeButton_clicked()
{
    ui->mapViewWidget->setMode(MapViewer::MapViewerMode::MODE_POKE);
}

void MapEditWidget::on_paintModeButton_clicked()
{
    ui->mapViewWidget->setMode(MapViewer::MapViewerMode::MODE_PAINT);
}

void MapEditWidget::on_brushSpin_valueChanged(int arg1)
{
    ui->mapViewWidget->setBrush(static_cast<byte>(arg1));
}

void MapEditWidget::on_brushElemCombo_currentIndexChanged(int index)
{
    auto newElem = static_cast<MapViewer::MapElement>(index);
    if (newElem == MapViewer::MapElement::MAP_ROTATION)
        ui->brushSpin->setMaximum(3);
    else
        ui->brushSpin->setMaximum(255);
    ui->mapViewWidget->setBrushElement(newElem);
}

void MapEditWidget::on_fillModeButton_clicked()
{
    ui->mapViewWidget->setMode(MapViewer::MapViewerMode::MODE_FILL);
}

void MapEditWidget::on_moveModeButton_clicked()
{
    ui->mapViewWidget->setMode(MapViewer::MapViewerMode::MODE_MOVE);
}

void MapEditWidget::on_entityCDImport_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this, "Import entity class declaration...",
                                                 QDir::homePath(),
                                                 "Entity Class Declarations (*.kfmt_ecd)");
    if (!filename.isEmpty())
    {
        QFile file(filename, this);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Failed to open file!",
                                  "Failed to open " + filename + " for reading!");
            return;
        }
        auto entityCD = file.readAll();
        file.close();
        auto index = ui->entityCDCombo->currentIndex();
        curMap->getClassDeclaration(index) = entityCD;
        fillEntityCDCombo();
        ui->entityCDCombo->setCurrentIndex(index);
        on_entityCDCombo_currentIndexChanged(index); // FIXME: Dirty hack. Do something proper.
    }
}

void MapEditWidget::on_entityCDExport_clicked()
{
    auto filename = QFileDialog::getSaveFileName(this, "Export entity class declaration as...",
                                                 QDir::homePath(),
                                                 "Entity Class Declarations (*.kfmt_ecd)");
    if (!filename.isEmpty())
    {
        if (!filename.endsWith(".kfmt_ecd"))
            filename.append(".kfmt_ecd");
        QByteArray entityCD = curMap->getClassDeclaration(ui->entityCDCombo->currentIndex());
        QFile file(filename, this);
        if (!file.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, "Failed to open file!",
                                  "Failed to open " + filename + " for writing!");
            return;
        }
        file.write(entityCD);
        file.close();
        QMessageBox::information(this, "Export successful!",
                                 "Entity Class Declaration exported successfully!");
    }
}

void MapEditWidget::on_entityInstanceImport_clicked()
{
    if (currentEntityInstance != 255)
    {
        QMessageBox::information(this, "Warning!", "Entity instace import/export is buggy!");

        auto filename = QFileDialog::getOpenFileName(this, "Import entity instance declaration...",
                                                     QDir::homePath(),
                                                     "Entity Instance Declaration (*.kfmt_eid)");
        if (!filename.isEmpty())
        {
            QFile file(filename, this);
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, "Failed to open file!",
                                      "Failed to open " + filename + " for reading!");
                return;
            }
            auto entityInstance = file.readAll();
            file.close();
            curMap->getInstance(currentEntityInstance) = entityInstance;
            entityInstanceHovered(currentEntityInstance); // FIXME: Dirty hack. Do something proper.
        }
    }
}

void MapEditWidget::on_entityInstanceExport_clicked()
{
    if (currentEntityInstance != 255)
    {
        QMessageBox::information(this, "Warning!", "Entity instace import/export is buggy!");
        auto filename = QFileDialog::getSaveFileName(this, "Export entity instance declaration as...",
                                                     QDir::homePath(),
                                                     "Entity Instance Declarations (*.kfmt_eid)");
        if (!filename.isEmpty())
        {
            if (!filename.endsWith(".kfmt_eid"))
                filename.append(".kfmt_eid");
            QByteArray entityInstance = curMap->getInstance(currentEntityInstance);
            QFile file(filename, this);
            if (!file.open(QIODevice::ReadWrite))
            {
                QMessageBox::critical(this, "Failed to open file!",
                                      "Failed to open " + filename + " for writing!");
                return;
            }
            file.write(entityInstance);
            file.close();
            QMessageBox::information(this, "Export successful!",
                                     "Entity Instance Declaration exported successfully!");
        }
    }
}

#include "mapeditwidget.h"
#include "ui_mapeditwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "models/entityclasstablemodel.h"
#include "models/entityinstancetablemodel.h"

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
}

void MapEditWidget::setMap(std::shared_ptr<Map> map)
{
    curMap = map;
    ui->mapViewWidget->setMap(map);
    fillEntityCDCombo();
}

MapEditWidget::~MapEditWidget()
{
    delete ui;
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
    ui->rotLabel->setText("Rotation: " + QString::number(rotation * 90) + "°");
    ui->colThingLabel->setText("Collision Thing: " + QString::number(collisionThing));
    ui->zoneDelimLabel->setText("Zone Delimiter: " + QString::number(zoneDelimiter));
    ui->tileIdLabel->setText("Tile ID: " + QString::number(tileId));

}

void MapEditWidget::objectInstanceHovered(size_t instanceIndex)
{
    auto instance = curMap->getObjectInstanceDeclarations()[instanceIndex];
    currentObjectInstance = instanceIndex;

    auto address = QString::number(0x80177714 + (instanceIndex * 0x44), 16);
    ui->objectInstanceAddrLabel->setText("Instance " + QString::number(instanceIndex) +
                                         ", at address " + address);

    QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(instance.TileLayer));
    ui->objectInstanceTable->setItem(0, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(instance.WEXTilePos));
    ui->objectInstanceTable->setItem(0, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(instance.NSYTilePos));
    ui->objectInstanceTable->setItem(0, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(instance.field_0x3));
    ui->objectInstanceTable->setItem(0, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(KingsField::getObjectIDAsUShort(instance.ObjectID))
                                                   + " ("
                                                   + KingsField::getObjectName(instance.ObjectID)
                                                   + ")");
    ui->objectInstanceTable->setItem(0, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(instance.ZRotation));
    ui->objectInstanceTable->setItem(0, 5, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(instance.FineWEXPos));
    ui->objectInstanceTable->setItem(0, 6, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(instance.FineNSYPos));
    ui->objectInstanceTable->setItem(0, 7, item7);
    QTableWidgetItem *item8 = new QTableWidgetItem(QString::number(instance.FineZPos));
    ui->objectInstanceTable->setItem(0, 8, item8);
    QTableWidgetItem *item9 = new QTableWidgetItem(QString::number(instance.Flags[0]));
    ui->objectInstanceTable->setItem(0, 9, item9);
    QTableWidgetItem *item10 = new QTableWidgetItem(QString::number(instance.Flags[1]));
    ui->objectInstanceTable->setItem(0, 10, item10);
    QTableWidgetItem *item11 = new QTableWidgetItem(QString::number(instance.Flags[2]));
    ui->objectInstanceTable->setItem(0, 11, item11);
    QTableWidgetItem *item12 = new QTableWidgetItem(QString::number(instance.Flags[3]));
    ui->objectInstanceTable->setItem(0, 12, item12);
    QTableWidgetItem *item13 = new QTableWidgetItem(QString::number(instance.Flags[4]));
    ui->objectInstanceTable->setItem(0, 13, item13);
    QTableWidgetItem *item14 = new QTableWidgetItem(QString::number(instance.Flags[5]));
    ui->objectInstanceTable->setItem(0, 14, item14);
    QTableWidgetItem *item15 = new QTableWidgetItem(QString::number(instance.Flags[6]));
    ui->objectInstanceTable->setItem(0, 15, item15);
    QTableWidgetItem *item16 = new QTableWidgetItem(QString::number(instance.Flags[7]));
    ui->objectInstanceTable->setItem(0, 16, item16);
    QTableWidgetItem *item17 = new QTableWidgetItem(QString::number(instance.Flags[8]));
    ui->objectInstanceTable->setItem(0, 17, item17);
    QTableWidgetItem *item18 = new QTableWidgetItem(QString::number(instance.Flags[9]));
    ui->objectInstanceTable->setItem(0, 18, item18);
}

void MapEditWidget::on_zoneDelimCheck_stateChanged(int arg1)
{
    ui->mapViewWidget->setDrawZoneDelimiters((arg1 == Qt::Checked));
}

void MapEditWidget::on_entityInstanceTable_itemChanged(QTableWidgetItem *item)
{
    curMap->setChanged();
}

void MapEditWidget::on_entityCDTable_itemChanged(QTableWidgetItem *item)
{
    curMap->setChanged();
}

void MapEditWidget::on_objectInstanceTable_itemChanged(QTableWidgetItem *item)
{
    KingsField::ObjectInstanceDeclaration &instance = curMap->getObjectInstance(currentObjectInstance);
    switch(item->row())
    {
        case (0): instance.TileLayer = item->text().toUShort(); break;
        case (1): instance.WEXTilePos = item->text().toUShort(); break;
        case (2): instance.NSYTilePos = item->text().toUShort(); break;
        case (3): instance.field_0x3 = item->text().toUShort(); break;
        case (4): instance.ObjectID = KingsField::getObjectIDFromUShort(item->text().leftRef(3).toUShort()); break;
        case (5): instance.ZRotation = item->text().toShort(); break;
        case (6): instance.FineWEXPos = item->text().toShort(); break;
        case (7): instance.FineNSYPos = item->text().toShort(); break;
        case (8): instance.FineZPos = item->text().toShort(); break;
        case (9): instance.Flags[0] = item->text().toUShort(); break;
        case (10): instance.Flags[1] = item->text().toUShort(); break;
        case (11): instance.Flags[2] = item->text().toUShort(); break;
        case (12): instance.Flags[3] = item->text().toUShort(); break;
        case (13): instance.Flags[4] = item->text().toUShort(); break;
        case (14): instance.Flags[5] = item->text().toUShort(); break;
        case (15): instance.Flags[6] = item->text().toUShort(); break;
        case (16): instance.Flags[7] = item->text().toUShort(); break;
        case (17): instance.Flags[8] = item->text().toUShort(); break;
        case (18): instance.Flags[9] = item->text().toUShort(); break;
    }
    curMap->setChanged();
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
    ui->mapViewWidget->setBrushElement(static_cast<MapViewer::MapElement>(index));
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
        curMap->setChanged();
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
            curMap->setChanged();
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

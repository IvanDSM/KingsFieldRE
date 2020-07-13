#include "mapeditwidget.h"
#include "ui_mapeditwidget.h"

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
    byte curEntityIndex = 0;
    for (auto entityCD : curMap->getEntityClassDeclarations())
    {
        ui->entityCDCombo->addItem(QString::number(curEntityIndex) + ": " + KingsField::getEntityMeshName(entityCD.MeshID));
        curEntityIndex++;
    }
}

void MapEditWidget::on_entityCDCombo_currentIndexChanged(int index)
{
    auto entity = curMap->getEntityClassDeclarations()[index];

    QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(KingsField::getEntityMeshIDAsByte(entity.MeshID)));
    ui->entityCDTable->setItem(0, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(entity.FourOrForty));
    ui->entityCDTable->setItem(0, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(entity.field_0x2));
    ui->entityCDTable->setItem(0, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(entity.field_0x3));
    ui->entityCDTable->setItem(0, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(entity.field_0x4));
    ui->entityCDTable->setItem(0, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(entity.field_0x5));
    ui->entityCDTable->setItem(0, 5, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(entity.field_0x6));
    ui->entityCDTable->setItem(0, 6, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(entity.field_0x7));
    ui->entityCDTable->setItem(0, 7, item7);
    QTableWidgetItem *item8 = new QTableWidgetItem(QString::number(entity.field_0x8));
    ui->entityCDTable->setItem(0, 8, item8);
    QTableWidgetItem *item9 = new QTableWidgetItem(QString::number(entity.field_0x9));
    ui->entityCDTable->setItem(0, 9, item9);
    QTableWidgetItem *item10 = new QTableWidgetItem(QString::number(entity.field_0xa));
    ui->entityCDTable->setItem(0, 10, item10);
    QTableWidgetItem *item11 = new QTableWidgetItem(QString::number(entity.field_0xb));
    ui->entityCDTable->setItem(0, 11, item11);
    QTableWidgetItem *item12 = new QTableWidgetItem(QString::number(entity.field_0xc));
    ui->entityCDTable->setItem(0, 12, item12);
    QTableWidgetItem *item13 = new QTableWidgetItem(QString::number(entity.field_0xd));
    ui->entityCDTable->setItem(0, 13, item13);
    QTableWidgetItem *item14 = new QTableWidgetItem(QString::number(entity.field_0xe));
    ui->entityCDTable->setItem(0, 14, item14);
    QTableWidgetItem *item15 = new QTableWidgetItem(QString::number(entity.field_0xf));
    ui->entityCDTable->setItem(0, 15, item15);
    QTableWidgetItem *item16 = new QTableWidgetItem(QString::number(entity.field_0x10));
    ui->entityCDTable->setItem(0, 16, item16);
    QTableWidgetItem *item17 = new QTableWidgetItem(QString::number(entity.field_0x11));
    ui->entityCDTable->setItem(0, 17, item17);
    QTableWidgetItem *item18 = new QTableWidgetItem(QString::number(entity.field_0x12));
    ui->entityCDTable->setItem(0, 18, item18);
    QTableWidgetItem *item19 = new QTableWidgetItem(QString::number(entity.field_0x13));
    ui->entityCDTable->setItem(0, 19, item19);
    QTableWidgetItem *item20 = new QTableWidgetItem(QString::number(entity.field_0x14));
    ui->entityCDTable->setItem(0, 20, item20);
    QTableWidgetItem *item21 = new QTableWidgetItem(QString::number(entity.field_0x15));
    ui->entityCDTable->setItem(0, 21, item21);
    QTableWidgetItem *item22 = new QTableWidgetItem(QString::number(entity.field_0x16));
    ui->entityCDTable->setItem(0, 22, item22);
    QTableWidgetItem *item23 = new QTableWidgetItem(QString::number(entity.field_0x17));
    ui->entityCDTable->setItem(0, 23, item23);
    QTableWidgetItem *item24 = new QTableWidgetItem(QString::number(entity.field_0x18));
    ui->entityCDTable->setItem(0, 24, item24);
    QTableWidgetItem *item25 = new QTableWidgetItem(QString::number(entity.field_0x19));
    ui->entityCDTable->setItem(0, 25, item25);
    QTableWidgetItem *item26 = new QTableWidgetItem(QString::number(entity.HP));
    ui->entityCDTable->setItem(0, 26, item26);
    QTableWidgetItem *item27 = new QTableWidgetItem(QString::number(entity.field_0x1c));
    ui->entityCDTable->setItem(0, 27, item27);
    QTableWidgetItem *item28 = new QTableWidgetItem(QString::number(entity.field_0x1d));
    ui->entityCDTable->setItem(0, 28, item28);
    QTableWidgetItem *item29 = new QTableWidgetItem(QString::number(entity.ExperienceGain));
    ui->entityCDTable->setItem(0, 29, item29);
    QTableWidgetItem *item30 = new QTableWidgetItem(QString::number(entity.DefSlash));
    ui->entityCDTable->setItem(0, 30, item30);
    QTableWidgetItem *item31 = new QTableWidgetItem(QString::number(entity.DefChop));
    ui->entityCDTable->setItem(0, 31, item31);
    QTableWidgetItem *item32 = new QTableWidgetItem(QString::number(entity.DefStab));
    ui->entityCDTable->setItem(0, 32, item32);
    QTableWidgetItem *item33 = new QTableWidgetItem(QString::number(entity.DefHolyMagic));
    ui->entityCDTable->setItem(0, 33, item33);
    QTableWidgetItem *item34 = new QTableWidgetItem(QString::number(entity.DefFireMagic));
    ui->entityCDTable->setItem(0, 34, item34);
    QTableWidgetItem *item35 = new QTableWidgetItem(QString::number(entity.DefEarthMagic));
    ui->entityCDTable->setItem(0, 35, item35);
    QTableWidgetItem *item36 = new QTableWidgetItem(QString::number(entity.DefWindMagic));
    ui->entityCDTable->setItem(0, 36, item36);
    QTableWidgetItem *item37 = new QTableWidgetItem(QString::number(entity.DefWaterMagic));
    ui->entityCDTable->setItem(0, 37, item37);
    QTableWidgetItem *item38 = new QTableWidgetItem(QString::number(entity.field_0x30));
    ui->entityCDTable->setItem(0, 38, item38);
    QTableWidgetItem *item39 = new QTableWidgetItem(QString::number(entity.field_0x31));
    ui->entityCDTable->setItem(0, 39, item39);
    QTableWidgetItem *item40 = new QTableWidgetItem(QString::number(entity.Scale));
    ui->entityCDTable->setItem(0, 40, item40);
    QTableWidgetItem *item41 = new QTableWidgetItem(QString::number(entity.field_0x34));
    ui->entityCDTable->setItem(0, 41, item41);
    QTableWidgetItem *item42 = new QTableWidgetItem(QString::number(entity.field_0x35));
    ui->entityCDTable->setItem(0, 42, item42);
    QTableWidgetItem *item43 = new QTableWidgetItem(QString::number(entity.field_0x36));
    ui->entityCDTable->setItem(0, 43, item43);
    QTableWidgetItem *item44 = new QTableWidgetItem(QString::number(entity.field_0x37));
    ui->entityCDTable->setItem(0, 44, item44);
    QTableWidgetItem *item45 = new QTableWidgetItem(QString::number(entity.SomePointers[0]));
    ui->entityCDTable->setItem(0, 45, item45);
    QTableWidgetItem *item46 = new QTableWidgetItem(QString::number(entity.SomePointers[1]));
    ui->entityCDTable->setItem(0, 46, item46);
    QTableWidgetItem *item47 = new QTableWidgetItem(QString::number(entity.SomePointers[2]));
    ui->entityCDTable->setItem(0, 47, item47);
    QTableWidgetItem *item48 = new QTableWidgetItem(QString::number(entity.SomePointers[3]));
    ui->entityCDTable->setItem(0, 48, item48);
    QTableWidgetItem *item49 = new QTableWidgetItem(QString::number(entity.SomePointers[4]));
    ui->entityCDTable->setItem(0, 49, item49);
    QTableWidgetItem *item50 = new QTableWidgetItem(QString::number(entity.SomePointers[5]));
    ui->entityCDTable->setItem(0, 50, item50);
    QTableWidgetItem *item51 = new QTableWidgetItem(QString::number(entity.SomePointers[6]));
    ui->entityCDTable->setItem(0, 51, item51);
    QTableWidgetItem *item52 = new QTableWidgetItem(QString::number(entity.SomePointers[7]));
    ui->entityCDTable->setItem(0, 52, item52);
    QTableWidgetItem *item53 = new QTableWidgetItem(QString::number(entity.SomePointers[8]));
    ui->entityCDTable->setItem(0, 53, item53);
    QTableWidgetItem *item54 = new QTableWidgetItem(QString::number(entity.SomePointers[9]));
    ui->entityCDTable->setItem(0, 54, item54);
    QTableWidgetItem *item55 = new QTableWidgetItem(QString::number(entity.SomePointers[10]));
    ui->entityCDTable->setItem(0, 55, item55);
    QTableWidgetItem *item56 = new QTableWidgetItem(QString::number(entity.SomePointers[11]));
    ui->entityCDTable->setItem(0, 56, item56);
    QTableWidgetItem *item57 = new QTableWidgetItem(QString::number(entity.SomePointers[12]));
    ui->entityCDTable->setItem(0, 57, item57);
    QTableWidgetItem *item58 = new QTableWidgetItem(QString::number(entity.SomePointers[13]));
    ui->entityCDTable->setItem(0, 58, item58);
    QTableWidgetItem *item59 = new QTableWidgetItem(QString::number(entity.SomePointers[14]));
    ui->entityCDTable->setItem(0, 59, item59);
    QTableWidgetItem *item60 = new QTableWidgetItem(QString::number(entity.SomePointers[15]));
    ui->entityCDTable->setItem(0, 60, item60);

}

void MapEditWidget::entityInstanceHovered(byte instanceIndex)
{
    auto instance = curMap->getEntityInstances()[instanceIndex];
    currentEntityInstance = instanceIndex;

    QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(instance.field_0x0));
    ui->entityInstanceTable->setItem(0, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(instance.EntityClass));
    ui->entityInstanceTable->setItem(0, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(instance.field_0x2));
    ui->entityInstanceTable->setItem(0, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(instance.WEXTilePos));
    ui->entityInstanceTable->setItem(0, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(instance.NSYTilePos));
    ui->entityInstanceTable->setItem(0, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(instance.field_0x5));
    ui->entityInstanceTable->setItem(0, 5, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(KingsField::getItemIDAsByte(instance.DroppedItem)));
    ui->entityInstanceTable->setItem(0, 6, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(instance.Layer));
    ui->entityInstanceTable->setItem(0, 7, item7);
    QTableWidgetItem *item8 = new QTableWidgetItem(QString::number(instance.field_0x8));
    ui->entityInstanceTable->setItem(0, 8, item8);
    QTableWidgetItem *item9 = new QTableWidgetItem(QString::number(instance.field_0x9));
    ui->entityInstanceTable->setItem(0, 9, item9);
    QTableWidgetItem *item10 = new QTableWidgetItem(QString::number(instance.field_0xa));
    ui->entityInstanceTable->setItem(0, 10, item10);
    QTableWidgetItem *item11 = new QTableWidgetItem(QString::number(instance.field_0xb));
    ui->entityInstanceTable->setItem(0, 11, item11);
    QTableWidgetItem *item12 = new QTableWidgetItem(QString::number(instance.field_0xc));
    ui->entityInstanceTable->setItem(0, 12, item12);
    QTableWidgetItem *item13 = new QTableWidgetItem(QString::number(instance.field_0xd));
    ui->entityInstanceTable->setItem(0, 13, item13);
    QTableWidgetItem *item14 = new QTableWidgetItem(QString::number(instance.field_0xe));
    ui->entityInstanceTable->setItem(0, 14, item14);
    QTableWidgetItem *item15 = new QTableWidgetItem(QString::number(instance.field_0xf));
    ui->entityInstanceTable->setItem(0, 15, item15);

    ui->entityCDCombo->setCurrentIndex(instance.EntityClass);
}

void MapEditWidget::hoveredTileInfo(byte elevation, byte rotation, byte collisionThing, byte zoneDelimiter)
{
    ui->elevLabel->setText("Elevation: " + QString::number(elevation));
    ui->rotLabel->setText("Rotation: " + QString::number(rotation));
    ui->colThingLabel->setText("Collision Thing: " + QString::number(collisionThing));
    ui->zoneDelimLabel->setText("Zone Delimiter: " + QString::number(zoneDelimiter));
}

void MapEditWidget::objectInstanceHovered(size_t instanceIndex)
{
    auto instance = curMap->getObjectInstanceDeclarations()[instanceIndex];
    currentObjectInstance = instanceIndex;

    QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(instance.TileLayer));
    ui->objectInstanceTable->setItem(0, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(instance.WEXTilePos));
    ui->objectInstanceTable->setItem(0, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(instance.NSYTilePos));
    ui->objectInstanceTable->setItem(0, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(instance.field_0x3));
    ui->objectInstanceTable->setItem(0, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(KingsField::getItemIDAsByte(instance.ItemID)));
    ui->objectInstanceTable->setItem(0, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(instance.field_0x5));
    ui->objectInstanceTable->setItem(0, 5, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(instance.field_0x6));
    ui->objectInstanceTable->setItem(0, 6, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(instance.field_0x7));
    ui->objectInstanceTable->setItem(0, 7, item7);
    QTableWidgetItem *item8 = new QTableWidgetItem(QString::number(instance.field_0x8));
    ui->objectInstanceTable->setItem(0, 8, item8);
    QTableWidgetItem *item9 = new QTableWidgetItem(QString::number(instance.field_0x9));
    ui->objectInstanceTable->setItem(0, 9, item9);
    QTableWidgetItem *item10 = new QTableWidgetItem(QString::number(instance.field_0xa));
    ui->objectInstanceTable->setItem(0, 10, item10);
    QTableWidgetItem *item11 = new QTableWidgetItem(QString::number(instance.field_0xb));
    ui->objectInstanceTable->setItem(0, 11, item11);
    QTableWidgetItem *item12 = new QTableWidgetItem(QString::number(instance.field_0xc));
    ui->objectInstanceTable->setItem(0, 12, item12);
    QTableWidgetItem *item13 = new QTableWidgetItem(QString::number(instance.field_0xd));
    ui->objectInstanceTable->setItem(0, 13, item13);
    QTableWidgetItem *item14 = new QTableWidgetItem(QString::number(instance.field_0xe));
    ui->objectInstanceTable->setItem(0, 14, item14);
    QTableWidgetItem *item15 = new QTableWidgetItem(QString::number(instance.field_0xf));
    ui->objectInstanceTable->setItem(0, 15, item15);
    QTableWidgetItem *item16 = new QTableWidgetItem(QString::number(KingsField::getItemIDAsByte(instance.KeyID)));
    ui->objectInstanceTable->setItem(0, 16, item16);
    QTableWidgetItem *item17 = new QTableWidgetItem(QString::number(instance.field_0x11));
    ui->objectInstanceTable->setItem(0, 17, item17);
    QTableWidgetItem *item18 = new QTableWidgetItem(QString::number(instance.InstanceContained));
    ui->objectInstanceTable->setItem(0, 18, item18);
    QTableWidgetItem *item19 = new QTableWidgetItem(QString::number(instance.field_0x13));
    ui->objectInstanceTable->setItem(0, 19, item19);
    QTableWidgetItem *item20 = new QTableWidgetItem(QString::number(instance.field_0x14));
    ui->objectInstanceTable->setItem(0, 20, item20);
    QTableWidgetItem *item21 = new QTableWidgetItem(QString::number(instance.field_0x15));
    ui->objectInstanceTable->setItem(0, 21, item21);
    QTableWidgetItem *item22 = new QTableWidgetItem(QString::number(instance.field_0x16));
    ui->objectInstanceTable->setItem(0, 22, item22);
}

void MapEditWidget::on_zoneDelimCheck_stateChanged(int arg1)
{
    ui->mapViewWidget->setDrawZoneDelimiters((arg1 == Qt::Checked));
}

void MapEditWidget::on_entityInstanceTable_itemChanged(QTableWidgetItem *item)
{
    KingsField::EntityInstance &instance = curMap->getInstance(currentEntityInstance);
    switch(item->row())
    {
        case (0): instance.field_0x0 = item->text().toUShort(); break;
        case (1): instance.EntityClass = item->text().toUShort(); break;
        case (2): instance.field_0x2 = item->text().toUShort(); break;
        case (3): instance.WEXTilePos = item->text().toUShort(); break;
        case (4): instance.NSYTilePos = item->text().toUShort(); break;
        case (5): instance.field_0x5 = item->text().toUShort(); break;
        case (6): instance.DroppedItem = KingsField::getItemIDFromByte(item->text().toUShort()); break;
        case (7): instance.Layer = item->text().toUShort(); break;
        case (8): instance.field_0x8 = item->text().toUShort(); break;
        case (9): instance.field_0x9 = item->text().toUShort(); break;
        case (10): instance.field_0xa = item->text().toUShort(); break;
        case (11): instance.field_0xb = item->text().toUShort(); break;
        case (12): instance.field_0xc = item->text().toUShort(); break;
        case (13): instance.field_0xd = item->text().toUShort(); break;
        case (14): instance.field_0xe = item->text().toUShort(); break;
        case (15): instance.field_0xf = item->text().toUShort();
    }
    curMap->setChanged();
}

void MapEditWidget::on_entityCDTable_itemChanged(QTableWidgetItem *item)
{
    KingsField::EntityClassDeclaration &classDecl = curMap->getClassDeclaration(ui->entityCDCombo->currentIndex());
    switch(item->row())
    {
        case (0): classDecl.MeshID = KingsField::getEntityMeshIDFromByte(item->text().toUShort()); break;
        case (1): classDecl.FourOrForty = item->text().toUShort(); break;
        case (2): classDecl.field_0x2 = item->text().toUShort(); break;
        case (3): classDecl.field_0x3 = item->text().toUShort(); break;
        case (4): classDecl.field_0x4 = item->text().toUShort(); break;
        case (5): classDecl.field_0x5 = item->text().toUShort(); break;
        case (6): classDecl.field_0x6 = item->text().toUShort(); break;
        case (7): classDecl.field_0x7 = item->text().toUShort(); break;
        case (8): classDecl.field_0x8 = item->text().toUShort(); break;
        case (9): classDecl.field_0x9 = item->text().toUShort(); break;
        case (10): classDecl.field_0xa = item->text().toUShort(); break;
        case (11): classDecl.field_0xb = item->text().toUShort(); break;
        case (12): classDecl.field_0xc = item->text().toUShort(); break;
        case (13): classDecl.field_0xd = item->text().toUShort(); break;
        case (14): classDecl.field_0xe = item->text().toUShort(); break;
        case (15): classDecl.field_0xf = item->text().toUShort(); break;
        case (16): classDecl.field_0x10 = item->text().toUShort(); break;
        case (17): classDecl.field_0x11 = item->text().toUShort(); break;
        case (18): classDecl.field_0x12 = item->text().toUShort(); break;
        case (19): classDecl.field_0x13 = item->text().toUShort(); break;
        case (20): classDecl.field_0x14 = item->text().toUShort(); break;
        case (21): classDecl.field_0x15 = item->text().toUShort(); break;
        case (22): classDecl.field_0x16 = item->text().toUShort(); break;
        case (23): classDecl.field_0x17 = item->text().toUShort(); break;
        case (24): classDecl.field_0x18 = item->text().toUShort(); break;
        case (25): classDecl.field_0x19 = item->text().toUShort(); break;
        case (26): classDecl.HP = item->text().toUShort(); break;
        case (27): classDecl.field_0x1c = item->text().toUShort(); break;
        case (28): classDecl.field_0x1d = item->text().toUShort(); break;
        case (29): classDecl.ExperienceGain = item->text().toUShort(); break;
        case (30): classDecl.DefSlash = item->text().toUShort(); break;
        case (31): classDecl.DefChop = item->text().toUShort(); break;
        case (32): classDecl.DefStab = item->text().toUShort(); break;
        case (33): classDecl.DefHolyMagic = item->text().toUShort(); break;
        case (34): classDecl.DefFireMagic = item->text().toUShort(); break;
        case (35): classDecl.DefEarthMagic = item->text().toUShort(); break;
        case (36): classDecl.DefWindMagic = item->text().toUShort(); break;
        case (37): classDecl.DefWaterMagic = item->text().toUShort(); break;
        case (38): classDecl.field_0x30 = item->text().toUShort(); break;
        case (39): classDecl.field_0x31 = item->text().toUShort(); break;
        case (40): classDecl.Scale = item->text().toShort(); break;
        case (41): classDecl.field_0x34 = item->text().toUShort(); break;
        case (42): classDecl.field_0x35 = item->text().toUShort(); break;
        case (43): classDecl.field_0x36 = item->text().toUShort(); break;
        case (44): classDecl.field_0x37 = item->text().toUShort(); break;
        case (45): classDecl.SomePointers[0] = item->text().toUInt(); break;
        case (46): classDecl.SomePointers[1] = item->text().toUInt(); break;
        case (47): classDecl.SomePointers[2] = item->text().toUInt(); break;
        case (48): classDecl.SomePointers[3] = item->text().toUInt(); break;
        case (49): classDecl.SomePointers[4] = item->text().toUInt(); break;
        case (50): classDecl.SomePointers[5] = item->text().toUInt(); break;
        case (51): classDecl.SomePointers[6] = item->text().toUInt(); break;
        case (52): classDecl.SomePointers[7] = item->text().toUInt(); break;
        case (53): classDecl.SomePointers[8] = item->text().toUInt(); break;
        case (54): classDecl.SomePointers[9] = item->text().toUInt(); break;
        case (55): classDecl.SomePointers[10] = item->text().toUInt(); break;
        case (56): classDecl.SomePointers[11] = item->text().toUInt(); break;
        case (57): classDecl.SomePointers[12] = item->text().toUInt(); break;
        case (58): classDecl.SomePointers[13] = item->text().toUInt(); break;
        case (59): classDecl.SomePointers[14] = item->text().toUInt(); break;
        case (60): classDecl.SomePointers[15] = item->text().toUInt(); break;
    }
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
        case (4): instance.ItemID = KingsField::getItemIDFromByte(item->text().toUShort()); break;
        case (5): instance.field_0x5 = item->text().toUShort(); break;
        case (6): instance.field_0x6 = item->text().toUShort(); break;
        case (7): instance.field_0x7 = item->text().toUShort(); break;
        case (8): instance.field_0x8 = item->text().toUShort(); break;
        case (9): instance.field_0x9 = item->text().toUShort(); break;
        case (10): instance.field_0xa = item->text().toUShort(); break;
        case (11): instance.field_0xb = item->text().toUShort(); break;
        case (12): instance.field_0xc = item->text().toUShort(); break;
        case (13): instance.field_0xd = item->text().toUShort(); break;
        case (14): instance.field_0xe = item->text().toUShort(); break;
        case (15): instance.field_0xf = item->text().toUShort(); break;
        case (16): instance.KeyID = KingsField::getItemIDFromByte(item->text().toUShort()); break;
        case (17): instance.field_0x11 = item->text().toUShort(); break;
        case (18): instance.InstanceContained = item->text().toUShort(); break;
        case (19): instance.field_0x13 = item->text().toUShort(); break;
        case (20): instance.field_0x14 = item->text().toUShort(); break;
        case (21): instance.field_0x15 = item->text().toUShort(); break;
        case (22): instance.field_0x16 = item->text().toUShort(); break;
        case (23): instance.field_0x17 = item->text().toUShort();
    }
    curMap->setChanged();
}

void MapEditWidget::on_elementCombo_currentIndexChanged(int index)
{
    auto elem = static_cast<MapViewer::MapElement>(index);
    ui->mapViewWidget->setElement(elem);
}

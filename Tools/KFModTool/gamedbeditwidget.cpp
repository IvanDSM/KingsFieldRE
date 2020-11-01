#include "gamedbeditwidget.h"

GameDBEditWidget::GameDBEditWidget(QWidget *parent, std::shared_ptr<GameDB> gameDB_) :
    QWidget(parent),
    gameDB(gameDB_),
    ui(new Ui::GameDBEditWidget)
{
    ui->setupUi(this);

    ui->armorTable->setModel(new ArmorStatsTableModel(ui->armorTable, gameDB->getArmorStats(0)));
    ui->magicTable->setModel(new MagicTableModel(ui->magicTable, gameDB->getMagic(0)));
    ui->objClassTable->setModel(new ObjectClassTableModel(ui->objClassTable, gameDB->getObjClass(0)));
    ui->levelTable->setModel(new PlayerLevelDataTableModel(ui->levelTable, gameDB->getLevel(0)));
    ui->weaponTable->setModel(new WeaponStatsTableModel(ui->weaponTable, gameDB->getWeaponStats(0)));

    fillArmorStatsCombo();
    fillMagicCombo();
    fillObjClassCombo();
    fillWeaponStatsCombo();
}

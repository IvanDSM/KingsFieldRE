#include "gamedbeditwidget.h"
#include "datahandlers/gamedb.h"
#include "models/armorstatslistmodel.h"
#include "models/armorstatstablemodel.h"
#include "models/magiclistmodel.h"
#include "models/magictablemodel.h"
#include "models/objectclasslistmodel.h"
#include "models/objectclasstablemodel.h"
#include "models/playerleveldatatablemodel.h"
#include "models/weaponstatslistmodel.h"
#include "models/weaponstatstablemodel.h"
#include <utility>

GameDBEditWidget::GameDBEditWidget(KFMTFile& file_, QWidget* parent)
    : KFMTEditor(file_, parent), ui(new Ui::GameDBEditWidget)
{
    handler = std::make_unique<GameDB>(file_);
    auto& gameDB = *reinterpret_cast<GameDB*>(handler.get());
    ui->setupUi(this);

    // Table models setup
    ui->armorTable->setModel(new ArmorStatsTableModel(gameDB, ui->armorTable));
    ui->magicTable->setModel(new MagicTableModel(gameDB, ui->magicTable));
    ui->objClassTable->setModel(new ObjectClassTableModel(gameDB, ui->objClassTable));
    ui->levelTable->setModel(new PlayerLevelDataTableModel(gameDB, ui->levelTable));
    ui->weaponTable->setModel(new WeaponStatsTableModel(gameDB, ui->weaponTable));

    // List models setup
    ui->armorCombo->setModel(new ArmorStatsListModel(gameDB, ui->armorCombo));
    ui->magicCombo->setModel(new MagicListModel(gameDB, ui->magicCombo));
    ui->objClassCombo->setModel(new ObjectClassListModel(gameDB, ui->objClassCombo));
    ui->weaponCombo->setModel(new WeaponStatsListModel(gameDB, ui->weaponCombo));
}

void GameDBEditWidget::on_armorCombo_currentIndexChanged(int index)
{
    reinterpret_cast<ArmorStatsTableModel*>(ui->armorTable->model())->setCurArmor(index);
}

void GameDBEditWidget::on_magicCombo_currentIndexChanged(int index)
{
    reinterpret_cast<MagicTableModel*>(ui->magicTable->model())->setCurMagic(index);
}

void GameDBEditWidget::on_objClassCombo_currentIndexChanged(int index)
{
    reinterpret_cast<ObjectClassTableModel*>(ui->objClassTable->model())->setCurObjectClass(index);
}

void GameDBEditWidget::on_levelSpin_valueChanged(int arg1)
{
    reinterpret_cast<PlayerLevelDataTableModel*>(ui->levelTable->model())->setCurLevel(arg1 - 1);
}

void GameDBEditWidget::on_weaponCombo_currentIndexChanged(int index)
{
    reinterpret_cast<WeaponStatsTableModel*>(ui->weaponTable->model())->setCurWeapon(index);
}

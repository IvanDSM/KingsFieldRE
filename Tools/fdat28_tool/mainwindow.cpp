#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QRandomGenerator>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto randomizer = QRandomGenerator::securelySeeded();
    setWindowTitle("FDAT28 Tool - " + sillyTitles.at(randomizer.generate() % sillyTitles.size()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionLoad_FDAT_28_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load FDAT 28", QDir::currentPath());
    if (fileName != "")
    {
        fdat28.loadFile(fileName);

        auto level = fdat28.getLvlData(static_cast<size_t>(ui->spinLevel->value() - 1));
        displayLevelData(level);

        auto magic = fdat28.getMagicData(static_cast<size_t>(ui->comboMagic->currentIndex()));
        displayMagicData(magic);

        auto godOnlyKnows = fdat28.getGodOnlyKnows(static_cast<size_t>(ui->spinGOKIndex->value()));
        displayGOKData(godOnlyKnows);

        auto weaponStats = fdat28.getWeaponStats(static_cast<size_t>(ui->comboWeapon->currentIndex()));
        displayWeaponStats(weaponStats);
    }

}

void MainWindow::on_actionShow_Hide_Unknown_toggled(bool arg1)
{
    ui->groupUnk2->setVisible(!arg1);
    ui->groupUnk3->setVisible(!arg1);
    ui->groupUnk4->setVisible(!arg1);
    ui->groupUnk5->setVisible(!arg1);
    ui->groupUnk6->setVisible(!arg1);
}

void MainWindow::displayGOKData(const KingsField80175914OddStruct &gokData)
{
    ui->tableGOKData->setItem(0, 0, new QTableWidgetItem(QString::number(gokData.field_0x0)));
    ui->tableGOKData->setItem(1, 0, new QTableWidgetItem(QString::number(gokData.SomeType)));
    ui->tableGOKData->setItem(2, 0, new QTableWidgetItem(QString::number(gokData.field_0x2)));
    ui->tableGOKData->setItem(3, 0, new QTableWidgetItem(QString::number(gokData.field_0x3)));
    ui->tableGOKData->setItem(4, 0, new QTableWidgetItem(QString::number(gokData.field_0x4)));
    ui->tableGOKData->setItem(5, 0, new QTableWidgetItem(QString::number(gokData.field_0x5)));
    ui->tableGOKData->setItem(6, 0, new QTableWidgetItem(QString::number(gokData.field_0x6)));
    ui->tableGOKData->setItem(7, 0, new QTableWidgetItem(QString::number(gokData.field_0x7)));
    ui->tableGOKData->setItem(8, 0, new QTableWidgetItem(QString::number(gokData.field_0x8)));
    ui->tableGOKData->setItem(9, 0, new QTableWidgetItem(QString::number(gokData.field_0x9)));
    ui->tableGOKData->setItem(10, 0, new QTableWidgetItem(QString::number(gokData.field_0xa)));
    ui->tableGOKData->setItem(11, 0, new QTableWidgetItem(QString::number(gokData.field_0xb)));
    ui->tableGOKData->setItem(12, 0, new QTableWidgetItem(QString::number(gokData.field_0xc)));
    ui->tableGOKData->setItem(13, 0, new QTableWidgetItem(QString::number(gokData.field_0xd)));
    ui->tableGOKData->setItem(14, 0, new QTableWidgetItem(QString::number(gokData.field_0xe)));
    ui->tableGOKData->setItem(15, 0, new QTableWidgetItem(QString::number(gokData.field_0xf)));
    ui->tableGOKData->setItem(16, 0, new QTableWidgetItem(QString::number(gokData.field_0x10)));
    ui->tableGOKData->setItem(17, 0, new QTableWidgetItem(QString::number(gokData.field_0x11)));
    ui->tableGOKData->setItem(18, 0, new QTableWidgetItem(QString::number(gokData.field_0x12)));
    ui->tableGOKData->setItem(19, 0, new QTableWidgetItem(QString::number(gokData.field_0x13)));
    ui->tableGOKData->setItem(20, 0, new QTableWidgetItem(QString::number(gokData.field_0x14)));
    ui->tableGOKData->setItem(21, 0, new QTableWidgetItem(QString::number(gokData.field_0x15)));
    ui->tableGOKData->setItem(22, 0, new QTableWidgetItem(QString::number(gokData.field_0x16)));
    ui->tableGOKData->setItem(23, 0, new QTableWidgetItem(QString::number(gokData.field_0x17)));
}

void MainWindow::displayLevelData(const KingsFieldPlayerLvlData &levelData)
{
    ui->tableLvlData->setItem(0, 0, new QTableWidgetItem(QString::number(levelData.BaseHP)));
    ui->tableLvlData->setItem(1, 0, new QTableWidgetItem(QString::number(levelData.BaseMP)));
    ui->tableLvlData->setItem(2, 0, new QTableWidgetItem(QString::number(levelData.StrPowerPlus)));
    ui->tableLvlData->setItem(3, 0, new QTableWidgetItem(QString::number(levelData.MagPowerPlus)));
    ui->tableLvlData->setItem(4, 0, new QTableWidgetItem(QString::number(levelData.ExpForNextLevel)));
}

void MainWindow::displayMagicData(const KingsFieldMagicStructure &magicData)
{
    ui->tableMagicData->setItem(0, 0, new QTableWidgetItem(QString::number(magicData.PlayerHas)));
    ui->tableMagicData->setItem(1, 0, new QTableWidgetItem(QString::number(magicData.ChargeRecoveryTime)));
    ui->tableMagicData->setItem(2, 0, new QTableWidgetItem(QString::number(magicData.field_0x2)));
    ui->tableMagicData->setItem(3, 0, new QTableWidgetItem(QString::number(magicData.field_0x3)));
    ui->tableMagicData->setItem(4, 0, new QTableWidgetItem(QString::number(magicData.field_0x4)));
    ui->tableMagicData->setItem(5, 0, new QTableWidgetItem(QString::number(magicData.field_0x5)));
    ui->tableMagicData->setItem(6, 0, new QTableWidgetItem(QString::number(magicData.field_0x6)));
    ui->tableMagicData->setItem(7, 0, new QTableWidgetItem(QString::number(magicData.field_0x7)));
    ui->tableMagicData->setItem(8, 0, new QTableWidgetItem(QString::number(magicData.SomeDmg1)));
    ui->tableMagicData->setItem(9, 0, new QTableWidgetItem(QString::number(magicData.SomeDmg2)));
    ui->tableMagicData->setItem(10, 0, new QTableWidgetItem(QString::number(magicData.SomeDmg3)));
    ui->tableMagicData->setItem(11, 0, new QTableWidgetItem(QString::number(magicData.FireDmg)));
    ui->tableMagicData->setItem(12, 0, new QTableWidgetItem(QString::number(magicData.EarthDmg)));
    ui->tableMagicData->setItem(13, 0, new QTableWidgetItem(QString::number(magicData.WindDmg)));
    ui->tableMagicData->setItem(14, 0, new QTableWidgetItem(QString::number(magicData.WaterDmg)));
    ui->tableMagicData->setItem(15, 0, new QTableWidgetItem(QString::number(magicData.MPCost)));
    ui->tableMagicData->setItem(16, 0, new QTableWidgetItem(QString::number(magicData.field_0x18)));
    ui->tableMagicData->setItem(17, 0, new QTableWidgetItem(QString::number(magicData.field_0x19)));

}

void MainWindow::displayWeaponStats(const KingsFieldWeaponStats &weaponStats)
{
    ui->tableWeaponStats->setItem(0, 0, new QTableWidgetItem(QString::number(weaponStats.OffSlash)));
    ui->tableWeaponStats->setItem(1, 0, new QTableWidgetItem(QString::number(weaponStats.OffChop)));
    ui->tableWeaponStats->setItem(2, 0, new QTableWidgetItem(QString::number(weaponStats.OffStab)));
    ui->tableWeaponStats->setItem(3, 0, new QTableWidgetItem(QString::number(weaponStats.OffHolyM)));
    ui->tableWeaponStats->setItem(4, 0, new QTableWidgetItem(QString::number(weaponStats.OffFireM)));
    ui->tableWeaponStats->setItem(5, 0, new QTableWidgetItem(QString::number(weaponStats.OffEarthM)));
    ui->tableWeaponStats->setItem(6, 0, new QTableWidgetItem(QString::number(weaponStats.OffWindM)));
    ui->tableWeaponStats->setItem(7, 0, new QTableWidgetItem(QString::number(weaponStats.OffWaterM)));
    ui->tableWeaponStats->setItem(8, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x10)));
    ui->tableWeaponStats->setItem(9, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x11)));
    ui->tableWeaponStats->setItem(10, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x12)));
    ui->tableWeaponStats->setItem(11, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x13)));
    ui->tableWeaponStats->setItem(12, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x14)));
    ui->tableWeaponStats->setItem(13, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x15)));
    ui->tableWeaponStats->setItem(14, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x16)));
    ui->tableWeaponStats->setItem(15, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x17)));
    ui->tableWeaponStats->setItem(16, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x18)));
    ui->tableWeaponStats->setItem(17, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x19)));
    ui->tableWeaponStats->setItem(18, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1a)));
    ui->tableWeaponStats->setItem(19, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1b)));
    ui->tableWeaponStats->setItem(20, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1c)));
    ui->tableWeaponStats->setItem(21, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1d)));
    ui->tableWeaponStats->setItem(22, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1e)));
    ui->tableWeaponStats->setItem(23, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x1f)));
    ui->tableWeaponStats->setItem(24, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x20)));
    ui->tableWeaponStats->setItem(25, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x21)));
    ui->tableWeaponStats->setItem(26, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x22)));
    ui->tableWeaponStats->setItem(27, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x23)));
    ui->tableWeaponStats->setItem(28, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x24)));
    ui->tableWeaponStats->setItem(29, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x25)));
    ui->tableWeaponStats->setItem(30, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x26)));
    ui->tableWeaponStats->setItem(31, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x27)));
    ui->tableWeaponStats->setItem(32, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x28)));
    ui->tableWeaponStats->setItem(33, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x29)));
    ui->tableWeaponStats->setItem(34, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2a)));
    ui->tableWeaponStats->setItem(35, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2b)));
    ui->tableWeaponStats->setItem(36, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2c)));
    ui->tableWeaponStats->setItem(37, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2d)));
    ui->tableWeaponStats->setItem(38, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2e)));
    ui->tableWeaponStats->setItem(39, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x2f)));
    ui->tableWeaponStats->setItem(40, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x30)));
    ui->tableWeaponStats->setItem(41, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x31)));
    ui->tableWeaponStats->setItem(42, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x32)));
    ui->tableWeaponStats->setItem(43, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x33)));
    ui->tableWeaponStats->setItem(44, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x34)));
    ui->tableWeaponStats->setItem(45, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x35)));
    ui->tableWeaponStats->setItem(46, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x36)));
    ui->tableWeaponStats->setItem(47, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x37)));
    ui->tableWeaponStats->setItem(48, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x38)));
    ui->tableWeaponStats->setItem(49, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x39)));
    ui->tableWeaponStats->setItem(50, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3a)));
    ui->tableWeaponStats->setItem(51, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3b)));
    ui->tableWeaponStats->setItem(52, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3c)));
    ui->tableWeaponStats->setItem(53, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3d)));
    ui->tableWeaponStats->setItem(54, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3e)));
    ui->tableWeaponStats->setItem(55, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x3f)));
    ui->tableWeaponStats->setItem(56, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x40)));
    ui->tableWeaponStats->setItem(57, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x41)));
    ui->tableWeaponStats->setItem(58, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x42)));
    ui->tableWeaponStats->setItem(59, 0, new QTableWidgetItem(QString::number(weaponStats.field_0x43)));
}

void MainWindow::on_spinLevel_valueChanged(int arg1)
{
    if (fdat28.isLoaded())
    {
        auto level = fdat28.getLvlData(static_cast<size_t>(arg1 - 1));
        displayLevelData(level);
    }
}

void MainWindow::on_comboMagic_currentIndexChanged(int index)
{
    if(fdat28.isLoaded())
    {
        auto magic = fdat28.getMagicData(static_cast<size_t>(index));
        displayMagicData(magic);
    }
}

void MainWindow::on_spinGOKIndex_valueChanged(int arg1)
{
    if(fdat28.isLoaded())
    {
        auto godOnlyKnows = fdat28.getGodOnlyKnows(static_cast<size_t>(arg1));
        displayGOKData(godOnlyKnows);
    }
}

void MainWindow::on_comboWeapon_currentIndexChanged(int index)
{
    if(fdat28.isLoaded())
    {
        auto weaponStats = fdat28.getWeaponStats(static_cast<size_t>(index));
        displayWeaponStats(weaponStats);
    }
}

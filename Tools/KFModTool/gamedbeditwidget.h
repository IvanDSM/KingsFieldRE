#ifndef GAMEDBEDITWIDGET_H
#define GAMEDBEDITWIDGET_H

#include <QWidget>
#include "ui_gamedbeditwidget.h"
#include "gamedb.h"
#include "models/playerleveldatatablemodel.h"
#include "models/magictablemodel.h"
#include "models/objectclasstablemodel.h"
#include "models/weaponstatstablemodel.h"

class GameDBEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameDBEditWidget(QWidget *parent = nullptr, std::shared_ptr<GameDB> gameDB_ = nullptr);

private slots:
    void on_magicCombo_currentIndexChanged(int index)
    {
        ui->magicTable->setModel(new MagicTableModel(ui->magicTable,
                                                     gameDB->getMagic(static_cast<byte>(index))));
    }

    void on_objClassCombo_currentIndexChanged(int index)
    {
        ui->objClassTable->setModel(new ObjectClassTableModel(ui->objClassTable,
                                                              gameDB->getObjClass(static_cast<unsigned short>(index))));
    }

    void on_levelSpin_valueChanged(int arg1)
    {
        ui->levelTable->setModel(new PlayerLevelDataTableModel(ui->levelTable,
                                                               gameDB->getLevel(static_cast<byte>(arg1 - 1))));
    }

    void on_weaponCombo_currentIndexChanged(int index)
    {
        ui->weaponTable->setModel(new WeaponStatsTableModel(ui->weaponTable,
                                                            gameDB->getWeaponStats(static_cast<byte>(index))));
    }

private:
    void fillMagicCombo()
    {
        for (byte i = 0; i < GameDB::magicDataSize; i++)
        {
            ui->magicCombo->addItem(QString::number(i) + " (0x" + QString::number(i) + ") " +
                                    KingsField::getMagicIDName(KingsField::getMagicIDFromByte(i)));
        }
    }

    void fillObjClassCombo()
    {
        for (unsigned short i = 0; i < GameDB::objClassDeclarationsSize; i++)
            ui->objClassCombo->addItem(QString::number(i) + " (0x" + QString::number(i) + ") " +
                                       KingsField::getObjectName(KingsField::getObjectIDFromUShort(i)));
    }

    void fillWeaponStatsCombo()
    {
        for (byte i = 0; i < GameDB::weaponStatsSize; i++)
        {
            ui->weaponCombo->addItem(QString::number(i) + " (0x" + QString::number(i) + ") " +
                                     KingsField::getWeaponStatsName(i));
        }
    }

    std::shared_ptr<GameDB> gameDB;
    Ui::GameDBEditWidget *ui;
};

#endif // GAMEDBEDITWIDGET_H

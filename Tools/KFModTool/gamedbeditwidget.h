#ifndef GAMEDBEDITWIDGET_H
#define GAMEDBEDITWIDGET_H

#include <QWidget>
#include "ui_gamedbeditwidget.h"
#include "gamedb.h"
#include "models/magictablemodel.h"

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

private:
    std::shared_ptr<GameDB> gameDB;
    Ui::GameDBEditWidget *ui;
};

#endif // GAMEDBEDITWIDGET_H

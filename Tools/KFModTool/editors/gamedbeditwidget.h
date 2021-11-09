#ifndef GAMEDBEDITWIDGET_H
#define GAMEDBEDITWIDGET_H

#include "editors/kfmteditor.h"
#include "ui_gamedbeditwidget.h"
#include <QWidget>

class GameDBEditWidget : public KFMTEditor
{
    Q_OBJECT

public:
    explicit GameDBEditWidget(KFMTFile& file_, QWidget* parent = nullptr);
    ~GameDBEditWidget() {delete ui;}

private slots:
    void on_armorCombo_currentIndexChanged(int index);

    void on_magicCombo_currentIndexChanged(int index);

    void on_objClassCombo_currentIndexChanged(int index);

    void on_levelSpin_valueChanged(int arg1);

    void on_weaponCombo_currentIndexChanged(int index);

private:
    Ui::GameDBEditWidget *ui;
};

#endif // GAMEDBEDITWIDGET_H

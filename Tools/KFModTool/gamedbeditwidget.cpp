#include "gamedbeditwidget.h"

GameDBEditWidget::GameDBEditWidget(QWidget *parent, std::shared_ptr<GameDB> gameDB_) :
    QWidget(parent),
    gameDB(gameDB_),
    ui(new Ui::GameDBEditWidget)
{
    ui->setupUi(this);
    ui->magicCombo->setCurrentIndex(0);
}

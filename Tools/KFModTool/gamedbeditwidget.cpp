#include "gamedbeditwidget.h"
#include "ui_gamedbeditwidget.h"

GameDBEditWidget::GameDBEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDBEditWidget)
{
    ui->setupUi(this);
}

GameDBEditWidget::~GameDBEditWidget()
{
    delete ui;
}

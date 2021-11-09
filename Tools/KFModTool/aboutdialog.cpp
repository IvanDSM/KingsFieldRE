#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->kfmtLabel->setText("KFModTool r" RUNID);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

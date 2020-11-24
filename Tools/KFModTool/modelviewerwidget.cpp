#include "modelviewerwidget.h"
#include "ui_modelviewerwidget.h"

ModelViewerWidget::ModelViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelViewerWidget)
{
    ui->setupUi(this);
}

ModelViewerWidget::~ModelViewerWidget()
{
    delete ui;
}

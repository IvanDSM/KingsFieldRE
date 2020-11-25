#include "modelviewerwidget.h"

ModelViewerWidget::ModelViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelViewerWidget)
{
    ui->setupUi(this);
}

void ModelViewerWidget::setModel(std::shared_ptr<Model> model)
{
    curModel = model;
}


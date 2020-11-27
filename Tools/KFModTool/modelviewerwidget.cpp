#include "modelviewerwidget.h"
#include "models/modelanimationlistmodel.h"
#include "models/modelobjecttablemodel.h"

ModelViewerWidget::ModelViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelViewerWidget)
{
    ui->setupUi(this);
}

void ModelViewerWidget::setModel(std::shared_ptr<Model> model)
{
    curModel = model;
    ui->modelGLView->setModel(model);
    ui->animList->setModel(new ModelAnimationListModel(ui->animList, model));
    ui->objList->setModel(new ModelObjectTableModel(ui->objList, model));
    connect(ui->objList->model(), &ModelObjectTableModel::dataChanged, 
            this, &ModelViewerWidget::objListChanged);
}


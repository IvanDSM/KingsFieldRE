#include "modelviewerwidget.h"
#include "datahandlers/model.h"
#include "models/modelanimationlistmodel.h"
#include "models/modelobjecttablemodel.h"

ModelViewerWidget::ModelViewerWidget(KFMTFile& file_, QWidget* parent)
    : KFMTEditor(file_, parent), ui(new Ui::ModelViewerWidget)
{
    handler = std::make_unique<Model>(file_);
    ui->setupUi(this);

    auto& model = *reinterpret_cast<Model*>(handler.get());
    ui->modelGLView->setModel(model);
    ui->animList->setModel(new ModelAnimationListModel(ui->animList, model));
    ui->objList->setModel(new ModelObjectTableModel(ui->objList, model));
    connect(ui->objList->model(), &ModelObjectTableModel::dataChanged, 
            this, &ModelViewerWidget::objListChanged);
}

void ModelViewerWidget::on_animList_activated(const QModelIndex& index)
{
    ui->modelGLView->setCurAnim(index.row());
}

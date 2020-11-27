#ifndef MODELVIEWERWIDGET_H
#define MODELVIEWERWIDGET_H

#include "model.h"
#include "ui_modelviewerwidget.h"
#include <QWidget>

namespace Ui {
class ModelViewerWidget;
}

class ModelViewerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelViewerWidget(QWidget *parent = nullptr);
    void setModel(std::shared_ptr<Model> model);
    
private slots:
    void objListChanged(const QModelIndex &, const QModelIndex &)
    {
        ui->modelGLView->repaint();
    }
    
private:
    std::shared_ptr<Model> curModel;
    std::unique_ptr<Ui::ModelViewerWidget> ui;
};

#endif // MODELVIEWERWIDGET_H

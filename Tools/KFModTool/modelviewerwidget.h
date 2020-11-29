#ifndef MODELVIEWERWIDGET_H
#define MODELVIEWERWIDGET_H

#include "model.h"
#include "ui_modelviewerwidget.h"
#include <QWidget>

class ModelViewerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelViewerWidget(QWidget *parent = nullptr);
    ~ModelViewerWidget() {delete ui;}
    
    void setModel(std::shared_ptr<Model> model);
    
private slots:
    void objListChanged(const QModelIndex &, const QModelIndex &)
    {
        ui->modelGLView->repaint();
    }
    
    void on_animList_activated(const QModelIndex &index);
    
private:
    std::shared_ptr<Model> curModel;
    Ui::ModelViewerWidget *ui;
};

#endif // MODELVIEWERWIDGET_H

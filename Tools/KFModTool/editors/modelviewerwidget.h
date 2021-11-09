#ifndef MODELVIEWERWIDGET_H
#define MODELVIEWERWIDGET_H

#include "editors/kfmteditor.h"
#include "ui_modelviewerwidget.h"
#include <QWidget>

class ModelViewerWidget : public KFMTEditor
{
    Q_OBJECT
    
public:
    explicit ModelViewerWidget(KFMTFile& file_, QWidget* parent = nullptr);
    ~ModelViewerWidget() {delete ui;}

private slots:
    void objListChanged(const QModelIndex&, const QModelIndex&) { ui->modelGLView->repaint(); }

    void on_animList_activated(const QModelIndex& index);

private:
    Ui::ModelViewerWidget *ui;
};

#endif // MODELVIEWERWIDGET_H

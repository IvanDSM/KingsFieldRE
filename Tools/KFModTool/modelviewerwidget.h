#ifndef MODELVIEWERWIDGET_H
#define MODELVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class ModelViewerWidget;
}

class ModelViewerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelViewerWidget(QWidget *parent = nullptr);
    ~ModelViewerWidget();
    
private:
    Ui::ModelViewerWidget *ui;
};

#endif // MODELVIEWERWIDGET_H

#ifndef MODELGLVIEW_H
#define MODELGLVIEW_H

#include "model.h"
#include <QOpenGLWidget>

class ModelGLView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ModelGLView(QWidget *parent = nullptr, std::shared_ptr<Model> model_ = nullptr) : 
        QOpenGLWidget(parent), model(model_) {}
    void setModel(std::shared_ptr<Model> model_);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    std::shared_ptr<Model> model;
};

#endif // MODELGLVIEW_H

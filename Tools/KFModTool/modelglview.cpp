#include "modelglview.h"

void ModelGLView::setModel(std::shared_ptr<Model> model_)
{
    model = model_;
    repaint();
}

void ModelGLView::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)
    makeCurrent();
    // GL stuff goes here or to a function you call here
}

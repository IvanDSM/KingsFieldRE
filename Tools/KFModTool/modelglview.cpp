#include "modelglview.h"

void ModelGLView::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)
    makeCurrent();
    // GL stuff goes here or to a function you call here
}

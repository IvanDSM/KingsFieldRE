#ifndef MODELGLVIEW_H
#define MODELGLVIEW_H

#include <QOpenGLWidget>

class ModelGLView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ModelGLView(QWidget *parent = nullptr);
    
signals:
    
};

#endif // MODELGLVIEW_H

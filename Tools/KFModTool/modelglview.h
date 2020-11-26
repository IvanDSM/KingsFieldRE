#ifndef MODELGLVIEW_H
#define MODELGLVIEW_H

#include "model.h"
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>

#include <QtMath>

class ModelGLView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ModelGLView(QWidget *parent = nullptr, std::shared_ptr<Model> model_ = nullptr) : 
        QOpenGLWidget(parent), model(model_) {}
    void setModel(std::shared_ptr<Model> model_);
    
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void BuildTMDModel();
    void DrawTMDModel();

    void BuildGrid();
    void DrawGrid();

private:
    std::shared_ptr<Model> model = NULL;

    //Some Vectors the Qt OpenGL libraries should have... Could be static const.
    QVector3D vecLeft  = {1.f, 0.f, 0.f};
    QVector3D vecUp    = {0.f, 1.f, 0.f};
    QVector3D vecFront = {0.f, 0.f, 1.f};

    //Matrices & Vectors
    //We do a weird here, and set the y to -1 for the up vector
    //this is identical to way the PS1 does it's projection (why tho sony)
    QVector3D glCamFrom = {0.f, 64.f, -256.f};
    QVector3D glCamTo   = {0.f, 0.f, 0.f};
    QVector3D glCamUp   = {0.f, 1.f, 0.f};
    QVector3D glWorldScale = {1.f, 1.f, 1.f};
    QVector3D glWorldRotation = {0.f, 0.f, 0.f};

    QMatrix4x4 glMatProj;
    QMatrix4x4 glMatView;
    QMatrix4x4 glMatWorld;

    //OGL Shader
    QOpenGLShaderProgram glProgram;
    unsigned int glProgWVP;

    //OGL Model
    unsigned int glVBO;
    unsigned int glVAO;

    float fRot = 0.0f;

    //
    // Primary Viewer Stuff
    //
    QOpenGLShaderProgram glSimpleProgram;
    unsigned int glSimpleProgramWVP;

    unsigned int glGridVBO;
    unsigned int glGridVAO;
    unsigned int glAxisVBO;
    unsigned int glAxisVAO;
};

#endif // MODELGLVIEW_H

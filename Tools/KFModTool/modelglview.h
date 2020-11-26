#ifndef MODELGLVIEW_H
#define MODELGLVIEW_H

#include "model.h"
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>
#include <QVector3D>

#include <QtMath>

/*!
 * \brief Constexpr function for generating grid at compile-time. I hate the fact this is a global
 * function.
 * \return Generated 3D grid
 */
constexpr std::array<QVector3D, 44> __weiVLGledoM_generateGrid()
{
    std::array<QVector3D, 44> grid;
    
    float gridSect = 20.f;
    int gridPos = 0;
    
    for(int i = 0; i <= 10; ++i)
    {
        grid[gridPos + 0] = {-100.f + (gridSect * i), 0.f, -100.f};
        grid[gridPos + 1] = {-100.f + (gridSect * i), 0.f,  100.f};
        grid[gridPos + 2] = {-100.f, 0.f, -100.f + (gridSect * i)};
        grid[gridPos + 3] = {100.f, 0.f, -100.f + (gridSect * i)};
        gridPos += 4;
    }
    
    return grid;
}

class ModelGLView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ModelGLView(QWidget *parent = nullptr, std::shared_ptr<Model> model_ = nullptr) : 
        QOpenGLWidget(parent), model(model_) 
    {
        connect(&refreshTimer, &QTimer::timeout, this, &ModelGLView::refreshTimeout);
        refreshTimer.start(16);
    }
    void setModel(std::shared_ptr<Model> model_);
    
protected:
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void BuildTMDModel();
    void DrawTMDModel();

    void BuildGrid();
    void DrawGrid();
    
private slots:
    void refreshTimeout() { repaint(); }
    
private:
    std::shared_ptr<Model> model = nullptr;
    
    QTimer refreshTimer{this};
    
    static constexpr std::array<QVector3D, 44> gridVertices = __weiVLGledoM_generateGrid();

    // Some Vectors the Qt OpenGL libraries should have... Could be static const.
    static constexpr QVector3D vecLeft  = {1.f, 0.f, 0.f};
    static constexpr QVector3D vecUp    = {0.f, 1.f, 0.f};
    static constexpr QVector3D vecFront = {0.f, 0.f, 1.f};
    
    // Some constants
    static constexpr float zNear = 0.1f;
    static constexpr float zFar  = 512.0f;
    static constexpr float pFoV  = 60.f;

    // Matrices & Vectors
    // We do a weird here, and set the y to -1 for the up vector
    // this is identical to way the PS1 does it's projection (why tho sony)
    QVector3D glCamFrom = {0.f, 64.f, -256.f};
    QVector3D glCamTo   = {0.f, 0.f, 0.f};
    QVector3D glCamUp   = {0.f, 1.f, 0.f};
    QVector3D glModelScale = {1.f, 1.f, 1.f};
    QVector3D glModelRotation = {0.f, 0.f, 0.f};

    QMatrix4x4 glMatProj;
    QMatrix4x4 glMatView;
    QMatrix4x4 glMatWorld;

    //OGL Shader
    QOpenGLShaderProgram glProgram;
    unsigned int glProgWVP = 0;

    //OGL Model
    unsigned int glVBO = 0;
    unsigned int glVAO = 0;
    bool tmdBuilt = false;
    
    // OGL Functions
    QOpenGLExtraFunctions *glFuncs = nullptr;

    float camRotY = 0.f;
    float camRotZ = 0.f;
    QPoint lastMousePos{-999, -999};

    //
    // Primary Viewer Stuff
    //
    QOpenGLShaderProgram glSimpleProgram;
    unsigned int glSimpleProgramWVP = 0;

    unsigned int glGridVBO = 0;
    unsigned int glGridVAO = 0;
    unsigned int glAxisVBO = 0;
    unsigned int glAxisVAO = 0;
};

#endif // MODELGLVIEW_H

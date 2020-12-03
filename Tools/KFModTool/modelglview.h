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
constexpr std::array<QVector3D, 92> __weiVLGledoM_generateGrid()
{ 
    std::array<QVector3D, 92> grid;
    
    float cellSize = 32.f;
    int   gridOff = 0;
    
    for(int i = 0; i <= 10; ++i)
    {
        if(i == 5)
        {
            //Axis X
            grid[gridOff + 0] = {-2048.f, 0.f, 0.f};
            grid[gridOff + 1] = {1.f, 0.f, 0.f};
            grid[gridOff + 2] = { 2048.f, 0.f, 0.f};
            grid[gridOff + 3] = {1.f, 0.f, 0.f};

            //Axis Z
            grid[gridOff + 4] = {0.f, 0.f, -2048.f};
            grid[gridOff + 5] = {0.f, 0.f, 1.f};
            grid[gridOff + 6] = {0.f, 0.f,  2048.f};
            grid[gridOff + 7] = {0.f, 0.f, 1.f};
        }
        else
        {
            grid[gridOff + 0] = {-160.f + (cellSize * i), 0.f, -160.f };
            grid[gridOff + 1] = {1.f, 1.f, 1.f};
            grid[gridOff + 2] = {-160.f + (cellSize * i), 0.f, 160.f };
            grid[gridOff + 3] = {1.f, 1.f, 1.f};

            grid[gridOff + 4] = {-160.f, 0.f, -160.f + (cellSize * i) };
            grid[gridOff + 5] = {1.f, 1.f, 1.f};
            grid[gridOff + 6] = {160.f, 0.f, -160.f + (cellSize * i) };
            grid[gridOff + 7] = {1.f, 1.f, 1.f};
        }

        gridOff += 8;
    }

    //Axis Y
    grid[gridOff + 0] = {0.f, -160.f, 0.f};
    grid[gridOff + 1] = {0.f, 1.f, 0.f};
    grid[gridOff + 2] = {0.f, 160.f, 0.f };
    grid[gridOff + 3] = {0.f, 1.f, 0.f};
    
    return grid;
}

class ModelGLView : public QOpenGLWidget
{
    Q_OBJECT
public:
    struct TMDVertex
    {
        QVector3D position;
        QVector3D normal;
        QVector4D colour;
        QVector2D texcoord;
    };
    
    struct MOVertex
    {
        QVector3D position1;
        QVector3D position2;
        QVector3D normal;
        QVector4D colour;
        QVector2D texcoord;
    };

    struct GLMesh {
        unsigned int numVertex;
        unsigned int VBO;
        unsigned int VAO;
    };
    
    explicit ModelGLView(QWidget *parent = nullptr, std::shared_ptr<Model> model_ = nullptr) : 
        QOpenGLWidget(parent), model(model_) 
    {
        connect(&refreshTimer, &QTimer::timeout, this, &ModelGLView::refreshTimeout);
        refreshTimer.start(16);

        //Force Qt into using OpenGL 3.0
        QSurfaceFormat fmt;
        fmt.setRenderableType(QSurfaceFormat::OpenGL);
        fmt.setMajorVersion(3);
        fmt.setMinorVersion(0);
        fmt.setSamples(2);

        setFormat(fmt);
        setMouseTracking(true);
    }

    ~ModelGLView()
    {
        glFuncs->glBindVertexArray(0);
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);

        if(model != nullptr)
        {
            for(GLMesh mesh : meshes)
            {
                glFuncs->glDeleteVertexArrays(1, &mesh.VAO);
                glFuncs->glDeleteBuffers(1, &mesh.VBO);
            }
            meshes.clear();

            if(model->animFrames.empty())
            {
                //Clear Shader
                glTMDProgram.release();
                glTMDProgram.removeAllShaders();
            }
            else
            {
                //Clear Shader
                glMOProgram.release();
                glMOProgram.removeAllShaders();

                glMOProgramMVP = 12345678;
            }
        }

        //Clear Grid
        glFuncs->glDeleteVertexArrays(1, &gridMesh.VAO);
        glFuncs->glDeleteBuffers(1, &gridMesh.VBO);

        glSimpleProgram.release();
        glSimpleProgram.removeAllShaders();
    }
    
    bool setCurAnim(int animationIndex)
    {
        if (animationIndex < -1 || static_cast<size_t>(animationIndex) > model->animations.size())
        {
            KFMTError::error("ModelGLView: Tried to set animation to non-existent animation " +
                             QString::number(animationIndex));
            return false;
        }
        
        curAnim = animationIndex;

        animFrame = 0;
        animFrameDelta = 0.f;

        KFMTError::log("Changed Animation: " + QString::number(curAnim));

        if(glFuncs != nullptr)
            BuildMOAnimation();

        return true;
    }
    
    void setModel(std::shared_ptr<Model> model_);
    
protected:
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void resizeGL(int w, int h) override;
    void paintGL() override;
    
private slots:
    void refreshTimeout() { repaint(); }
    
private:
    void BuildMOAnimation();
    void DrawMOAnimation();

    void BuildTMDModel();
    void DrawTMDModel();

    void BuildGrid();
    void DrawGrid();
    
    std::shared_ptr<Model> model = nullptr;
    int curAnim = -1;
    
    QTimer refreshTimer{this};
    
    static constexpr std::array<QVector3D, 92> gridVertices = __weiVLGledoM_generateGrid();

    // Some Vectors the Qt OpenGL libraries should have...
    static constexpr QVector3D vecLeft  = {1.f, 0.f, 0.f};
    static constexpr QVector3D vecUp    = {0.f, 1.f, 0.f};
    static constexpr QVector3D vecFront = {0.f, 0.f, 1.f};
    
    // Some constants
    static constexpr float zNear = 0.1f;
    static constexpr float zFar  = 2048.0f;
    static constexpr float pFoV  = 60.f;

    // Matrices & Vectors
    QVector3D glCamFrom = {0.f, 64.f, -128.f};
    QVector3D glCamTo   = {0.f, 0.f, 0.f};
    QVector3D glCamUp   = {0.f,-1.f, 0.f};

    QVector3D glModelScale = {256.f, 256.f, 256.f};
    QVector3D glModelRotation = {0.f, 0.f, 0.f};

    QMatrix4x4 glMatProj;
    QMatrix4x4 glMatView;
    QMatrix4x4 glMatWorld;

    //Meshes
    std::vector<GLMesh> meshes;

    //MO Stuff
    QOpenGLShaderProgram glMOProgram;
    unsigned int glMOProgramMVP = 12345678;
    unsigned int glMOProgramModel = 0;
    unsigned int glMOProgramLightPos = 0;
    unsigned int glMOProgramWeight = 0;

    unsigned int animFrame = 0;

    float animFrameAdd   = 0.05f;
    float animFrameDelta = 0.f;

    //TMD Stuff
    QOpenGLShaderProgram glTMDProgram;
    unsigned int glTMDProgramMVP = 0;
    unsigned int glTMDProgramModel = 0;
    unsigned int glTMDProgramLightPos = 0;
    
    // OGL Functions
    QOpenGLExtraFunctions *glFuncs = nullptr;

    float camRotY = 0.f;
    float camRotZ = 0.f;
    float camTranslateX = 0.f;
    float camTranslateY = 0.f;
    float camZoom = 128.f;

    QPoint lastMousePos{-999, -999};

    //
    // Primary Viewer Stuff
    //
    QOpenGLShaderProgram glSimpleProgram;
    unsigned int glSimpleProgramMVP = 0;
    GLMesh gridMesh;
};

#endif // MODELGLVIEW_H

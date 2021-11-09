#ifndef MAPVIEWER3D_H
#define MAPVIEWER3D_H

#include "datahandlers/map.h"
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>

class MapViewer3D : public QOpenGLWidget
{
    Q_OBJECT
    using ShaderParam = int;

public:
    explicit MapViewer3D(QWidget* parent = nullptr) : QOpenGLWidget(parent)
    {
        connect(&refreshTimer, &QTimer::timeout, this, &MapViewer3D::refreshTimeout);
        grabKeyboard();
        refreshTimer.start(16);
        setMouseTracking(true);
    }
    ~MapViewer3D()
    {
        makeCurrent();
        tileset.clear();
        psxVRAM.destroy();
        shader.release();
        shader.removeAllShaders();
    }
    void setMap(Map& map_) { map = &map_; }

protected:
    // QWidget interface
    void keyPressEvent(QKeyEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    // QOpenGLWidget interface
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private slots:
    void refreshTimeout() { repaint(); }

private:
    struct TileMesh
    {
        struct Vertex
        {
            QVector3D position;
            QVector3D normal;
            QVector4D colour;
            QVector2D texcoord;
        };

        // These empty constructors are here because C++ is hell.
        // Seriously, go ahead and comment them. See the shitstorm that brews up.
        TileMesh() {}
        TileMesh(TileMesh&&) {}
        ~TileMesh()
        {
            buffer.destroy();
            vao.destroy();
        }

        QOpenGLVertexArrayObject vao;
        QOpenGLBuffer buffer;
        size_t vertexCount;
    };

    void buildShader();
    void buildTileset();
    void buildVRAM();

    bool initialized = false;
    Map* map;
    QOpenGLExtraFunctions* glFuncs = nullptr;
    QOpenGLShaderProgram shader;
    ShaderParam mvp;
    ShaderParam model;
    ShaderParam lightPos;
    QOpenGLTexture psxVRAM{QOpenGLTexture::Target2D};
    std::vector<TileMesh> tileset;

    QTimer refreshTimer{this};

    // Some Vectors the Qt OpenGL libraries should have...
    static constexpr QVector3D vecLeft{1.f, 0.f, 0.f};
    static constexpr QVector3D vecUp{0.f, 1.f, 0.f};
    static constexpr QVector3D vecFront{0.f, 0.f, 1.f};

    // Some constants
    static constexpr float zNear = 0.1f;
    static constexpr float zFar = 16384.0f;
    static constexpr float pFoV = 60.f;

    // Camera stuff
    QVector3D camPos{0.f, 128.f, 0.f};
    QVector3D camFront{0.f, 0.f, 1.f};
    QVector3D camUp{0.f, -1.f, 0.f};
    float camYaw = 90.f;
    float camPitch = 0.f;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 world;

    QPoint lastMousePos{-999, -999};
};

#endif // MAPVIEWER3D_H

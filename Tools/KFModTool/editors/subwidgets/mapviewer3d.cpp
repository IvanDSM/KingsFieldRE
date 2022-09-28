#include "mapviewer3d.h"
#include "core/kfmtcore.h"
#include "datahandlers/model.h"
#include "datahandlers/texturedb.h"
#include <cmath>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>

void MapViewer3D::keyPressEvent(QKeyEvent* event)
{
    static const auto speed = 32.f;

    if (event->key() == Qt::Key_W)
        camPos += camFront * speed;
    else if (event->key() == Qt::Key_S)
        camPos -= camFront * speed;

    if (event->key() == Qt::Key_A)
        camPos -= QVector3D::crossProduct(camFront, camUp).normalized() * speed;
    else if (event->key() == Qt::Key_D)
        camPos += QVector3D::crossProduct(camFront, camUp).normalized() * speed;

    QOpenGLWidget::keyPressEvent(event);
}

void MapViewer3D::mouseReleaseEvent(QMouseEvent*)
{
    lastMousePos = {-999, -999};
}

void MapViewer3D::mouseMoveEvent(QMouseEvent* event)
{
    //Rotation
    if ((event->buttons() & Qt::MiddleButton) != 0)
    {
        if (lastMousePos.x() != -999)
        {
            auto mousePosDiff = event->globalPos() - lastMousePos;

            camYaw += -mousePosDiff.x();
            camPitch += mousePosDiff.y();

            std::clamp(camPitch, -89.f, 89.f);

            camFront = QVector3D(cos(qDegreesToRadians(camYaw)) * cos(qDegreesToRadians(camPitch)),
                                 sin(qDegreesToRadians(camPitch)),
                                 sin(qDegreesToRadians(camYaw)) * cos(qDegreesToRadians(camPitch)))
                           .normalized();
        }
    }

    lastMousePos = event->globalPos();
}

void MapViewer3D::initializeGL()
{
    if (glFuncs == nullptr) glFuncs = context()->extraFunctions();

    //Initialize some basic OGL stuff
    glFuncs->glClearColor(0.f, 0.f, 0.f, 1.f);

    //Set some OGL render states (cull etc)
    glFuncs->glEnable(GL_CULL_FACE);
    glFuncs->glEnable(GL_DEPTH_TEST);
    glFuncs->glEnable(GL_TEXTURE_2D);
}

void MapViewer3D::paintGL()
{
    if (!initialized)
        return;

    //Clear Buffers
    glFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Build View Matrix
    view.setToIdentity();
    view.lookAt(camPos, camPos + camFront, camUp);

    //Build World Matrix
    world.setToIdentity();
    world.scale({80.f, 80.f, 80.f});

    psxVRAM.bind();
    shader.bind();

    // Draw map
    for (size_t layer = 1; layer <= 2; layer++)
        for (size_t x = 0; x < 80; x++)
            for (size_t y = 0; y < 80; y++)
            {
                QMatrix4x4 tileMatrix;

                const auto& tile = map->getTile(x, y, layer);
                if (tile.TileID >= tileset.size()) continue;

                auto& tileMesh = tileset[tile.TileID];
                tileMatrix.translate({static_cast<float>(79 - x) * .5f,
                                      (static_cast<float>(tile.Elevation) * -128.f) / 4096.f,
                                      static_cast<float>(y) * .5f});
                tileMatrix.rotate(tile.Rotation * 90.f - 90.f, vecUp);

                shader.setUniformValue(mvp, (projection * view) * world * tileMatrix);
                shader.setUniformValue(model, tileMatrix);
                shader.setUniformValue(lightPos, camPos);
                tileMesh.vao.bind();
                glFuncs->glDrawArrays(GL_TRIANGLES, 0, tileMesh.vertexCount);
                tileMesh.vao.release();
            }
}

void MapViewer3D::resizeGL(int w, int h)
{
    //Build Projection Matrix according to new w & h
    projection.setToIdentity();
    projection.perspective(pFoV, static_cast<float>(w) / static_cast<float>(h), zNear, zFar);
}

void MapViewer3D::setMap(Map& map_)
{
    map = &map_;

    buildShader();
    buildTileset();
    buildVRAM();

    initialized = true;
}

void MapViewer3D::buildShader()
{
    if (!shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litStatic.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if (!shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if (!shader.link()) KFMTError::error("ModelGLView: Couldn't link GLSL Program...");
    mvp = shader.uniformLocation("uMVP");
    model = shader.uniformLocation("uModel");
    lightPos = shader.uniformLocation("uLightPos");
}

void MapViewer3D::buildTileset()
{
    const auto index = map->getFile().indexInContainer();
    auto rtmd = Model(*core.getFile("RTMD.T", index / 3));

    tileset.reserve(rtmd.baseObjects.size());

    for (const auto& obj : rtmd.baseObjects)
    {
        auto& mesh = tileset.emplace_back();
        std::vector<TileMesh::Vertex> vertices;
        vertices.reserve(obj.vertices.size());
        for (const auto& prim : obj.primitives)
        {
            auto adaptedCoords = prim.getAdaptedTexCoords();

            if (prim.isTriangle())
            {
                TileMesh::Vertex v0;
                TileMesh::Vertex v1;
                TileMesh::Vertex v2;

                //Vertex 1
                v0.position = obj.vertices[prim.vertex0];
                v0.normal = obj.normals[prim.normal0];
                v0.colour = prim.Colour0();
                v0.texcoord = adaptedCoords[0];

                //Vertex 2
                v1.position = obj.vertices[prim.vertex1];
                v1.normal = prim.isSmooth() ? obj.normals[prim.normal1] : obj.normals[prim.normal0];
                v1.colour = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                v1.texcoord = adaptedCoords[1];

                //Vertex 2
                v2.position = obj.vertices[prim.vertex2];
                v2.normal = prim.isSmooth() ? obj.normals[prim.normal2] : obj.normals[prim.normal0];
                v2.colour = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                v2.texcoord = adaptedCoords[2];

                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

                if (prim.isDoubleSided()) //Just reverse-wind the previous triangle
                {
                    vertices.push_back(v0);
                    vertices.push_back(v2);
                    vertices.push_back(v1);
                }
            }
            else if (prim.isQuad())
            {
                TileMesh::Vertex v0;
                TileMesh::Vertex v1;
                TileMesh::Vertex v2;
                TileMesh::Vertex v3;

                //Vertex 1
                v0.position = obj.vertices[prim.vertex0];
                v0.normal = obj.normals[prim.normal0];
                v0.colour = prim.Colour0();
                v0.texcoord = adaptedCoords[0];

                //Vertex 2
                v1.position = obj.vertices[prim.vertex1];
                v1.normal = prim.isSmooth() ? obj.normals[prim.normal1] : obj.normals[prim.normal0];
                v1.colour = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                v1.texcoord = adaptedCoords[1];

                //Vertex 2
                v2.position = obj.vertices[prim.vertex2];
                v2.normal = prim.isSmooth() ? obj.normals[prim.normal2] : obj.normals[prim.normal0];
                v2.colour = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                v2.texcoord = adaptedCoords[2];

                //Vertex 2
                v3.position = obj.vertices[prim.vertex3];
                v3.normal = prim.isSmooth() ? obj.normals[prim.normal3] : obj.normals[prim.normal0];
                v3.colour = prim.isGradation() ? prim.Colour3() : prim.Colour0();
                v3.texcoord = adaptedCoords[3];

                //Split the quad into two seperate triangles

                //Tri 1 (0, 1, 2)
                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

                //Tri 2 (2, 3, 1)
                vertices.push_back(v2);
                vertices.push_back(v3);
                vertices.push_back(v1);

                if (prim.isDoubleSided()) //Just reverse-wind the previous triangle
                {
                    //Tri 1 (0, 1, 2)
                    vertices.push_back(v0);
                    vertices.push_back(v2);
                    vertices.push_back(v1);

                    //Tri 2 (1, 3, 2)
                    vertices.push_back(v1);
                    vertices.push_back(v2);
                    vertices.push_back(v3);
                }
            }
            else
                KFMTError::error("MapViewer3D: Unhandled TMD primitive type (line or sprite).");
        }

        mesh.buffer.create();
        mesh.vao.create();

        mesh.vao.bind();
        mesh.buffer.bind();
        mesh.buffer.allocate(vertices.data(), vertices.size() * sizeof(TileMesh::Vertex));

        shader.setAttributeBuffer(0, GL_FLOAT, offsetof(TileMesh::Vertex, position), 3, 48);
        shader.setAttributeBuffer(1, GL_FLOAT, offsetof(TileMesh::Vertex, normal), 3, 48);
        shader.setAttributeBuffer(2, GL_FLOAT, offsetof(TileMesh::Vertex, colour), 4, 48);
        shader.setAttributeBuffer(3, GL_FLOAT, offsetof(TileMesh::Vertex, texcoord), 2, 48);

        shader.enableAttributeArray(0);
        shader.enableAttributeArray(1);
        shader.enableAttributeArray(2);
        shader.enableAttributeArray(3);

        //mesh.buffer.release();
        mesh.vao.release();
        mesh.vertexCount = vertices.size();
    }
}

void MapViewer3D::buildVRAM()
{
    // We create a vector for the Texture DBs we'll load
    std::vector<TextureDB> textureDBs;

    // and fill that vector up appropriately
    // First we do the game DBs
    switch (core.currentGame())
    {
        case KFMTCore::SimpleGame::KF2: textureDBs.emplace_back(*core.getFile("FDAT.T", 27)); break;
        case KFMTCore::SimpleGame::KF3: textureDBs.emplace_back(*core.getFile("FDAT.T", 84)); break;
        case KFMTCore::SimpleGame::KFPS:
            textureDBs.emplace_back(*core.getFile("FDAT.T", 81));
            break;
        default: break;
    }

    // We also load appropriate subtextures
    const auto index = map->getFile().indexInContainer();
    textureDBs.emplace_back(*core.getFile("RTIM.T", index / 3));

    QImage image({4096, 512}, QImage::Format::Format_RGBA8888);
    QPainter imagePainter(&image);
    imagePainter.setWindow({0, 0, 4096, 512});
    for (auto& db : textureDBs)
        for (size_t i = 0; i < db.getTextureCount(); i++)
        {
            auto& texture = db.getTexture(i);
            imagePainter.drawImage(QRectF(texture.pxVramX,
                                          texture.pxVramY,
                                          texture.pxWidth,
                                          texture.pxHeight),
                                   texture.image,
                                   QRectF(0, 0, texture.pxWidth, texture.pxHeight));
        }
    // For KF2, we re-draw the water texture for the western and eastern shores
    // For some reason the RTMD overwrites it? I dunno
    if (core.currentGame() == KFMTCore::SimpleGame::KF2 && (index == 0 || index == 9))
    {
        const auto& water = textureDBs.front().getTexture(71);
        imagePainter.drawImage(QRectF(water.pxVramX, water.pxVramY, water.pxWidth, water.pxHeight),
                               water.image,
                               QRectF(0, 0, water.pxWidth, water.pxHeight));
    }
    imagePainter.end();

    psxVRAM.setData(image);
    psxVRAM.setMagnificationFilter(QOpenGLTexture::Filter::Nearest);
    psxVRAM.setMinificationFilter(QOpenGLTexture::Filter::Nearest);
}

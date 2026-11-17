#include "modelglview.h"
#include "core/kfmtcore.h"
#include "datahandlers/texturedb.h"
#include <cmath>
#include <iostream>
#include <utility>
#include <QDateTime>
#include <QMouseEvent>
#include <QWheelEvent>

void ModelGLView::initializeGL()
{
    if (glFuncs == nullptr)
        glFuncs = context()->extraFunctions();

    glFuncs->glClearColor(0x34 / 255.0f, 0x49 / 255.0f, 0x5E / 255.0f, 1.f);

    glFuncs->glEnable(GL_CULL_FACE);
    glFuncs->glEnable(GL_DEPTH_TEST);
    glFuncs->glEnable(GL_TEXTURE_2D);

    BuildGrid();
    BuildGizmo();
}

void ModelGLView::mousePressEvent(QMouseEvent* event)
{
    lastMousePos = event->globalPos();
    if (event->button() == Qt::LeftButton && gizmoEnabled)
    {
        const int hit = hitTestGizmo(event->pos());
        if (hit >= 0)
        {
            activeGizmoAxis = hit;
            gizmoDragStartPos = gizmoPos;
            gizmoAccumDelta = {0.f, 0.f, 0.f};
            return;
        }
    }
    activeGizmoAxis = -1;
}

void ModelGLView::mouseMoveEvent(QMouseEvent* event)
{
    if (activeGizmoAxis >= 0 && (event->buttons() & Qt::LeftButton))
    {
        if (lastMousePos.x() != -999)
        {
            const QPoint prevLocal = mapFromGlobal(lastMousePos);
            const QVector3D rawDelta = projectAxisDelta(activeGizmoAxis, prevLocal, event->pos());
            gizmoAccumDelta += rawDelta;

            QVector3D targetPos = gizmoDragStartPos + gizmoAccumDelta;

            if (gizmoSnapFilter)
            {
                targetPos = gizmoSnapFilter(activeGizmoAxis, targetPos, event->modifiers());
            }
            else if ((event->modifiers() & Qt::ShiftModifier) && gizmoSnapStep > 0.f)
            {
                const int a = activeGizmoAxis;
                targetPos[a] = std::round(targetPos[a] / gizmoSnapStep) * gizmoSnapStep;
            }

            const QVector3D appliedDelta = targetPos - gizmoPos;
            if (!appliedDelta.isNull())
            {
                gizmoPos = targetPos;
                if (onGizmoDragged) onGizmoDragged(appliedDelta);
            }
        }
        lastMousePos = event->globalPos();
        repaint();
        return;
    }

    if (gizmoEnabled && event->buttons() == Qt::NoButton)
    {
        const int hit = hitTestGizmo(event->pos());
        if (hit != hoveredGizmoAxis)
        {
            hoveredGizmoAxis = hit;
            setCursor(hit >= 0 ? Qt::SizeAllCursor : Qt::ArrowCursor);
        }
    }

    // Rotation (Middle button always, or Left button when AC1 gizmo mode is active)
    if (event->buttons() == Qt::MiddleButton || (gizmoEnabled && event->buttons() == Qt::LeftButton))
    {
        if (lastMousePos.x() != -999)
        {
            auto mousePosDiff = event->globalPos() - lastMousePos;
            camRotY += (mousePosDiff.x() * 0.0174533f) * 0.25f;
            camRotZ += (mousePosDiff.y() * 0.0174533f) * 0.25f;
        }
    }
    else if (event->buttons() == Qt::RightButton)
    {
        if (lastMousePos.x() != -999)
        {
            auto mousePosDiff = event->globalPos() - lastMousePos;
            camTranslateX += -mousePosDiff.x();
            camTranslateY += mousePosDiff.y();
        }
    }
    lastMousePos = event->globalPos();
}

void ModelGLView::wheelEvent(QWheelEvent* event)
{
    camZoom -= (event->angleDelta().y() / 120.f) * 8.f;
    camZoom = qMax(camZoom, 8.f);
}

void ModelGLView::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    activeGizmoAxis = -1;
    lastMousePos = {-999, -999};
}

void ModelGLView::resizeGL(int w, int h)
{
    if (h == 0) h = 1;
    glMatProj.setToIdentity();
    glMatProj.perspective(pFoV, static_cast<float>(w) / static_cast<float>(h), zNear, zFar);
}

void ModelGLView::paintGL()
{
    glFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Stop camera flipping
    camRotZ = qMin(qMax(-1.570750f, camRotZ), 1.570750f);

    // Orbit around glCamTo
    glCamFrom.setX(glCamTo.x() + std::cos(camRotY) * std::cos(camRotZ) * camZoom);
    glCamFrom.setY(glCamTo.y() + std::sin(camRotZ) * camZoom);
    glCamFrom.setZ(glCamTo.z() + std::sin(camRotY) * std::cos(camRotZ) * camZoom);

    glMatView.setToIdentity();
    glMatView.translate(camTranslateX, camTranslateY, 0);
    glMatView.lookAt(glCamFrom, glCamTo, glCamUp);

    glMatWorld.setToIdentity();
    glMatWorld.scale(glModelScale);
    glMatWorld.rotate(glModelRotation.x(), vecLeft);
    glMatWorld.rotate(glModelRotation.y(), vecUp);
    glMatWorld.rotate(glModelRotation.z(), vecFront);

    DrawGrid();

    switch (curModelType)
    {
    case ModelType::None:
        if (model != nullptr) buildModel();
        break;
    case ModelType::Static:
        DrawTMDModel();
        break;
    case ModelType::Animated:
        DrawMOAnimation();
        break;
    }

    if (!spawnMarkers.empty())
        DrawSpawns();

    if (gizmoEnabled)
        DrawGizmo();
}

void ModelGLView::buildModel()
{
    buildTexture();

    if (model->animations.empty())
    {
        BuildTMDModel();
        curModelType = ModelType::Static;
    }
    else
    {
        BuildMOAnimation();
        setCurAnim(0);
        curModelType = ModelType::Animated;
    }
}

void ModelGLView::BuildMOAnimation()
{
    glFuncs->glBindVertexArray(0);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);

    for (GLMesh& mesh : meshes)
    {
        glFuncs->glDeleteBuffers(mesh.frames.size(), mesh.frames.data());
        glFuncs->glDeleteVertexArrays(1, &mesh.VAO);
    }
    meshes.clear();

    for (const auto& Anim : model->animations)
    {
        unsigned int i = 0;

        GLMesh& glMesh = meshes.emplace_back();
        glMesh.frames.resize(Anim.frameIndexes.size());

        glFuncs->glGenBuffers(Anim.frameIndexes.size(), glMesh.frames.data());
        glFuncs->glGenVertexArrays(1, &glMesh.VAO);
        glFuncs->glBindVertexArray(glMesh.VAO);

        for (const size_t frameID : Anim.frameIndexes)
        {
            const Model::Mesh& frame1 = model->morphTargets[model->animFrames[frameID].frameID];
            const Model::Mesh& frame2
                = i == Anim.frameIndexes.size() - 1
                      ? model->morphTargets[model->animFrames[Anim.frameIndexes[0]].frameID]
                      : model->morphTargets[model->animFrames[frameID + 1].frameID];

            std::vector<MOVertex> vertices;

            for (const auto& prim : model->baseObjects[0].primitives)
            {
                auto adaptedCoords = prim.getAdaptedTexCoords();
                if (prim.isTriangle())
                {
                    MOVertex v0, v1, v2;

                    v0.position1 = frame1.vertices[prim.vertex0];
                    v0.position2 = frame2.vertices[prim.vertex0];
                    v0.normal = frame1.normals[prim.normal0];
                    v0.colour = prim.Colour0();
                    v0.texcoord = adaptedCoords[0];

                    v1.position1 = frame1.vertices[prim.vertex1];
                    v1.position2 = frame2.vertices[prim.vertex1];
                    v1.normal = prim.isSmooth() ? frame1.normals[prim.normal1]
                                                : frame1.normals[prim.normal0];
                    v1.colour = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                    v1.texcoord = adaptedCoords[1];

                    v2.position1 = frame1.vertices[prim.vertex2];
                    v2.position2 = frame2.vertices[prim.vertex2];
                    v2.normal = prim.isSmooth() ? frame1.normals[prim.normal2]
                                                : frame1.normals[prim.normal0];
                    v2.colour = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                    v2.texcoord = adaptedCoords[2];

                    vertices.push_back(v2);
                    vertices.push_back(v1);
                    vertices.push_back(v0);
                }
                else if (prim.isQuad())
                {
                    MOVertex v0, v1, v2, v3;

                    v0.position1 = frame1.vertices[prim.vertex0];
                    v0.position2 = frame2.vertices[prim.vertex0];
                    v0.normal = frame1.normals[prim.normal0];
                    v0.colour = prim.Colour0();
                    v0.texcoord = adaptedCoords[0];

                    v1.position1 = frame1.vertices[prim.vertex1];
                    v1.position2 = frame2.vertices[prim.vertex1];
                    v1.normal = prim.isSmooth() ? frame1.normals[prim.normal1]
                                                : frame1.normals[prim.normal0];
                    v1.colour = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                    v1.texcoord = adaptedCoords[1];

                    v2.position1 = frame1.vertices[prim.vertex2];
                    v2.position2 = frame2.vertices[prim.vertex2];
                    v2.normal = prim.isSmooth() ? frame1.normals[prim.normal2]
                                                : frame1.normals[prim.normal0];
                    v2.colour = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                    v2.texcoord = adaptedCoords[2];

                    v3.position1 = frame1.vertices[prim.vertex3];
                    v3.position2 = frame2.vertices[prim.vertex3];
                    v3.normal = prim.isSmooth() ? frame1.normals[prim.normal3]
                                                : frame1.normals[prim.normal0];
                    v3.colour = prim.isGradation() ? prim.Colour3() : prim.Colour0();
                    v3.texcoord = adaptedCoords[3];

                    vertices.push_back(v2);
                    vertices.push_back(v1);
                    vertices.push_back(v0);

                    vertices.push_back(v2);
                    vertices.push_back(v3);
                    vertices.push_back(v1);
                }
                else
                {
                    KFMTError::error("ModelGLView: Unhandled TMD primitive type (line or sprite).");
                }
            }

            glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glMesh.frames[i]);
            glFuncs->glBufferData(GL_ARRAY_BUFFER,
                                  vertices.size() * sizeof(MOVertex),
                                  vertices.data(),
                                  GL_STATIC_DRAW);
            glMesh.numVertex = vertices.size();
            vertices.clear();
            i++;
        }
    }

    if (glMOProgramMVP == 12345678)
    {
        if (!glMOProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litMime.vert"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

        if (!glMOProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

        if (!glMOProgram.link())
            KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

        glMOProgramMVP = glMOProgram.uniformLocation("uMVP");
        glMOProgramModel = glMOProgram.uniformLocation("uModel");
        glMOProgramLightPos = glMOProgram.uniformLocation("uLightPos");
        glMOProgramWeight = glMOProgram.uniformLocation("uWeight");
    }

    animFrame = 0;
    animFrameDelta = 0.f;
}

void ModelGLView::DrawMOAnimation()
{
    glMOProgram.bind();
    glMOProgram.setUniformValue(glMOProgramMVP, (glMatProj * glMatView) * glMatWorld);
    glMOProgram.setUniformValue(glMOProgramModel, glMatWorld);
    glMOProgram.setUniformValue(glMOProgramLightPos, glCamFrom);
    glMOProgram.setUniformValue(glMOProgramWeight, animFrameDelta);

    psxVRAM.bind();

    glFuncs->glBindVertexArray(meshes[curAnim].VAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, meshes[curAnim].frames[animFrame]);
    glFuncs->glDrawArrays(GL_TRIANGLES, 0, meshes[curAnim].numVertex);

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 60, nullptr);
    glFuncs->glEnableVertexAttribArray(0);
    glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 60, reinterpret_cast<void*>(12));
    glFuncs->glEnableVertexAttribArray(1);
    glFuncs->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 60, reinterpret_cast<void*>(24));
    glFuncs->glEnableVertexAttribArray(2);
    glFuncs->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 60, reinterpret_cast<void*>(36));
    glFuncs->glEnableVertexAttribArray(3);
    glFuncs->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 60, reinterpret_cast<void*>(52));
    glFuncs->glEnableVertexAttribArray(4);

    glFuncs->glBindVertexArray(0);

    animFrameDelta += 0.05f;
    if (animFrameDelta >= 1.f)
    {
        animFrame = (animFrame + 1) % meshes[curAnim].frames.size();
        animFrameDelta = 0.f;
    }
}

void ModelGLView::BuildTMDModel()
{
    if (!model) return;

    for (GLMesh& mesh : meshes)
    {
        glFuncs->glDeleteVertexArrays(1, &mesh.VAO);
        glFuncs->glDeleteBuffers(mesh.frames.size(), mesh.frames.data());
    }
    meshes.clear();

    for (const auto& tmdObj : model->baseObjects)
    {
        std::vector<TMDVertex> vertices;
        GLMesh& mesh = meshes.emplace_back();
        mesh.frames.resize(1);

        auto getVertex = [&](size_t idx) -> QVector3D {
            return idx < tmdObj.vertices.size() ? tmdObj.vertices[idx] : QVector3D(0.f, 0.f, 0.f);
        };
        auto getNormal = [&](size_t idx) -> QVector3D {
            return idx < tmdObj.normals.size() ? tmdObj.normals[idx] : QVector3D(0.f, -1.f, 0.f);
        };

        for (const auto& tmdPrim : tmdObj.primitives)
        {
            auto adaptedCoords = tmdPrim.getAdaptedTexCoords();
            if (tmdPrim.isTriangle())
            {
                TMDVertex v0, v1, v2;

                v0.position = getVertex(tmdPrim.vertex0);
                v0.normal = getNormal(tmdPrim.normal0);
                v0.colour = tmdPrim.Colour0();
                v0.texcoord = adaptedCoords[0];

                v1.position = getVertex(tmdPrim.vertex1);
                v1.normal = tmdPrim.isSmooth() ? getNormal(tmdPrim.normal1)
                                               : getNormal(tmdPrim.normal0);
                v1.colour = tmdPrim.isGradation() ? tmdPrim.Colour1() : tmdPrim.Colour0();
                v1.texcoord = adaptedCoords[1];

                v2.position = getVertex(tmdPrim.vertex2);
                v2.normal = tmdPrim.isSmooth() ? getNormal(tmdPrim.normal2)
                                               : getNormal(tmdPrim.normal0);
                v2.colour = tmdPrim.isGradation() ? tmdPrim.Colour2() : tmdPrim.Colour0();
                v2.texcoord = adaptedCoords[2];
                // ...
            }
            else if (tmdPrim.isQuad())
            {
                TMDVertex v0, v1, v2, v3;

                v0.position = getVertex(tmdPrim.vertex0);
                v0.normal = getNormal(tmdPrim.normal0);
                v0.colour = tmdPrim.Colour0();
                v0.texcoord = adaptedCoords[0];

                v1.position = getVertex(tmdPrim.vertex1);
                v1.normal = tmdPrim.isSmooth() ? getNormal(tmdPrim.normal1)
                                               : getNormal(tmdPrim.normal0);
                v1.colour = tmdPrim.isGradation() ? tmdPrim.Colour1() : tmdPrim.Colour0();
                v1.texcoord = adaptedCoords[1];

                v2.position = getVertex(tmdPrim.vertex2);
                v2.normal = tmdPrim.isSmooth() ? getNormal(tmdPrim.normal2)
                                               : getNormal(tmdPrim.normal0);
                v2.colour = tmdPrim.isGradation() ? tmdPrim.Colour2() : tmdPrim.Colour0();
                v2.texcoord = adaptedCoords[2];

                v3.position = getVertex(tmdPrim.vertex3);
                v3.normal = tmdPrim.isSmooth() ? getNormal(tmdPrim.normal3)
                                               : getNormal(tmdPrim.normal0);
                v3.colour = tmdPrim.isGradation() ? tmdPrim.Colour3() : tmdPrim.Colour0();
                v3.texcoord = adaptedCoords[3];

                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

                vertices.push_back(v2);
                vertices.push_back(v3);
                vertices.push_back(v1);

                if (tmdPrim.isDoubleSided())
                {
                    vertices.push_back(v0);
                    vertices.push_back(v2);
                    vertices.push_back(v1);

                    vertices.push_back(v1);
                    vertices.push_back(v2);
                    vertices.push_back(v3);
                }
            }
            else
                KFMTError::error("ModelGLView: Unhandled TMD primitive type (line or sprite).");
        }

        glFuncs->glGenBuffers(1, mesh.frames.data());
        glFuncs->glGenVertexArrays(1, &mesh.VAO);

        glFuncs->glBindVertexArray(mesh.VAO);
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, mesh.frames[0]);
        glFuncs->glBufferData(GL_ARRAY_BUFFER,
                              vertices.size() * sizeof(TMDVertex),
                              vertices.empty() ? nullptr : &vertices.front(),
                              GL_STATIC_DRAW);

        glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48,
                                       reinterpret_cast<void*>(offsetof(TMDVertex, position)));
        glFuncs->glEnableVertexAttribArray(0);

        glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48,
                                       reinterpret_cast<void*>(offsetof(TMDVertex, normal)));
        glFuncs->glEnableVertexAttribArray(1);

        glFuncs->glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 48,
                                       reinterpret_cast<void*>(offsetof(TMDVertex, colour)));
        glFuncs->glEnableVertexAttribArray(2);

        glFuncs->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 48,
                                       reinterpret_cast<void*>(offsetof(TMDVertex, texcoord)));
        glFuncs->glEnableVertexAttribArray(3);

        glFuncs->glBindVertexArray(0);
        mesh.numVertex = vertices.size();
    }

    // Preserve original KF2 ModelViewerWidget behavior for multi-object TMDs
    if (model->getFile().getDataType() != KFMTFile::DataType::ACMissionStream && model->baseObjects.size() > 1)
    {
        for (auto& obj : model->baseObjects)
            obj.visible = false;
    }

    if (glTMDProgramMVP == 0)
    {
        if (!glTMDProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litStatic.vert"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

        if (!glTMDProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

        if (!glTMDProgram.link())
            KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

        glTMDProgramMVP = glTMDProgram.uniformLocation("uMVP");
        glTMDProgramModel = glTMDProgram.uniformLocation("uModel");
        glTMDProgramLightPos = glTMDProgram.uniformLocation("uLightPos");
    }
}

void ModelGLView::DrawTMDModel()
{
    if (!model || meshes.size() < model->baseObjects.size()) return;

    //Bind GLSL Program
    glTMDProgram.bind();
    glTMDProgram.setUniformValue(glTMDProgramMVP, (glMatProj * glMatView) * glMatWorld);
    glTMDProgram.setUniformValue(glTMDProgramModel, glMatWorld);
    glTMDProgram.setUniformValue(glTMDProgramLightPos, glCamFrom);

    // Bind PSX VRAM texture
    if (psxVRAM.isCreated())
        psxVRAM.bind();

    //Render each object
    for (size_t i = 0; i < model->baseObjects.size(); ++i)
    {
        //Don't render this object if it is not visible.
        if (!model->baseObjects[i].visible || meshes[i].numVertex == 0) continue;

        glFuncs->glBindVertexArray(meshes[i].VAO);
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, meshes[i].numVertex);
        glFuncs->glBindVertexArray(0);
    }
}

void ModelGLView::BuildGrid()
{
    gridMesh.frames.resize(1);
    glFuncs->glGenBuffers(1, gridMesh.frames.data());
    glFuncs->glGenVertexArrays(1, &gridMesh.VAO);

    glFuncs->glBindVertexArray(gridMesh.VAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, gridMesh.frames[0]);
    glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices.data(), GL_STATIC_DRAW);

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, reinterpret_cast<void*>(0));
    glFuncs->glEnableVertexAttribArray(0);
    glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, reinterpret_cast<void*>(12));
    glFuncs->glEnableVertexAttribArray(1);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFuncs->glBindVertexArray(0);

    if (!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/unlitSimple.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if (!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/unlitSimple.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if (!glSimpleProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glSimpleProgramMVP = glSimpleProgram.uniformLocation("uMVP");
}

void ModelGLView::DrawGrid()
{
    glSimpleProgram.bind();
    glSimpleProgram.setUniformValue(glSimpleProgramMVP, (glMatProj * glMatView));

    glFuncs->glBindVertexArray(gridMesh.VAO);
    glFuncs->glDrawArrays(GL_LINES, 0, 46);

    glFuncs->glBindVertexArray(0);
}

void ModelGLView::BuildGizmo()
{
    glFuncs->glGenBuffers(1, &glGizmoVBO);
    glFuncs->glGenVertexArrays(1, &glGizmoVAO);

    glFuncs->glBindVertexArray(glGizmoVAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glGizmoVBO);
    glFuncs->glBufferData(GL_ARRAY_BUFFER, 30 * 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, reinterpret_cast<void*>(0));
    glFuncs->glEnableVertexAttribArray(0);
    glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, reinterpret_cast<void*>(12));
    glFuncs->glEnableVertexAttribArray(1);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFuncs->glBindVertexArray(0);
}

void ModelGLView::DrawGizmo()
{
    if (glGizmoVAO == 0 || glGizmoVBO == 0) return;

    const float len = qMax(32.f, camZoom * 0.22f);
    const float tip = len * 0.18f;
    const float rad = len * 0.055f;

    const std::array<QVector3D, 3> axes   = {{{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}}};
    const std::array<QVector3D, 3> perp1  = {{{0.f, 1.f, 0.f}, {1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}}};
    const std::array<QVector3D, 3> perp2  = {{{0.f, 0.f, 1.f}, {0.f, 0.f, 1.f}, {0.f, 1.f, 0.f}}};
    const std::array<QVector3D, 3> colors = {{{1.f, 0.2f, 0.2f}, {0.2f, 1.f, 0.2f}, {0.25f, 0.55f, 1.f}}};

    std::vector<float> verts;
    verts.reserve(30 * 6);

    auto pushV = [&](const QVector3D& p, const QVector3D& c) {
        verts.push_back(p.x()); verts.push_back(p.y()); verts.push_back(p.z());
        verts.push_back(c.x()); verts.push_back(c.y()); verts.push_back(c.z());
    };

    for (int a = 0; a < 3; a++)
    {
        const bool isHi = (a == activeGizmoAxis || a == hoveredGizmoAxis);
        const QVector3D col = isHi ? QVector3D(1.f, 0.95f, 0.2f) : colors[a];
        const QVector3D end = gizmoPos + axes[a] * len;
        const QVector3D base = gizmoPos + axes[a] * (len - tip);

        pushV(gizmoPos, col); pushV(end, col);
        pushV(end, col); pushV(base + perp1[a] * rad, col);
        pushV(end, col); pushV(base - perp1[a] * rad, col);
        pushV(end, col); pushV(base + perp2[a] * rad, col);
        pushV(end, col); pushV(base - perp2[a] * rad, col);
    }

    glFuncs->glDisable(GL_DEPTH_TEST);
    glFuncs->glLineWidth(3.0f);

    glSimpleProgram.bind();
    glSimpleProgram.setUniformValue(glSimpleProgramMVP, glMatProj * glMatView);

    glFuncs->glBindVertexArray(glGizmoVAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glGizmoVBO);
    glFuncs->glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size() * sizeof(float), verts.data());
    glFuncs->glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(verts.size() / 6));

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFuncs->glBindVertexArray(0);
    glSimpleProgram.release();

    glFuncs->glLineWidth(1.0f);
    glFuncs->glEnable(GL_DEPTH_TEST);
}

void ModelGLView::DrawSpawns()
{
    if (glGizmoVAO == 0 || glGizmoVBO == 0 || spawnMarkers.empty()) return;

    std::vector<float> verts;
    verts.reserve(spawnMarkers.size() * 24 * 6); // 12 edges * 2 verts per octahedron

    auto pushEdge = [&](const QVector3D& a, const QVector3D& b, const QVector3D& c) {
        verts.push_back(a.x()); verts.push_back(a.y()); verts.push_back(a.z());
        verts.push_back(c.x()); verts.push_back(c.y()); verts.push_back(c.z());
        verts.push_back(b.x()); verts.push_back(b.y()); verts.push_back(b.z());
        verts.push_back(c.x()); verts.push_back(c.y()); verts.push_back(c.z());
    };

    for (const auto& sp : spawnMarkers)
    {
        const float r = sp.selected ? 22.f : 12.f;
        const QVector3D col = sp.selected ? QVector3D(1.f, 0.25f, 0.25f) : QVector3D(0.2f, 0.95f, 0.95f);

        const QVector3D top    = sp.pos + QVector3D(0.f, -r * 1.4f, 0.f);
        const QVector3D bottom = sp.pos + QVector3D(0.f,  r * 1.4f, 0.f);
        const QVector3D px     = sp.pos + QVector3D( r, 0.f, 0.f);
        const QVector3D nx     = sp.pos + QVector3D(-r, 0.f, 0.f);
        const QVector3D pz     = sp.pos + QVector3D(0.f, 0.f,  r);
        const QVector3D nz     = sp.pos + QVector3D(0.f, 0.f, -r);

        // Top pyramid edges
        pushEdge(top, px, col); pushEdge(top, nx, col);
        pushEdge(top, pz, col); pushEdge(top, nz, col);
        // Bottom pyramid edges
        pushEdge(bottom, px, col); pushEdge(bottom, nx, col);
        pushEdge(bottom, pz, col); pushEdge(bottom, nz, col);
        // Equator ring
        pushEdge(px, pz, col); pushEdge(pz, nx, col);
        pushEdge(nx, nz, col); pushEdge(nz, px, col);
    }

    glFuncs->glLineWidth(2.0f);
    glSimpleProgram.bind();
    glSimpleProgram.setUniformValue(glSimpleProgramMVP, glMatProj * glMatView);

    glFuncs->glBindVertexArray(glGizmoVAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glGizmoVBO);
    glFuncs->glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_DYNAMIC_DRAW);
    glFuncs->glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(verts.size() / 6));

    // Re-allocate gizmo VBO back to 30 vertices so DrawGizmo()'s glBufferSubData always fits
    glFuncs->glBufferData(GL_ARRAY_BUFFER, 30 * 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFuncs->glBindVertexArray(0);
    glSimpleProgram.release();
    glFuncs->glLineWidth(1.0f);
}

int ModelGLView::hitTestGizmo(const QPoint& mousePos) const
{
    if (!gizmoEnabled || width() <= 0 || height() <= 0) return -1;

    const QMatrix4x4 vp = glMatProj * glMatView;
    auto toScreen = [&](const QVector3D& w) -> QPointF {
        const QVector4D clip = vp * QVector4D(w, 1.f);
        if (clip.w() <= 1e-5f) return {-9999.f, -9999.f};
        return {(clip.x() / clip.w() * 0.5f + 0.5f) * width(),
                (1.f - (clip.y() / clip.w() * 0.5f + 0.5f)) * height()};
    };

    const float len = qMax(32.f, camZoom * 0.22f);
    const std::array<QVector3D, 3> axes = {{{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}}};
    const QPointF pOrigin = toScreen(gizmoPos);
    const QPointF m(mousePos);

    int bestAxis = -1;
    double bestDist = 14.0;

    for (int a = 0; a < 3; a++)
    {
        const QPointF pEnd = toScreen(gizmoPos + axes[a] * len);
        const QPointF seg = pEnd - pOrigin;
        const double segLenSq = seg.x() * seg.x() + seg.y() * seg.y();
        if (segLenSq < 1e-4) continue;

        double t = ((m.x() - pOrigin.x()) * seg.x() + (m.y() - pOrigin.y()) * seg.y()) / segLenSq;
        t = qBound(0.0, t, 1.15);
        const QPointF proj = pOrigin + seg * t;
        const double d = std::hypot(m.x() - proj.x(), m.y() - proj.y());
        if (d < bestDist)
        {
            bestDist = d;
            bestAxis = a;
        }
    }
    return bestAxis;
}

QVector3D ModelGLView::projectAxisDelta(int axis, const QPoint& p0, const QPoint& p1) const
{
    if (axis < 0 || axis > 2 || width() <= 0 || height() <= 0) return {};

    const QMatrix4x4 vp = glMatProj * glMatView;
    auto toScreen = [&](const QVector3D& w) -> QPointF {
        const QVector4D clip = vp * QVector4D(w, 1.f);
        if (clip.w() <= 1e-5f) return {0.f, 0.f};
        return {(clip.x() / clip.w() * 0.5f + 0.5f) * width(),
                (1.f - (clip.y() / clip.w() * 0.5f + 0.5f)) * height()};
    };

    const std::array<QVector3D, 3> axes = {{{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}}};
    const QPointF s0 = toScreen(gizmoPos);
    const QPointF s1 = toScreen(gizmoPos + axes[axis] * 64.f);
    const QPointF screenAxis = s1 - s0;
    const double lenSq = screenAxis.x() * screenAxis.x() + screenAxis.y() * screenAxis.y();
    if (lenSq < 1e-4) return {};

    const QPointF mouseDelta = QPointF(p1 - p0);
    const double pixelsAlongAxis = (mouseDelta.x() * screenAxis.x() + mouseDelta.y() * screenAxis.y()) / lenSq;
    return axes[axis] * static_cast<float>(pixelsAlongAxis * 64.0);
}

void ModelGLView::buildTexture()
{
    if (!model) return;

    QImage image({4096, 512}, QImage::Format::Format_RGBA8888);
    image.fill(Qt::white);

    if (model->getFile().getDataType() != KFMTFile::DataType::ACMissionStream)
    {
        std::vector<TextureDB> textureDBs;

        switch (core.currentGame())
        {
        case KFMTCore::SimpleGame::KF2: textureDBs.emplace_back(*core.getFile("FDAT.T", 27)); break;
        case KFMTCore::SimpleGame::KF3: textureDBs.emplace_back(*core.getFile("FDAT.T", 84)); break;
        case KFMTCore::SimpleGame::KFPS: textureDBs.emplace_back(*core.getFile("FDAT.T", 81)); break;
        default: break;
        }

        const auto fileName = model->getFile().filePath;
        const auto index = model->getFile().indexInContainer();

        if (fileName.contains("RTMD"))
            textureDBs.emplace_back(*core.getFile("RTIM.T", index));
        else if (fileName.contains("MO"))
            textureDBs.emplace_back(*core.getFile("RTIM.T", 0));

        if (!textureDBs.empty())
        {
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
            imagePainter.end();
        }
    }

    if (psxVRAM.isCreated())
        psxVRAM.destroy();

    psxVRAM.setData(image);
    psxVRAM.setMagnificationFilter(QOpenGLTexture::Filter::Nearest);
    psxVRAM.setMinificationFilter(QOpenGLTexture::Filter::Nearest);
}
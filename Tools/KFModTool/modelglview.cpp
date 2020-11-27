#include "modelglview.h"
#include <iostream> 
#include <QMouseEvent>
#include <QWheelEvent>

void ModelGLView::setModel(std::shared_ptr<Model> model_)
{    
    model = model_;
}

void ModelGLView::initializeGL()
{
    if (glFuncs == nullptr)
        glFuncs = context()->extraFunctions();
    
    //Initialize some basic OGL stuff
    glFuncs->glClearColor(0x34 / 255.0f, 0x49 / 255.0f, 0x5E / 255.0f, 1.f);    //Nice Palettes: https://htmlcolorcodes.com/

    //Set some OGL render states (cull etc)
    glFuncs->glEnable(GL_CULL_FACE);
    glFuncs->glEnable(GL_DEPTH_TEST);

    BuildGrid();

    while (model == nullptr) { /* Wait for model */ };
    BuildTMDModel();
}

void ModelGLView::mouseMoveEvent(QMouseEvent * event)
{
    //Rotation
    if (event->buttons() == Qt::MiddleButton)
    {
        if (lastMousePos.x() != -999)
        {
            auto mousePosDiff = event->globalPos() - lastMousePos;
            camRotY += (mousePosDiff.x() * 0.0174533) * 0.25f;
            camRotZ += (mousePosDiff.y() * 0.0174533) * 0.25f;
        }
        lastMousePos = event->globalPos();
    }
}

void ModelGLView::wheelEvent(QWheelEvent *event)
{
   camZoom += event->pixelDelta().y();
}

void ModelGLView::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event)
    lastMousePos = {-999, -999};
}

void ModelGLView::resizeGL(int w, int h)
{
    //Build Projection Matrix according to new w & h
    glMatProj.setToIdentity();
    glMatProj.perspective(pFoV, (float)w / (float)h, zNear, zFar);
}

void ModelGLView::paintGL()
{
    //Clear Buffers
    glFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Apply Rotation to glCamFrom
    glCamFrom.setX(qCos(camRotY) * qCos(camRotZ) * camZoom);
    glCamFrom.setY(qSin(camRotZ) * camZoom);
    glCamFrom.setZ(qSin(camRotY) * qCos(camRotZ) * camZoom);

    //Build View Matrix
    glMatView.setToIdentity();
    glMatView.lookAt(glCamFrom, glCamTo, glCamUp);

    //Build World Matrix
    glMatWorld.setToIdentity();
    glMatWorld.scale(glModelScale);
    glMatWorld.rotate(glModelRotation.x(), vecLeft);
    glMatWorld.rotate(glModelRotation.y(), vecUp);
    glMatWorld.rotate(glModelRotation.z(), vecFront);

    //glMatView.rotate(camRotY, vecUp);
    //glMatView.rotate(camRotZ, vecLeft);
    
    DrawGrid();
    DrawTMDModel();
}

void ModelGLView::BuildTMDModel()
{
    //Loop through each object and build it for OpenGL.
    std::vector<TMDVertex> vertices;

    //
    // To-do : refactor this gigantic mess
    //    Load Normals, Colour and Texcoord
    // Vec3 to QVector3D function pls?
    //
    for(Model::Mesh& tmdObj : model->baseObjects)
    {
        for(Model::Primitive tmdPrim : tmdObj.primitives)
        {
            if(tmdPrim.isTriangle())
            {
                //Add 3 vertices to the list
                TMDVertex v0, v1, v2;

                //Vertex 1
                v0.position = tmdObj.vertices[tmdPrim.vertex0];
                v0.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal0] : tmdObj.normals[tmdPrim.normal0];
                v0.colour = tmdPrim.isGradation() ? tmdPrim.Colour0() : tmdPrim.Colour0();
                v0.texcoord = {0.f,0.f};

                //Vertex 2
                v1.position = tmdObj.vertices[tmdPrim.vertex1];
                v1.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal1] : tmdObj.normals[tmdPrim.normal0];
                v1.colour = tmdPrim.isGradation() ? tmdPrim.Colour1() : tmdPrim.Colour0();
                v1.texcoord = {0.f,0.f};

                //Vertex 2
                v2.position = tmdObj.vertices[tmdPrim.vertex2];
                v2.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal2] : tmdObj.normals[tmdPrim.normal0];
                v2.colour = tmdPrim.isGradation() ? tmdPrim.Colour2() : tmdPrim.Colour0();
                v2.texcoord = {0.f,0.f};

                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

            }
            else if (tmdPrim.isQuad())
            {
                //Add 4 vertices to the list
                TMDVertex v0, v1, v2, v3;

                //Vertex 1
                v0.position = tmdObj.vertices[tmdPrim.vertex0];
                v0.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal0] : tmdObj.normals[tmdPrim.normal0];
                v0.colour = tmdPrim.isGradation() ? tmdPrim.Colour0() : tmdPrim.Colour0();
                v0.texcoord = {0.f,0.f};

                //Vertex 2
                v1.position = tmdObj.vertices[tmdPrim.vertex1];
                v1.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal1] : tmdObj.normals[tmdPrim.normal0];
                v1.colour = tmdPrim.isGradation() ? tmdPrim.Colour1() : tmdPrim.Colour0();
                v1.texcoord = {0.f,0.f};

                //Vertex 2
                v2.position = tmdObj.vertices[tmdPrim.vertex2];
                v2.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal2] : tmdObj.normals[tmdPrim.normal0];
                v2.colour = tmdPrim.isGradation() ? tmdPrim.Colour2() : tmdPrim.Colour0();
                v2.texcoord = {0.f,0.f};

                //Vertex 2
                v3.position = tmdObj.vertices[tmdPrim.vertex3];
                v3.normal = tmdPrim.isSmooth() ? tmdObj.normals[tmdPrim.normal3] : tmdObj.normals[tmdPrim.normal0];
                v3.colour = tmdPrim.isGradation() ? tmdPrim.Colour3() : tmdPrim.Colour0();
                v3.texcoord = {0.f,0.f};

                //Split the quad into two seperate triangles

                //Tri 1 (0, 1, 2)
                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

                //Tri 2 (1, 2, 3)
                vertices.push_back(v3);
                vertices.push_back(v2);
                vertices.push_back(v1);
            }
            else
                KFMTError::error("ModelGLView: Unhandled TMD primitive type (line or sprite).");
        }

        //Begin Generating OpenGL stuff for this object
        glFuncs->glGenBuffers(1, &tmdObj.oglVertexBufferObject);
        glFuncs->glGenVertexArrays(1, &tmdObj.oglVertexArrayObject);

        //Bind array buffer
        glFuncs->glBindVertexArray(tmdObj.oglVertexArrayObject);

        //bind vertex buffer, and copy the data to it
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, tmdObj.oglVertexBufferObject);
        glFuncs->glBufferData(GL_ARRAY_BUFFER, 48 * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

        //Set up the offsets and strides of each component of the vertex...

        //Position
        glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48, (void*)0);
        glFuncs->glEnableVertexAttribArray(0);

        //Normal
        glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48, (void*)12);
        glFuncs->glEnableVertexAttribArray(1);

        //Colour
        glFuncs->glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 48, (void*)24);
        glFuncs->glEnableVertexAttribArray(2);

        //Texcoord
        glFuncs->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 48, (void*)40);
        glFuncs->glEnableVertexAttribArray(3);

        //Unbind buffers
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
        glFuncs->glBindVertexArray(0);

        //Set vertex number for draw...
        tmdObj.oglVertexNum = vertices.size();
    }

    //Now we build the shaders required for rendering
    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litStatic.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if(!glProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glProgramMVP = glProgram.uniformLocation("uMVP");
    glProgramModel = glProgram.uniformLocation("uModel");
    glProgramLightPos = glProgram.uniformLocation("uLightPos");

    tmdBuilt = true;
}

void ModelGLView::DrawTMDModel()
{
    //Bind GLSL Program
    glProgram.bind();
    glProgram.setUniformValue(glProgramMVP, (glMatProj * glMatView) * glMatWorld);
    glProgram.setUniformValue(glProgramModel, glMatWorld);
    glProgram.setUniformValue(glProgramLightPos, glCamFrom);

    for(Model::Mesh tmdObj : model->baseObjects)
    {
        if(!tmdObj.visible)
           continue;

        glFuncs->glBindVertexArray(tmdObj.oglVertexArrayObject);
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, tmdObj.oglVertexNum);

        glFuncs->glBindVertexArray(0);
    }
}

//
// GL Grid
//
void ModelGLView::BuildGrid()
{
    glFuncs->glGenBuffers(1, &glGridVBO);
    glFuncs->glGenVertexArrays(1, &glGridVAO);

    glFuncs->glBindVertexArray(glGridVAO);
    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glGridVBO);
    glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices.data(), GL_STATIC_DRAW);

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glFuncs->glEnableVertexAttribArray(0);
    glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glFuncs->glEnableVertexAttribArray(1);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFuncs->glBindVertexArray(0);

    //Build Shader
    if(!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/unlitSimple.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if(!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/unlitSimple.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if(!glSimpleProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glSimpleProgramMVP = glSimpleProgram.uniformLocation("uMVP");
}

void ModelGLView::DrawGrid()
{
    //Bind GLSL Program
    glSimpleProgram.bind();
    glSimpleProgram.setUniformValue(glSimpleProgramMVP, (glMatProj * glMatView));

    glFuncs->glBindVertexArray(glGridVAO);
    glFuncs->glDrawArrays(GL_LINES, 0, 46);

    glFuncs->glBindVertexArray(0);
}

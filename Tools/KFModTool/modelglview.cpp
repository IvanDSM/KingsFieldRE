#include "modelglview.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream> 
#include <utility>

void ModelGLView::setModel(std::shared_ptr<Model> model_)
{    
    model = std::move(model_);
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
    if(model->animations.empty())
        BuildTMDModel();
    else
        setCurAnim(0);
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
    camZoom -= (event->angleDelta().y() / 120.f) * 8.f;
    camZoom = qMax(camZoom, 8.f);
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
    glMatProj.perspective(pFoV, static_cast<float>(w) / static_cast<float>(h), zNear, zFar);
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
    
    DrawGrid();

    //If curAnim is -1, we must be drawing a TMD, else it's MO
    if(curAnim == -1)
    {
        DrawTMDModel();
    }else{
        DrawMOAnimation();
    }
}

//
// MO Build & Draw
//
void ModelGLView::BuildMOAnimation()
{
    //Get the animation from the model
    Model::MOAnimation Anim = model->animations[curAnim];
    Model::Mesh frame1;
    Model::Mesh frame2;

    //Build each animation frame
    unsigned int i = 0;


    for(size_t frameID : Anim.frameIndexes)
    {
         Model::MOFrame &moFrame = model->animFrames[frameID];

         //My little, not very safe safe guard.
         if(moFrame.glVAO > 0)
             continue;

        if(i == Anim.frameIndexes.size()-1)
        {
            frame1 = model->morphTargets[model->animFrames[Anim.frameIndexes[Anim.frameIndexes.size()-1]].frameID];
            frame2 = model->morphTargets[model->animFrames[Anim.frameIndexes[0]].frameID];

            KFMTError::log("Frames End: ");
            KFMTError::log("    f1: " + QString::number(model->animFrames[Anim.frameIndexes[Anim.frameIndexes.size()-1]].frameID));
            KFMTError::log("    f2: " + QString::number(model->animFrames[Anim.frameIndexes[0]].frameID));
        }else
        {
            frame1 = model->morphTargets[model->animFrames[frameID].frameID];
            frame2 = model->morphTargets[model->animFrames[frameID+1].frameID];

            if((frameID+1) > model->animFrames.size())
            {
                KFMTError::error("GLModelView: Frame ID exceeded maximum");
                KFMTError::log("This should be impossible!");
            }

            KFMTError::log("Frames Mid/Start: ");
            KFMTError::log("    f1: " + QString::number(model->animFrames[frameID].frameID));
            KFMTError::log("    f2: " + QString::number(model->animFrames[frameID+1].frameID));
        }

        //Now build the actual frame!
        std::vector<MOVertex> vertices;
        for(Model::Primitive &prim : model->baseObjects[0].primitives)
        {
            if(prim.isTriangle())
            {
                MOVertex v0, v1, v2;

                //Vertex 1
                v0.position1 = frame1.vertices[prim.vertex0];
                v0.position2 = frame2.vertices[prim.vertex0];
                v0.normal    = prim.isSmooth() ? frame1.normals[prim.normal0] : frame1.normals[prim.normal0];
                v0.colour    = prim.isGradation() ? prim.Colour0() : prim.Colour0();
                v0.texcoord  = {0.f,0.f};

                //Vertex 2
                v1.position1 = frame1.vertices[prim.vertex1];
                v1.position2 = frame2.vertices[prim.vertex1];
                v1.normal    = prim.isSmooth() ? frame1.normals[prim.normal1] : frame1.normals[prim.normal0];
                v1.colour    = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                v1.texcoord  = {0.f,0.f};

                //Vertex 3
                v2.position1 = frame1.vertices[prim.vertex2];
                v2.position2 = frame2.vertices[prim.vertex2];
                v2.normal    = prim.isSmooth() ? frame1.normals[prim.normal2] : frame1.normals[prim.normal0];
                v2.colour    = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                v2.texcoord  = {0.f,0.f};

                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

            }else
            if(prim.isQuad())
            {
                MOVertex v0, v1, v2, v3;

                //Vertex 1
                v0.position1 = frame1.vertices[prim.vertex0];
                v0.position2 = frame2.vertices[prim.vertex0];
                v0.normal    = prim.isSmooth() ? frame1.normals[prim.normal0] : frame1.normals[prim.normal0];
                v0.colour    = prim.isGradation() ? prim.Colour0() : prim.Colour0();
                v0.texcoord  = {0.f,0.f};

                //Vertex 2
                v1.position1 = frame1.vertices[prim.vertex1];
                v1.position2 = frame2.vertices[prim.vertex1];
                v1.normal    = prim.isSmooth() ? frame1.normals[prim.normal1] : frame1.normals[prim.normal0];
                v1.colour    = prim.isGradation() ? prim.Colour1() : prim.Colour0();
                v1.texcoord  = {0.f,0.f};

                //Vertex 3
                v2.position1 = frame1.vertices[prim.vertex2];
                v2.position2 = frame2.vertices[prim.vertex2];
                v2.normal    = prim.isSmooth() ? frame1.normals[prim.normal2] : frame1.normals[prim.normal0];
                v2.colour    = prim.isGradation() ? prim.Colour2() : prim.Colour0();
                v2.texcoord  = {0.f,0.f};

                //Vertex 4
                v3.position1 = frame1.vertices[prim.vertex3];
                v3.position2 = frame2.vertices[prim.vertex3];
                v3.normal    = prim.isSmooth() ? frame1.normals[prim.normal3] : frame1.normals[prim.normal0];
                v3.colour    = prim.isGradation() ? prim.Colour3() : prim.Colour0();
                v3.texcoord  = {0.f,0.f};

                //Tri 1 (0, 1, 2)
                vertices.push_back(v2);
                vertices.push_back(v1);
                vertices.push_back(v0);

                //Tri 2 (1, 3, 2)
                vertices.push_back(v2);
                vertices.push_back(v3);
                vertices.push_back(v1);

            }else{
                KFMTError::error("ModelGLView: Unhandled TMD primitive type (line or sprite).");
            }
        }

        //Begin Generating OpenGL stuff for this frame
        glFuncs->glGenBuffers(1, &moFrame.glVBO);
        glFuncs->glGenVertexArrays(1, &moFrame.glVAO);

        //Bind array buffer
        glFuncs->glBindVertexArray(moFrame.glVAO);

        //bind vertex buffer, and copy the data to it
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, moFrame.glVBO);
        glFuncs->glBufferData(GL_ARRAY_BUFFER, 60 * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

        //Set up the offsets and strides of each component of the vertex...

        //Position 1
        glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 60, (void*)0);
        glFuncs->glEnableVertexAttribArray(0);

        //Position 2
        glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 60, (void*)12);
        glFuncs->glEnableVertexAttribArray(1);

        //Normal
        glFuncs->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 60, (void*)24);
        glFuncs->glEnableVertexAttribArray(2);

        //Colour
        glFuncs->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 60, (void*)36);
        glFuncs->glEnableVertexAttribArray(3);

        //Texcoord
        glFuncs->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 60, (void*)52);
        glFuncs->glEnableVertexAttribArray(4);

        //Unbind buffers
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
        glFuncs->glBindVertexArray(0);

        //Set vertex number for draw...
        moFrame.glVertexNum = vertices.size();
        i++;
    }

    //Build MO Shader (only once though)
    if(glMOProgramMVP == 12345678)
    {
        if(!glMOProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litMime.vert"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

        if(!glMOProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
            KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

        if(!glMOProgram.link())
            KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

        glMOProgramMVP = glMOProgram.uniformLocation("uMVP");
        glMOProgramModel = glMOProgram.uniformLocation("uModel");
        glMOProgramLightPos = glMOProgram.uniformLocation("uLightPos");
        glMOProgramWeight = glMOProgram.uniformLocation("uWeight");
    }
}

void ModelGLView::DrawMOAnimation()
{
    //Set up the shader...
    glMOProgram.bind();
    glMOProgram.setUniformValue(glMOProgramMVP, (glMatProj * glMatView) * glMatWorld);
    glMOProgram.setUniformValue(glMOProgramModel, glMatWorld);
    glMOProgram.setUniformValue(glMOProgramLightPos, glCamFrom);
    glMOProgram.setUniformValue(glMOProgramWeight, animFrameDelta);

    //Draw it...
    //Get current animation
    uint convertedInd = model->animations[curAnim].frameIndexes[animFrame];

    glFuncs->glBindVertexArray(model->animFrames[convertedInd].glVAO);
    glFuncs->glDrawArrays(GL_TRIANGLES, 0, model->animFrames[convertedInd].glVertexNum);

    glFuncs->glBindVertexArray(0);

    //Some quick 'n' dirty logic to make things move
    animFrameDelta += 0.01;
    if(animFrameDelta >= 1.f)
    {
        animFrame++;

        if(animFrame >= model->animations[curAnim].frameIndexes.size())
        {
            animFrame = 0;
        }

        KFMTError::log("Frame: " + QString::number(animFrame));
        animFrameDelta = 0.f;
    }
}

//
// TMD/RTMD Build & Draw
//
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

                //Tri 2 (1, 3, 2)
                vertices.push_back(v2);
                vertices.push_back(v3);
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
    if(!glTMDProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/litStatic.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if(!glTMDProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/litCommon.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if(!glTMDProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glTMDProgramMVP = glTMDProgram.uniformLocation("uMVP");
    glTMDProgramModel = glTMDProgram.uniformLocation("uModel");
    glTMDProgramLightPos = glTMDProgram.uniformLocation("uLightPos");
}

void ModelGLView::DrawTMDModel()
{
    //Bind GLSL Program
    glTMDProgram.bind();
    glTMDProgram.setUniformValue(glTMDProgramMVP, (glMatProj * glMatView) * glMatWorld);
    glTMDProgram.setUniformValue(glTMDProgramModel, glMatWorld);
    glTMDProgram.setUniformValue(glTMDProgramLightPos, glCamFrom);

    for(const Model::Mesh& tmdObj : model->baseObjects)
    {
        if(tmdObj.visible)
        {
            glFuncs->glBindVertexArray(tmdObj.oglVertexArrayObject);
            glFuncs->glDrawArrays(GL_TRIANGLES, 0, tmdObj.oglVertexNum);

            glFuncs->glBindVertexArray(0);
        }
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

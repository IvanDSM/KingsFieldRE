#include "modelglview.h"
#include <iostream> 
#include <QMouseEvent>

void ModelGLView::setModel(std::shared_ptr<Model> model_)
{
    //Destroy all previously created GL resources
    if(model != NULL)
    {
        glProgram.removeAllShaders();

        glFuncs->glDeleteBuffers(1, &glVBO);
        glFuncs->glDeleteVertexArrays(1, &glVAO);
    }
    model = model_;

    //Build model
    //Imaginary IF statement where we check if it's MO, TMD or RTMD
    BuildTMDModel();
}

void ModelGLView::initializeGL()
{
    if (glFuncs == nullptr)
        glFuncs = context()->extraFunctions();
    
    //Initialize some basic OGL stuff
    glFuncs->glClearColor(0x34 / 255.0f, 0x49 / 255.0f, 0x5E / 255.0f, 1.f);    //Nice Palettes: https://htmlcolorcodes.com/

    //Set some OGL render states (cull etc)
    //glFuncs->glCullFace(GL_BACK);
    //glFuncs->glEnable(GL_CULL_FACE);
    //glFuncs->glDepthFunc(GL_LEQUAL);
    //glFuncs->glEnable(GL_DEPTH_TEST);
    glFuncs->glLineWidth(1.f);
    //glFuncs->glEnable(GL_LINE);
    //BuildTMDModel();
    BuildGrid();
    
}

void ModelGLView::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::MiddleButton)
    {
        if (lastMousePos.x() != -999)
        {
            auto mousePosDiff = event->globalPos() - lastMousePos;
            camRotY += mousePosDiff.x() * 0.25f;
            camRotZ += mousePosDiff.y() * 0.25f;
        }
        lastMousePos = event->globalPos();
    }
}

void ModelGLView::mouseReleaseEvent(QMouseEvent * event)
{
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
    glFuncs->glClear(GL_COLOR_BUFFER_BIT);

    //Build View Matrix
    glMatView.setToIdentity();
    glMatView.lookAt(glCamFrom, glCamTo, glCamUp);

    //Build World Matrix
    glMatWorld.setToIdentity();
    glMatWorld.scale(glModelScale);
    glMatWorld.rotate(glModelRotation.x(), vecLeft);
    glMatWorld.rotate(0.f, vecUp);
    glMatWorld.rotate(glModelRotation.z(), vecFront);

    glModelRotation.setY(0.f);

    glMatView.rotate(camRotY, vecUp);
    glMatView.rotate(camRotZ, vecLeft);
    
    DrawGrid();

    //Here's where we finally draw...
    //Imaginary IF statement where we check if it's MO, TMD or RTMD

    //DrawTMDModel();
}

void ModelGLView::BuildTMDModel()
{
    //BuildTMDModel Imagines that all objects are parts of a bigger mesh

    //Build Model
    glFuncs->glGenBuffers(1, &glVBO);
    glFuncs->glGenVertexArrays(1, &glVAO);

    //Build VertexBuffer in memory ready for copy
    float vertices[] = {
        -128.f, -128.f, 0.0f,
         128.f, -128.f, 0.0f,
          0.0f,  128.f, 0.0f
    };

    //Copy to GL
    glFuncs->glBindVertexArray(glVAO);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glFuncs->glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

    glFuncs->glEnableVertexAttribArray(0);
    //glFuncs->glEnableVertexAttribArray(1);

    glFuncs->glBindVertexArray(0);

    //Build Shader
    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tmdShader.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tmdShader.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if(!glProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glProgWVP = glProgram.uniformLocation("uWVP");
}

void ModelGLView::DrawTMDModel()
{
    //Bind GLSL Program
    glProgram.bind();
    glProgram.setUniformValue(glProgWVP, (glMatProj * glMatView * glMatWorld));

    glFuncs->glBindVertexArray(glVAO);
    glFuncs->glDrawArrays(GL_TRIANGLES, 0, 3);
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

    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
    glFuncs->glEnableVertexAttribArray(0);
    glFuncs->glBindVertexArray(0);

    //Build Shader
    //TO-DO: (Change this to use 'simpleShader.vert / simpleShader.frag'
    if(!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tmdShader.vert"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Vertex Shader...");

    if(!glSimpleProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tmdShader.frag"))
        KFMTError::error("ModelGLView: Couldn't load GLSL Fragment Shader...");

    if(!glSimpleProgram.link())
        KFMTError::error("ModelGLView: Couldn't link GLSL Program...");

    glSimpleProgramWVP = glSimpleProgram.uniformLocation("uWVP");
}

void ModelGLView::DrawGrid()
{
    //Bind GLSL Program
    glSimpleProgram.bind();
    glSimpleProgram.setUniformValue(glSimpleProgramWVP, (glMatProj * glMatView));

    glFuncs->glBindVertexArray(glGridVAO);
    glFuncs->glDrawArrays(GL_LINES, 0, 44);
}

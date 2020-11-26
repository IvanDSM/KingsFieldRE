#include "modelglview.h"

//
// Some constants
//
static const float zNear = 0.1f;
static const float zFar  = 512.0f;
static const float pFoV  = 60.f;

QOpenGLFunctions *F;
QOpenGLExtraFunctions *E;

void ModelGLView::setModel(std::shared_ptr<Model> model_)
{
    //Destroy all previously created GL resources
    if(model != NULL)
    {
        //Get OGL Functions
        E = QOpenGLContext::currentContext()->extraFunctions();
        F = QOpenGLContext::currentContext()->functions();

        glProgram.removeAllShaders();

        E->glDeleteBuffers(1, &glVBO);
        E->glDeleteVertexArrays(1, &glVAO);
    }
    model = model_;

    //Build model
    //Imaginary IF statement where we check if it's MO, TMD or RTMD
    BuildTMDModel();
}

void ModelGLView::initializeGL()
{
    //Get OGL Functions
    E = QOpenGLContext::currentContext()->extraFunctions();
    F = QOpenGLContext::currentContext()->functions();

    //Initialize some basic OGL stuff
    F->glClearColor(0x34 / 255.0f, 0x49 / 255.0f, 0x5E / 255.0f, 1.f);    //Nice Palettes: https://htmlcolorcodes.com/

    //Set some OGL render states (cull etc)
    //F->glCullFace(GL_BACK);
    //F->glEnable(GL_CULL_FACE);
    //F->glDepthFunc(GL_LEQUAL);
    //F->glEnable(GL_DEPTH_TEST);

    BuildTMDModel();
}

void ModelGLView::resizeGL(int w, int h)
{
    //Build Projection Matrix according to new w & h
    glMatProj.setToIdentity();
    glMatProj.perspective(pFoV, (float)w / (float)h, zNear, zFar);
}

void ModelGLView::paintGL()
{
    //Get OGL Functions
    E = QOpenGLContext::currentContext()->extraFunctions();
    F = QOpenGLContext::currentContext()->functions();

    //Clear Buffers
    F->glClear(GL_COLOR_BUFFER_BIT);

    //Build View Matrix
    glMatView.setToIdentity();
    glMatView.lookAt(glCamFrom, glCamTo, glCamUp);

    //Build World Matrix
    glMatWorld.setToIdentity();
    glMatWorld.scale(glWorldScale);
    glMatWorld.rotate(glWorldRotation.x(), vecLeft);
    glMatWorld.rotate(fRot, vecUp);
    glMatWorld.rotate(glWorldRotation.z(), vecFront);

    glWorldRotation.setY(fRot);

    fRot += 15.0f;

    //Here's where we finally draw...
    //Imaginary IF statement where we check if it's MO, TMD or RTMD
    DrawTMDModel();
}

void ModelGLView::BuildTMDModel()
{
    //BuildTMDModel Imagines that all objects are parts of a bigger mesh

    //Build Model
    F->glGenBuffers(1, &glVBO);
    E->glGenVertexArrays(1, &glVAO);

    //Build VertexBuffer in memory ready for copy
    float vertices[] = {
        -128.f, -128.f, 0.0f,
         128.f, -128.f, 0.0f,
          0.0f,  128.f, 0.0f
    };

    //Copy to GL
    E->glBindVertexArray(glVAO);

    E->glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    E->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    F->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //F->glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

    F->glEnableVertexAttribArray(0);
    //F->glEnableVertexAttribArray(1);

    E->glBindVertexArray(0);

    //Build Shader
    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tmdShader.vert"))
        KFMTError::error("Couldn't load GLSL Vertex Shader...");

    if(!glProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tmdShader.frag"))
        KFMTError::error("Couldn't load GLSL Fragment Shader...");

    if(!glProgram.link())
        KFMTError::error("Couldn't link GLSL Program...");

    glProgWVP = glProgram.uniformLocation("uWVP");
}

void ModelGLView::DrawTMDModel()
{
    //Bind GLSL Program
    glProgram.bind();
    glProgram.setUniformValue(glProgWVP, (glMatProj * glMatView * glMatWorld));

    E->glBindVertexArray(glVAO);
    F->glDrawArrays(GL_TRIANGLES, 0, 3);
}

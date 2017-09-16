#include "glwidget.h"
#include <stdio.h>
#include "SteeringBehaviors/constants.h"
#include "SteeringBehaviors/GameWorld.h"


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    g_GameWorld = new GameWorld(constWindowWidth, constWindowHeight);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(16.667);
    this->setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
    delete timer;
    delete g_GameWorld;
}

void GLWidget::initializeGL()
{
   GLenum glewError = glewInit();
   if( glewError != GLEW_OK )
   {
       printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
       exit(EXIT_FAILURE);
   }

   if( !GLEW_VERSION_3_0 )
   {
       printf( "OpenGL 3.0 not supported!\n" );
       exit(EXIT_FAILURE);
   }

   glViewport( 0.f, 0.f, constWindowWidth, constWindowHeight );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( 0.0, constWindowWidth, constWindowHeight, 0.0, 1.0, -1.0 );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   glClearColor( 1.f, 1.f, 1.f, 1.f );

   GLenum error = glGetError();
   if( error != GL_NO_ERROR )
   {
       printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
       exit(EXIT_FAILURE);
   }

   gdi->SetColor();
}



void GLWidget::resizeGL(int width, int height)
{
    g_GameWorld->cxClientSet(width);
    g_GameWorld->cyClientSet(height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
    glViewport(0.0f, 0.0f, width, height);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    g_GameWorld->Update(0.016667);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_GameWorld->Render();
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    g_GameWorld->HandleKeyPresses(e);
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    g_GameWorld->SetCrosshair(e);
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    g_GameWorld->SetCrosshair(e);
    updateGL();
}

void GLWidget::toggleShowObstacles()
{
    g_GameWorld->toggleShowObstacles();
}

void GLWidget::toggleShowWalls()
{
    g_GameWorld->toggleShowWalls();
}

void GLWidget::switchWeightedSum()
{
    g_GameWorld->switchWeightedSum();
}

void GLWidget::switchPrioritized()
{
    g_GameWorld->switchPrioritized();
}

void GLWidget::switchDithered()
{
    g_GameWorld->switchDithered();
}

void GLWidget::toggleShowKeys()
{
    g_GameWorld->ToggleViewKeys();
}

void GLWidget::toggleShowFPS()
{
    g_GameWorld->ToggleShowFPS();
}

void GLWidget::toggleSmoothing()
{
    g_GameWorld->toggleSmoothing();
}

void GLWidget::changeMaxSteeringForce(int f)
{
    g_GameWorld->changeMaxSteeringForce((double)f);
}

void GLWidget::changeMaxSpeed(int s)
{
    g_GameWorld->changeMaxSpeed((double)s);
}

void GLWidget::changeWanderJitter(int w)
{
    g_GameWorld->changeWanderJitter((double)w);
}

void GLWidget::changeWanderDistance(double d)
{
    g_GameWorld->changeWanderDistance(d);
}

void GLWidget::changeWanderRadius(double d)
{
    g_GameWorld->changeWanderRadius(d);
}

void GLWidget::toggleShowWanderCircle()
{
    g_GameWorld->toggleShowWanderCircle();
}

void GLWidget::toggleShowDetectionBox()
{
    g_GameWorld->toggleShowDetectionBox();
}

void GLWidget::toggleShowFeelers()
{
    g_GameWorld->toggleShowFeelers();
}

void GLWidget::toggleShowSteeringForce()
{
    g_GameWorld->toggleShowSteeringForce();
}

void GLWidget::changeCohesionWeight(double d)
{
    g_GameWorld->changeCohesionWeight(d);
}

void GLWidget::changeAlignmentWeight(double d)
{
    g_GameWorld->changeAlignmentWeight(d);
}

void GLWidget::changeSeparationWeight(double d)
{
    g_GameWorld->changeSeparationWeight(d);
}


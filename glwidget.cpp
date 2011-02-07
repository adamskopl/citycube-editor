#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
#include "object.h"
PreviewWidget::PreviewWidget(globalContainer *globals, QWidget *parent)
    : QGLWidget(parent)
{
    clock = new EClock;
    //we are passing whole floorsTree, because we are previewing every floor
    gameWorld = new LWorld(globals -> floorsTree);
    gameWorld -> stairsTree = globals -> stairsTree;
    gameCamera = gameWorld -> camera;
    loopDone = false;

    clock -> start();

    //cameraKid = new LObject();

    //center of the map (at the beginning)

    //cameraKid = globals -> cameraKid;
    //cameraKid -> position = LVector(500.0f, 0.0f, 500.0f);
    //cameraKid -> direction = -45.0f;

    LObject *camKid = globals -> cameraKid;
    camKid -> direction = 20.0f;

    gameWorld -> camera -> spyMode(camKid);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(10);
    trolltechPurple = QColor::fromCmykF(0.0, 0.0, 0.0, 0.0);

    //floorsTree = globals -> floorsTree;
    //actualFloor = globals -> actualFloor;
    GC = globals;
}

PreviewWidget::~PreviewWidget()
{

}

void PreviewWidget::updateScene()
{
    updateGL();

}

void PreviewWidget::initializeGL()
{
     //glClearColor(0.0, 0.0, 0.0, 0.0);

}

void PreviewWidget::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //prepare camera
    float timePassed = clock -> time();
    gameCamera -> animate((float)timePassed/1000.0f);
    gameWorld -> prepare();
    gameWorld -> draw(gameCamera);
    gameWorld -> animate(timePassed);

}

void PreviewWidget::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    //glViewport(0,0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //REPLACE gluPerspective WITH SOMETHING ELSE
    //no GLU at all
    gluPerspective(54.0f,(GLfloat)w/(GLfloat)h,0.1,1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void PreviewWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::MidButton)
    {
      gameCamera -> reset();
    }
  lastPos = event->pos();
}


void PreviewWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();
  
  if (event->buttons() & Qt::LeftButton) 
    {
      gameCamera -> modRotActB(4 * dx);
      gameCamera -> modRotXB(dy);
    } 
  else 
    if (event->buttons() & Qt::RightButton) 
      {
	gameCamera -> modHeightB(-dy);
      }


  lastPos = event->pos();
}

void PreviewWidget::wheelEvent(QWheelEvent *event)
{
  gameCamera->modDistB((float)(-(event->delta())));
}

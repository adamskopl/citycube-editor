#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "clock.h"
#include "camera.h"
#include "world.h"
#include "lucidbeaver.h"
#include "globalcontainer.h"
class PreviewWidget : public QGLWidget
{
    Q_OBJECT

public:
    PreviewWidget(globalContainer *, QWidget *parent = 0);
    ~PreviewWidget();

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    //    void mousePressEvent(QMouseEvent *event);
    //    void mouseMoveEvent(QMouseEvent *event);

    //from lucidia:
    EClock *clock;
    SDL_Event event;
    Uint32 start;

    bool loopDone;

    LCamera *gameCamera;
    LWorld *gameWorld;

    //LObject *cameraKid;

   public:    

    int fieldsCount;
    void launch();

    QColor trolltechPurple;

    globalContainer *GC;

private slots:
    void updateScene();
};

#endif // GLWIDGET_H

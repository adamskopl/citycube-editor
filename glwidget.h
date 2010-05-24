#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class PreviewWidget : public QGLWidget
{
    Q_OBJECT

public:
    PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();

};

#endif // GLWIDGET_H

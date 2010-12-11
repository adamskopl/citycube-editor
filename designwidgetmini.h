#ifndef DESIGNWIDGETMINI_H
#define DESIGNWIDGETMINI_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPrinter>
#include <QtGui>
#include "globalcontainer.h"

using namespace std;

class DesignWidgetMini : public QWidget
{
public:
    DesignWidgetMini(globalContainer *GC);
 protected:
    void paintEvent(QPaintEvent *event);

 private:
    
    QPainter *painter;
    QPen pen;
    QBrush brush;

    globalContainer *GC;
    float mouseX, mouseY;
    float selectedX, selectedY;
    float gridSize;
    
    void setVariables();
    void drawImages();
    void setDrawStyle(drawStyle style);

    void drawGrid();
    void drawPointer();
    void drawDefinedWindows();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    LField *editedField;
    int wallIndex;
    void drawChosenWall();

    int windowCornerIndex;
    LVector newWindowCorners[2];


    float wallW, wallH, drawnW, drawnH, biggerDimension, scale, topMargin, leftMargin;

 public:
    void beginNewEditing(LField *field, int wall);    
    //    void setEditedField(LField *field, int wallI){editedField = field; wallIndex = wallI;}
};

#endif // DESIGNWIDGETMINI_H

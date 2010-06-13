#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

#include "lucidbeaver.h"
#include "globalcontainer.h"

using namespace std;


enum drawStyle {invisible, field, actualField, stylePointedField, styleChosenField, pointer, connection, wall,
                normal, inactive, floorLine, fieldSide};

//none       - waiting for actions
//defining   - new field is being defined
//connecting - field is chosen and waiting for defining connectin
//enum STATE {none, defining, connecting};

class QTextEdit;
class QComboBOx;
class LField;

  class DesignWidget : public QWidget
  {
      Q_OBJECT
  public:

      //vector with fields is passed with pointer, because its shared betwee
      //this class and PreviewWidget
      DesignWidget(globalContainer *, QTextEdit*, QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *event);

  private:

      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *);
      void mouseReleaseEvent(QMouseEvent *);

      void setVariables();       

      //////////////////////////////////////
      void printInfo(const QString &text);
      void printWarning(const QString &text);
      void printError(const QString &text);
      void printSuccess(const QString &text);
      //////////////////////////////////////
      void drawGrid();
      void drawDefinedFields();
      void drawPointer();
      void drawActualField();

      void drawNewFloorLine();
      void drawFloorsSide();
      void drawFieldSide(LField *);

      void refreshFields();

      ////////////
      void addFloor(float);

      ////////////

      float giveScalar(float x1, float x2, float y1, float y2);

      QTextEdit *reportWidget;

      ///////////////////
      QPainter *painter;
      QPen pen;
      QBrush brush;
      ///////////////////


      void setDrawStyle(drawStyle);
      ///////////////////

      //design widget's size
      float worldSize;
      float gridSize;
      float clickedPos;

      float mouseX, mouseY;

      //which corner is defined now ?
      char cornerIndex;
      //ID of new field
      int fieldID;
      LVector newCorners[4];
      LField definedField;

      float selectedX, selectedY;


      //LObject *worldList;
      //LObject *floorsTree;
      //LField *actualFloor;
      //LObject *cameraKid; //object spied by camera
      //int *floorsAmount;

      globalContainer *GC;


      //is any field pointed right now ?
      bool isFieldPointed;
      LField *pointedField;
      LField *chosenField;

      void removeField(LField *);

      void drawFloor(LBFloor *);
      void drawField(LField *);

      //int pointedFieldID;
      //int chosenFieldID;

  };

#endif // PAINTWIDGET_H

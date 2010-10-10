#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPrinter>
#include "lucidbeaver.h"
#include "globalcontainer.h"

using namespace std;


enum drawStyle {invisible, field, actualField, stylePointedField, styleChosenField, pointer, connection, wall,
                normal, inactive, floorLine, fieldSide, wallInactive, styleChosenWall, styleStairsTriangle, drawStyleGrid};

//none       - waiting for actions
//defining   - new field is being defined
//connecting - field is chosen and waiting for defining connectin
//enum STATE {none, defining, connecting};

class QTextEdit;
class QComboBOx;
class QCheckBox;
class LField;

  class DesignWidget : public QWidget
  {
      Q_OBJECT
  public:

      int scrollX, scrollY;

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
  public:
      //////////////////////////////////////
      void printInfo(const QString &text);
      void printWarning(const QString &text);
      void printError(const QString &text);
      void printSuccess(const QString &text);
      //////////////////////////////////////

  private:
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
  public:
      LField *chosenField;
  private:
      void removeField(LField *);

      void drawFloor(LBFloor *);
      void drawField(LField *);

      QCheckBox *drawBoxes;
      QCheckBox *renderBoxes;

      //int pointedFieldID;
      //int chosenFieldID;

      void drawPig();

      //index of chosen wall (can be changed with 'A' and 'D' keys)
  public:
      char chosenWall;
      void drawStairsTriangles();
      void addNewStairs();

  };

#endif // PAINTWIDGET_H

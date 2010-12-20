#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPrinter>
#include "lucidbeaver.h"
#include "globalcontainer.h"
#include "lbwallhelper.h"
#include "lbmathhelper.h"
#include "lbstairshelper.h"
#include "designwidgetmini.h"

using namespace std;




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
      DesignWidget(globalContainer *, QTextEdit*, DesignWidgetMini *DM, QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *event);

  private:

      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *);
      void mouseReleaseEvent(QMouseEvent *);
      //      void wheelEvent(QWheelEvent *);

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
      void drawDefinedField();

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

      //look out! mouseV has 3d coords - so it's not XY but XZ
      LVector mouseV;
      LVector selectedV;

      //which corner is defined now ?
      char cornerIndex;
      //ID of new field
      int fieldID;
      LVector newCorners[4];
      LField definedField;

      

      //      qreal SCALE;
      //      LVector worldV;

      //LObject *worldList;
      //LObject *floorsTree;
      //LField *actualFloor;
      //LObject *cameraKid; //object spied by camera
      //int *floorsAmount;

      globalContainer *GC;


      //is any field pointed right now ?
      bool isFieldPointed;
      LField *pointedField;

      DesignWidgetMini *designMini;
      
      //      QMatrix globalMatrix;
      //      QMatrix globalMatrix2;
  public:
      //chosen field for defining
      //      LField *chosenField;
      //second field, chosen after choosing first one
      //      LField *chosenField2;

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

      void drawWallParts();
      void drawBreakingHole();

      bool checkTouching();
      bool arePointsCollinear(LVector, LVector, LVector, LVector);

      //class helping in making holes in walls
      LBWallHelper WH;
      lbmathhelper MH;
      lbStairsHelper *SH;

      //points on &WH or SH
      LBHelpersBase *HB;

      //things to reset on clicking with right mouse button
      void resetOnRMB();

  };

#endif // PAINTWIDGET_H

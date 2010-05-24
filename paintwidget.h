#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class QTextEdit;

  class DesignWidget : public QWidget
  {
      Q_OBJECT
  public:
      DesignWidget(QTextEdit*, QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *event);

  private:
      void drawGrid(QPainter *painter);
      void setVariables();       
      void mousePressEvent(QMouseEvent *event);

      QTextEdit *reportWidget;
      QPen pen;
      QBrush brush;

      //design widget's size
      float size;
      float gridSize;
      float clickedPos;


  };

#endif // PAINTWIDGET_H

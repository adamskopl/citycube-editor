#include <QtGui>

#include "paintwidget.h"

DesignWidget::DesignWidget(QTextEdit *reportWidget, QWidget *parent)
    : QWidget(parent)
{
    this->reportWidget = reportWidget;

    resize(QSize(1000,1000));
    setBackgroundRole(QPalette::Base);

    pen = QPen(Qt::green, 1);
    //brush = QBrush(Qt::green);

    setVariables();
}

void DesignWidget::setVariables()
{
    size = 1000.0f;
    gridSize = 10.0f;
}

void DesignWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    drawGrid(&painter);
}

void DesignWidget::drawGrid(QPainter *painter)
{
    for(int cnt = 0; cnt <= size; cnt += gridSize)
    {
        //vertical line
        painter -> drawLine(cnt, 0, cnt, size-1);
        //horizontal line
        painter -> drawLine(0, cnt, size-1, cnt);
    }
}

void DesignWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    reportWidget -> setText("clicked on: ("+QString::number(x)+", "+QString::number(y)+")");
}


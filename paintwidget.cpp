#include <QtGui>

#include "paintwidget.h"

DesignWidget::DesignWidget(QTextEdit *reportWidget, QWidget *parent)
    : QWidget(parent)
{
    this->reportWidget = reportWidget;

    resize(QSize(1000,1000));
    setBackgroundRole(QPalette::Base);

    pen = QPen(Qt::black, 1);
    //brush = QBrush(Qt::green);

    setVariables();
    setMouseTracking(true);
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
    for(int x = 0; x <= size; x += gridSize)
        for(int y = 0; y <= size; y += gridSize)
        {
        if(mouseX - x <= 5 && mouseY - y <=5
           && mouseX - x >= -4 && mouseY -y >= -4)
        {
            painter->drawRect(QRect(x-5, y-5, 10, 10));
        }
            painter->drawPoint(x, y);
        }
}

void DesignWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    reportWidget -> setText("clicked on: ("+QString::number(x)+", "+QString::number(y)+")");
}

void DesignWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseX = event->pos().x();
    mouseY = event->pos().y();

    //update needed on every mouse motion (shape's highliting etc.)
    update();
}

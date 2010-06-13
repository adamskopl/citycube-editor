#include <QtGui>

#include "paintwidget.h"
#include "field.h"
#include <math.h>
#include <stdio.h>


void DesignWidget::printInfo(const QString &text)
{
    reportWidget -> setTextColor(Qt::darkBlue);
    reportWidget -> append(text);
}

void DesignWidget::printWarning(const QString &text)
{
    reportWidget -> setTextColor(Qt::darkYellow);
    reportWidget -> append(text);
}

void DesignWidget::printError(const QString &text)
{
    reportWidget -> setTextColor(Qt::darkRed);
    reportWidget -> append(text);
}

void DesignWidget::printSuccess(const QString &text)
{
    reportWidget -> setTextColor(Qt::darkGreen);
    reportWidget -> append(text);
}

DesignWidget::DesignWidget(globalContainer *globals, QTextEdit *reportWidget, QWidget *parent)
    : QWidget(parent)
{
    this->reportWidget = reportWidget;

    resize(QSize(1000,1000));
    setBackgroundRole(QPalette::Dark);
    //setForegroundRole(QPalette::Highlight);

    pen = QPen(Qt::black, 1);
    brush = QBrush(Qt::green);

    reportWidget -> setReadOnly(true);

   // painter = new QPainter(this);
    setVariables();
    setMouseTracking(true);

    //fields = globalFields;
    cameraKid = globals -> cameraKid;
    floorsTree = globals -> floorsTree;
    actualFloor = globals -> actualFloor;

    appState = globals -> appState;
    floorsComboBox = globals -> floorsComboBox;
    floorsAmount = globals -> floorsAmount;
    GC = globals;
}

void DesignWidget::setVariables()
{
    worldSize = 1000.0f;
    gridSize = 10.0f;
    cornerIndex = 0;
    fieldID = 0;
    isFieldPointed = false;
    //pointedFieldID = -1; //no field pointed

    pointedField = NULL;
    chosenField = NULL;
    //appState = none;

}

void DesignWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    drawGrid();

    switch(*appState)
    {
    case(addingFloor):
        {
            drawNewFloorLine();
            drawFloorsSide();

            break;
        }
    default:
        {
            drawDefinedFields();
            drawActualField();
            drawPointer();
            break;
        }
    }
    delete painter;
}

void DesignWidget::drawGrid()
{

    int crossX, crossY;

    for(int x = 0; x <= worldSize; x += gridSize)
        for(int y = 0; y <= worldSize; y += gridSize)
        {
        if(mouseX - x <= 5 && mouseY - y <=5
           && mouseX - x >= -4 && mouseY -y >= -4)
        {
            crossX = x; crossY = y;
        }else
            painter->drawPoint(x, y);
        }

    selectedX = crossX;
    selectedY = crossY;
}

void DesignWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
//    reportWidget -> setText("clicked on: ("+QString::number(x)+", "+QString::number(y)+")");

    switch(event->button())
    {
    //left button
    case(1):
        {
            switch(*appState){

            case(none):
                {
                    if(isFieldPointed)
                    {
                        //chosenFieldID = pointedFieldID;
                        chosenField = pointedField;
                        *appState = connecting;
                        printInfo("choose connection ...");
                    }
                    else
                    {
                        //the beggining of defining
                        *appState = defining;
                        cornerIndex++;
                        newCorners[0].x = selectedX;
                        newCorners[0].z = selectedY;
                    }
                    break;
                }

            case(defining):
                {
                    switch(cornerIndex)
                    {
                        //case(0) is done in 'none' case
                    case(1):
                        {
                            cornerIndex++;
                            newCorners[1].x = selectedX;
                            newCorners[1].z = selectedY;
                            break;
                        }
                    case(2):
                        {
                            cornerIndex++;
                            newCorners[2].x = selectedX;
                            newCorners[2].z = selectedY;
                            break;
                        }
                    case(3):
                        {
                            cornerIndex = 0;
                            newCorners[3].x = selectedX;
                            newCorners[3].z = selectedY;

                            //set HEIGHT
                            newCorners[0].y = GC -> actualFloor -> height;
                            newCorners[1].y = GC -> actualFloor -> height;
                            newCorners[2].y = GC -> actualFloor -> height;
                            newCorners[3].y = GC -> actualFloor -> height;


                            LField *temp = new LField(WWWW, newCorners);
                            //temp -> ID = fields->size();
                            //fieldID++;
                            //!fields->push_back(*temp);

                            GC -> actualFloor -> connect(temp);

                            printSuccess("new field added");
                            GC -> cameraKid -> position = temp-> centerPoint;
                            GC -> cameraKid -> position.y = GC -> actualFloor -> height;

                            *appState = none;
                            //world -> checkConnections();
                            break;
                        }
                    }//switch(cornerIndex)
                    break;
                }//case(none)

            case(connecting):
                {
                    if(isFieldPointed)
                    {
                        if(pointedField->connectTo(chosenField))
                            printSuccess("... connection defined");
                        else
                            printError("... wrong field chosen");

                        //chosenFieldID = -1;
                        chosenField = NULL;
                        *appState = none;
                    }
                    break;
                }
            case(addingFloor):
                {
                    addFloor(selectedY);
                    *appState = none;
                }

            }//switch(state)

            break;
        }//case(1) - button
    //right button
    case(2):
        {
            switch(*appState){

            case(defining):
                {
                    cornerIndex = 0;
                    *appState = none;
                    break;
                }           

            case(connecting):
                {
                    *appState = none;
                    chosenField = NULL;
                    break;
                }
            case(none):
                {
                    if(isFieldPointed)
                    {
                        //pointedField->disconnect();
                        //fields->
                        //refreshFields();
                        removeField(pointedField);

                    }
                    break;
                }
            case(addingFloor):
                {    
                    *appState = none;
                    break;
                }

            }
            break;
        }
    case(Qt::MidButton):
        {

            break;
        }


    }
}

void DesignWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case(Qt::MidButton):
        {

            break;
        }

    }

}

void DesignWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseX = event->pos().x();
    mouseY = event->pos().y();


    //update needed on every mouse motion (shape's highliting etc.)
    update();
}

void DesignWidget::drawDefinedFields()
{

    setDrawStyle(field);
    isFieldPointed = false;
    //pointedFieldID = -1.0f;

    LField *helpField;
    if(GC->actualFloor->hasChild())
        helpField = (LField*)GC->actualFloor -> child;
    else
        return;


    if(GC->actualFloor->draw == false)
        return;

    while(1)
    {
        //check if field is pointed with mouse
        if(helpField->isPointIn(LVector(mouseX, 0.0f, mouseY)))
        {
            isFieldPointed = true;
            cameraKid -> position = helpField->centerPoint;
            cameraKid -> position.y = GC -> actualFloor -> height;
            //if new field is not defined right now
            if(!cornerIndex)
            {
                //pointedFieldID = helpField->ID;
                pointedField = helpField;
                setDrawStyle(stylePointedField);
            }
            else
            {
                if(*appState == connecting)
                    setDrawStyle(inactive);
                else
                    setDrawStyle(field);
            }
        }
        else
        {
            if(*appState == connecting)
                setDrawStyle(inactive);
            else
                setDrawStyle(field);
        }

        if(helpField == chosenField)
            setDrawStyle(styleChosenField);

        QPolygon drawField;

        drawField << QPoint(helpField->corners[0].x, helpField->corners[0].z)
                << QPoint(helpField->corners[1].x,helpField->corners[1].z)
                << QPoint(helpField->corners[2].x,helpField->corners[2].z)
                << QPoint(helpField->corners[3].x,helpField->corners[3].z);

        painter->drawPolygon(drawField);

        //draw Normals
        setDrawStyle(normal);
        for(int cntN = 0; cntN < 4; cntN++)
        {
            int x1 = helpField->corners[cntN].x + helpField->vectors[cntN].x/2;
            int z1 = helpField->corners[cntN].z + helpField->vectors[cntN].z/2;
            int x2 = x1 + helpField->cornersN[cntN].x*10.0f;
            int z2 = z1 + helpField->cornersN[cntN].z*10.0f;

            painter -> drawLine(x1, z1, x2, z2);
        }
        /////////////////////////////////////////
        //draw connections or walls (loop would be better. so so so.)
        if(helpField->connections[0])
            setDrawStyle(connection);
        else
            setDrawStyle(wall);
        painter -> drawLine(helpField->corners[0].x, helpField->corners[0].z,
                            helpField->corners[1].x, helpField->corners[1].z);

        if(helpField->connections[1])
            setDrawStyle(connection);
        else
            setDrawStyle(wall);
        painter -> drawLine(helpField->corners[1].x, helpField->corners[1].z,
                            helpField->corners[2].x, helpField->corners[2].z);

        if(helpField->connections[2])
            setDrawStyle(connection);
        else
            setDrawStyle(wall);
        painter -> drawLine(helpField->corners[2].x, helpField->corners[2].z,
                            helpField->corners[3].x, helpField->corners[3].z);

        if(helpField->connections[3])
            setDrawStyle(connection);
        else
            setDrawStyle(wall);
        painter -> drawLine(helpField->corners[3].x, helpField->corners[3].z,
                            helpField->corners[0].x, helpField->corners[0].z);


        if(helpField -> isLast())
            break;
        else
            helpField = (LField*)helpField -> next;
    }



}


void DesignWidget::drawPointer()
{
    if(isFieldPointed)
        return;
    setDrawStyle(pointer);
    painter->drawRect(QRect(selectedX-5, selectedY-5, 10, 10));
}

void DesignWidget::drawActualField()
{

    setDrawStyle(actualField);

    switch(cornerIndex)
    {
    case(1):
        {

            painter->drawLine(newCorners[0].x, newCorners[0].z, selectedX, selectedY);
            break;
        }

    case(2):
        {
            painter->drawLine(newCorners[0].x, newCorners[0].z, newCorners[1].x, newCorners[1].z);
            painter->drawLine(newCorners[1].x, newCorners[1].z, selectedX, selectedY);
            break;
        }

    case(3):
        {            
            painter->drawLine(newCorners[0].x, newCorners[0].z, newCorners[1].x, newCorners[1].z);
            painter->drawLine(newCorners[1].x, newCorners[1].z, newCorners[2].x, newCorners[2].z);
            painter->drawLine(newCorners[2].x, newCorners[2].z, selectedX, selectedY);
            painter->drawLine(newCorners[0].x, newCorners[0].z, selectedX, selectedY);
            break;
        }
    }
}

void DesignWidget::setDrawStyle(drawStyle style)
{
    switch(style)
    {
    //none
    case(invisible):
        {
            pen.setColor(Qt::transparent);
            brush.setColor(Qt::transparent);
            break;
        }

    //field
    case(field):
        {
            brush.setColor(QColor(160, 170, 180));
            pen.setColor(Qt::transparent);
            pen.setStyle(Qt::SolidLine);
            break;
        }
    //actual field
    case(actualField):
        {
            pen.setStyle(Qt::DotLine);
            pen.setColor(Qt::red);
            pen.setWidth(2);
            break;
        }
    //selected field
    case(stylePointedField):
        {
            brush.setColor(Qt::darkGreen);
            pen.setColor(Qt::transparent);
            pen.setWidth(1);
            break;
        }
    //pointer
    case(pointer):
        {
            brush.setColor(Qt::yellow);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            break;
        }
    case(connection):
        {
//            brush.setColor(Qt::cyan);
            pen.setColor(Qt::yellow);
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(1);
            break;
        }
    case(wall):
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            break;
        }

    case(normal):
        {
            pen.setColor(Qt::magenta);
            pen.setWidth(1);
            break;
        }
    case(inactive):
        {
            brush.setColor(Qt::darkGray);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            break;
        }
    case(styleChosenField):
        {
            brush.setColor(Qt::darkRed);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            break;
        }
    case(floorLine):
        {
            pen.setColor(Qt::green);
            pen.setStyle(Qt::DashDotDotLine);
            pen.setWidth(1);
            break;
        }
    case(fieldSide):
        {
            pen.setColor(Qt::yellow);
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(3);

            break;
        }
    }

    painter->setBrush(brush);
    painter->setPen(pen);
}

//for now on it's refreshing only indexes
//LAUNCH WHEN ANY FIELD IS REMOVED
void DesignWidget::refreshFields()
{

    //refresh ID's - in case of removing fields
    //for(int cnt = 0; cnt < fields->size(); cnt++)
    //{
//        fields->at(cnt).ID = cnt;
    //}
}

void DesignWidget::removeField(LField *rem)
{
    rem -> remove();
    delete rem;
    printInfo("field removed");

}

void DesignWidget::drawNewFloorLine()
{
    setDrawStyle(floorLine);
    painter -> drawLine(0, selectedY, 1000 , selectedY);

}

void DesignWidget::drawFloorsSide()
{
    //WARNING - overwrites actualFloor pointer!
    LObject *actualFloor;

    //for every floor draw its fields
    if(floorsTree -> hasChild())
        actualFloor = ((LField*)(floorsTree -> child));

    //break this while(), when last floor is drawn
    while(1)
    {
        LField * drawnField;
        //draw floor's fields

        if(actualFloor -> hasChild())
        {
            drawnField = ((LField*)(actualFloor -> child));

            //break this while(), when last field is drawn
            while(1)
            {
                drawFieldSide(drawnField);
                if(drawnField -> isLast())
                    break;
                drawnField = (LField*)drawnField -> next;
            }
        }
        if(actualFloor -> isLast())
            break;
        actualFloor = (LField*)actualFloor -> next;
    }

}

void DesignWidget::drawFieldSide(LField *drawnField)
{
    setDrawStyle(fieldSide);

    for(int cnt = 0; cnt < 4; cnt++)
    {    
        int a1 = cnt;
        int a2;
        if(cnt == 3)
            a2 = 0;
        else
            a2 = a1+1;

        //0 height is in the center - so the negative values could be lower and positive higher
        int yPos = worldSize - drawnField -> corners[a1].y;

        painter -> drawLine(drawnField->corners[a1].x, yPos,
                    drawnField->corners[a2].x, yPos);

    }
}

void DesignWidget::addFloor(float height)
{
    LField *help = new LField;
    help -> height = worldSize - height;

    ((LObject*)help) -> connectTo(floorsTree);

    QString *floorName = new QString("floor" + QString::number(*floorsAmount));
    floorsComboBox -> addItem(tr(floorName->toAscii()));
    (*floorsAmount)++;
}


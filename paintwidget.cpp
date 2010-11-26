#include <QtGui>

#include "paintwidget.h"
#include "field.h"
#include "lbstairs.h"
#include <math.h>

#include <stdio.h>
#include <iostream>
//TODO: class is too big. add other classes helping DesignWidget
//TODO: every object that was created with NEW, has to be deleted on end

//delete this, when cout will not be needed
using namespace std;

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

    //set
    //setForegroundRole(QPalette::Dark);

    pen = QPen(Qt::black, 1);
    brush = QBrush(Qt::red);

    reportWidget -> setReadOnly(true);

    // painter = new QPainter(this);
    setVariables();
    setMouseTracking(true);

    GC = globals;
    //drawBoxes = GC

    scrollX = 0;
    scrollY = 0;

    chosenWall = 0;
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

    //    QPainter painter(this);

    switch(*(GC -> appState))
    {
    case(addingFloor):
        {
	  drawNewFloorLine();
	  drawFloorsSide();

	  break;
        }
    case(connectingFields):
      {
	drawDefinedFields();
	drawWallParts();
	break;
      }
    case(breakingHole):
      {
	drawDefinedFields();
	drawBreakingHole();
	break;
      }
    default:
        {
	    drawStairsTriangles();
	    drawDefinedFields();
            drawDefinedField();
            drawPointer();
            break;
        }
    }

    setDrawStyle(drawStyleBigPoint);
    //    painter->drawPoint(WH.passageA.x, WH.passageA.z);
    //    painter->drawPoint(WH.passageB.x, WH.passageB.z);    

    drawPig();
    delete painter;
}

void DesignWidget::drawGrid()
{
    setDrawStyle(drawStyleGrid);
    painter->fillRect(0, 0, worldSize, worldSize, brush);

    int crossX = 0, crossY = 0;

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
  //    int x = event->pos().x();
  //    int y = event->pos().y();
    //    reportWidget -> setText("clicked on: ("+QString::number(x)+", "+QString::number(y)+")");

    switch(event->button())
    {
        //left button
    case(1):
        {
            switch(*(GC -> appState)){

            case(none):
                {
                    if(isFieldPointed)
                    {
                        //chosenFieldID = pointedFieldID;
                        chosenField = pointedField;
                        *(GC->appState) = editingField;
                        printInfo("choose other field ...");
                    }
                    else
                    {
                        //the beggining of defining
                        *(GC -> appState) = defining;
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

                            *(GC -> appState) = none;
                            //world -> checkConnections();
                            break;
                        }
                    }//switch(cornerIndex)
                    break;
                }//case(none)
            case(definingStairs):
                {
                    //if no field for stairs is chosen    
                    if(isFieldPointed)
                    {
                        //if bottom field is not chosen
                        if(GC -> stairsBottom == NULL)
                        {
                            printInfo("... select border from which stairs will begin (hit 'W', when you're done') ...");
                            GC -> stairsBottom = pointedField;
                        }
                        else
                        {
                            //if top field is not chosen
                            if(GC -> stairsTop == NULL)
                            {
                                printInfo("... select border where stairs will end (hit 'W', when you're done') ...");
                                GC -> stairsTop = pointedField;
                            }
                        }
                    }
                    break;
                }
            case(editingField):
                {
                    if(isFieldPointed)
                    {
		      /*if(pointedField->connectTo(chosenField))
                            printSuccess("... connection defined");
                        else
                            printError("... wrong field chosen");
		      */
                        //chosenFieldID = -1;
                        chosenField2 = pointedField;
			if( checkTouching() )
			  {
			    printSuccess("YES!");
			    //			    *(GC -> appState) = connectingFields;
			    //			    chosenField2 = pointedField;
			    *(GC -> appState) = connectingFields;
			    //chosenField = NULL;
			    //chosenField2 = NULL;
			  }
			else
			  {
			    printError("NO !");
			    *(GC -> appState) = none;
			    chosenField = NULL;
			    chosenField2 = NULL;
			  }

                    }
                    break;
                }
            case(addingFloor):
                {
                    addFloor(selectedY);
                    *(GC -> appState) = none;
		    break;
                }
	    case(connectingFields):
	      {
		if(WH.isPartPointed())
		  *(GC -> appState) = breakingHole;
		break;
	      }
	    case(breakingHole):
	      {
		//for future: it is best to try build functions, that would work for every number of variables. e.g: we have dist1, dist2 ... dist30.

		//check on what pointer is pointing, and point on next variable
		if(WH.distPointer == &WH.dist1)
		  {
		    WH.distPointer = &WH.dist2;
		    WH.pointPointer = &WH.point2;
		  }
		else
		  if(WH.distPointer == &WH.dist2)
		    {
		      //create new field's passage
		      WH.addPassage(chosenField, chosenField2);
		      chosenField = NULL;
		      chosenField2 = NULL;
		      *GC->appState = none;
		    }
		  else
		    {
		      printError("distPointer is pointint on unknown! (case(breakingHole))");
		    }
		break;
	      }
	    default:
	      {
		printWarning("program warning: new appstate without definition");
	      }
            }//switch(state)

            break;
        }//case(1) - button
        //right button
    case(2):
        {
            switch(*(GC-> appState)){

            case(defining):
                {
                    cornerIndex = 0;
                    *(GC -> appState) = none;
                    break;
                }           

            case(editingField):
                {
                    *(GC -> appState) = none;
                    chosenField = NULL;
                    chosenWall = 0;
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
                    else // change floor
                    {
                        GC -> actualFloor = (LBFloor*)(GC -> actualFloor -> next);

                    }
                    break;
                }
            case(addingFloor):
                {    
                    *(GC -> appState) = none;
                    break;
                }
            case(definingStairs):
                {
                    GC -> stairsBottom = NULL;
                    GC -> stairsTop = NULL;
                    GC -> stairsFieldBottomEdge = 0;
                    GC -> stairsFieldTopEdge = 0;
                    GC -> isBottomFieldSet = false;

                    *(GC -> appState) = none;
                    printInfo("... cancelled.");
                    break;
                }
	    case(connectingFields):
	      {
		resetOnRMB();
		break;
	      }
	    case(breakingHole):
	      {
		resetOnRMB();
	      }
	    default:
	      {
		printWarning("program warning: new appstate without definition");
	      }
            }
            break;
        }
    case(Qt::MidButton):
        {

            break;
        }
    default:
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
    default:
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

//draw all fields on each floor. Pass floors, that has
void DesignWidget::drawDefinedFields()
{
  setDrawStyle(drawStyleField);
  isFieldPointed = false;

    LBFloor *helpFloor;

    if(GC->floorsTree->hasChild())
        helpFloor = (LBFloor*) GC-> floorsTree -> child;
    else
        return;


    //break this while when last floor is drawn
    while(1)
    {
      //first draw every floor except actual one
        if(helpFloor != GC -> actualFloor)
            drawFloor(helpFloor);

        if(! helpFloor -> isLast())
            helpFloor = (LBFloor*)(helpFloor -> next);
        else
            break;
    }

    //draw actual first in the end - so it covers others
    drawFloor(GC -> actualFloor);

    //drawChosenWall
    if(*(GC -> appState) == editingField)
    {
        setDrawStyle(drawStyleChosenWall);

        int a, b;
        a = chosenWall;
        if(chosenWall == 3)
            b = 0;
        else
            b = chosenWall+1;
        painter -> drawLine(chosenField -> corners[a].x, chosenField -> corners[a].z,
                            chosenField -> corners[b].x, chosenField -> corners[b].z);
    }

}


void DesignWidget::drawPointer()
{
    if(isFieldPointed)
        return;
    setDrawStyle(pointer);
    painter->drawRect(QRect(selectedX-5, selectedY-5, 10, 10));
}

void DesignWidget::drawDefinedField()
{

    setDrawStyle(drawStyleDefinedField);

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
    //TODO: dodać wszędzie prefiks "drawStyle"
    switch(style)
    {        
        //when drawing grid
    case(drawStyleGrid):
        {
	  //            pen.setColor(Qt::white);
	  pen.setColor("#8d8d8d");
	    //            brush.setColor(QColor(58,107,200));//blue
	    //brush.setColor(QColor(71,145,0));
	    brush.setColor("#393939");
	    pen.setWidth(1);
            break;
        }

        //none
    case(invisible):
        {
            pen.setColor(Qt::transparent);
            brush.setColor(Qt::transparent);
            break;
        }

        //field
    case(drawStyleField):
        {
	  //	  brush.setColor(QColor(160, 170, 180));
	  //	  pen.setStyle(Qt::SolidLine);
	  pen.setWidth(1);
	  pen.setColor(Qt::black);
	  brush.setColor(Qt::transparent);
            break;
        }
        //actual field
    case(drawStyleDefinedField):
        {
	  pen.setStyle(Qt::DotLine);
	  pen.setColor("#ff8c19");
	  pen.setWidth(1);
	  break;
        }
        //selected field
    case(stylePointedField):
        {
	  //	  brush.setColor(Qt::darkGreen);
	  brush.setColor("#8a5722");
	    pen.setColor(Qt::transparent);
	    pen.setStyle(Qt::SolidLine);
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
    case(drawStyleWall):
        {
            pen.setStyle(Qt::SolidLine);
	    pen.setColor("#ffa000");
	    brush.setColor(Qt::transparent);
	    //            pen.setColor(Qt::white);
	    //  pen.setColor(Qt::black);
            pen.setWidth(1);
            break;
        }

    case(wallInactive):
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::lightGray);
            pen.setWidth(1);
            break;
        }

        //normal vector (this is how it is in english?)
    case(normal):
        {
	  pen.setStyle(Qt::SolidLine);
	  //	  pen.setColor(Qt::magenta);
	  pen.setColor("#22dddd");
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
	  //	  brush.setColor(Qt::darkRed);
	  brush.setColor("#8a5722");
	  pen.setColor(Qt::black);
	  pen.setStyle(Qt::SolidLine);
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
    case(drawStyleChosenWall):
        {
            pen.setColor(Qt::yellow);
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(3);
            break;
        }
    case(styleStairsTriangle):
      {
	pen.setColor(Qt::black);
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	brush.setColor(Qt::darkYellow);
	break;
      }

    case(drawStyleBigPoint):
      {
	pen.setColor(Qt::red);
	pen.setWidth(3);
	brush.setColor(Qt::red);
	break;
      }
    case(drawStyleHighlightParts):
      {
	pen.setColor(Qt::yellow);
	//	pen.setColor("#00c1ff");
	pen.setWidth(2);

	break;
      }
    case(drawStyleWallChoose):
      {
	pen.setStyle(Qt::DashDotDotLine);
	pen.setColor(Qt::yellow);

	pen.setWidth(1);

	break;
      }
    }

    painter-> setBrush(brush);
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
  
    LObject *actualFloor = NULL;

    //for every floor draw its fields
    if(GC -> floorsTree -> hasChild())
        actualFloor = ((LField*)(GC -> floorsTree -> child));
    else
      {
	printError("actualFloor not set!");
	return;
      }

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
    //actualize checkboxes
    GC -> drawBoxes[*(GC -> floorsAmount)].setDisabled(false);
    GC -> drawBoxes[*(GC -> floorsAmount)].setChecked(true);
    GC -> renderBoxes[*(GC -> floorsAmount)].setDisabled(false);
    GC -> renderBoxes[*(GC -> floorsAmount)].setChecked(true);

    LBFloor *help = new LBFloor(worldSize - height);

    ((LObject*)help) -> connectTo(GC -> floorsTree);

    QString *floorName = new QString("floor" + QString::number(*(GC -> floorsAmount)));
    GC -> floorsComboBox -> addItem(tr(floorName->toAscii()));
    (*(GC -> floorsAmount))++;

}


void DesignWidget::drawFloor(LBFloor *drawnFloor)
{
    if( !(drawnFloor -> isItDrawn) )
        return;

    LField *helpField;
    if(drawnFloor -> hasChild())
        helpField = (LField*)drawnFloor -> child;
    else
        return;



    //break this while, when last field of actual floor is drawn
    while(1)
    {
      //Okay, little mess. We have new state: connectingFields
      //this complicates following code (before drawing floors other than actual one)
      //if another state will appear, rebuild of following "if" will be needed


      //for now: check if field is pointed only if ...
      if(*(GC -> appState) == none || *(GC -> appState) == editingField)
	if(drawnFloor == GC -> actualFloor)
	  {
            //check if field is pointed with mouse
            if(helpField->isPointIn(LVector(mouseX, 0.0f, mouseY)))
            {
                isFieldPointed = true;
                GC -> cameraKid -> position = helpField->centerPoint;
                GC -> cameraKid -> position.y = GC -> actualFloor -> height;

                //if new field is not being defined right now
                if(!cornerIndex)
                {
                    //pointedFieldID = helpField->ID;
                    pointedField = helpField;
		    setDrawStyle(stylePointedField);
                }
	    }
            else
	      {
		if(*(GC -> appState) == editingField)
		  setDrawStyle(inactive);
		else
		setDrawStyle(drawStyleField);
	      }

            if(helpField == chosenField)
	      setDrawStyle(styleChosenField);
	    
            QPolygon drawField;

	    drawField << QPoint(helpField->corners[0].x, helpField->corners[0].z)
		      << QPoint(helpField->corners[1].x,helpField->corners[1].z)
		      << QPoint(helpField->corners[2].x,helpField->corners[2].z)
		      << QPoint(helpField->corners[3].x,helpField->corners[3].z);

	    painter->drawPolygon(drawField);
	  }//(if drawnFloor == GC -> actualFloor)

      //draw parts of "connectingFields" state
      if(*(GC -> appState) == connectingFields)
	{
	  
	}


        /////////////////////////////////////////////
        //PART FOR EVERY FLOOR (not only actual) :
        /////////////////////////////////////////////

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
        //draw walls with defined passages
	if(drawnFloor == GC -> actualFloor)
	  setDrawStyle(drawStyleWall);
	else
	  setDrawStyle(wallInactive);

        for(int cnt = 0; cnt < 4; cnt++)
        {
            int a, b;
            a = cnt;
            if(cnt == 3)
                b = 0;
            else
                b = a + 1;

	    LVector wallVector = helpField -> corners[b] - helpField -> corners[a];
	    float wallLength = wallVector.Length();

	    //points for drawing lines defining wall parts
	    LVector pointA, pointB;

	    pointA = helpField -> corners[a];

	    if(helpField -> passageTree[a] -> hasChild())
	      {
		lbpassage *helpPassage = (lbpassage*)(helpField -> passageTree[a] -> child);
		while(1)
		  {
		    //multiply wall's vector by ratio of passage's point distance and Wall's length
		    pointB = helpField -> corners[a] + wallVector * (helpPassage -> d1 / wallLength);
		    painter -> drawLine(pointA.x, pointA.z, pointB.x, pointB.z);
		    pointA = helpField -> corners[a] + wallVector * (helpPassage -> d2 / wallLength);

		    if( ! helpPassage -> isLast())
		      {
			helpPassage = (lbpassage*)(helpPassage -> next);
		      }
		    //last passage
		    else
		      {
			break;
		      }
		  }
	      }

	    //draw last wall part (draw whole wall if we don't have passages yet)
	    pointB = helpField -> corners[b];
	    painter -> drawLine(pointA.x, pointA.z, pointB.x, pointB.z);

	}

        /////////////////////////////
        if(helpField -> isLast())
            break;
        else
            helpField = (LField*)helpField -> next;
        /////////////////////////////
    }

}

void DesignWidget::drawPig()
{
    QRectF target(scrollX + 490, scrollY + 490, 80.0, 80.0);
    QRectF source(0.0, 0.0, 80.0, 80.0);

    switch(*(GC -> appState))
    {
    case(defining):
        {
            QImage image("pigNewField.png");
            painter -> drawImage(target, image, source);
            break;
        }
    case(editingField):
        {
            QImage image("pigField.png");
            painter -> drawImage(target, image, source);
            break;
        }
    case(addingFloor):
        {
            QImage image("pigNewFloor.png");
            painter -> drawImage(target, image, source);
            break;
        }
    case(definingStairs):
        {
            QImage image("pigStairs.png");
            painter -> drawImage(target, image, source);
            break;
        }

    default:
        {
            QImage image("pigRuler.png");
            painter -> drawImage(target, image, source);
            break;
        }
    }
}

void DesignWidget::drawStairsTriangles()
{
    if(*(GC -> appState) == definingStairs)
    {
        //if bottom field is chosen
        if(GC -> stairsBottom)
        {
            //draw triangle symbolizing stairs beginning
            QPolygon drawnTriangle;


            int a = GC -> stairsFieldBottomEdge;
            int b;
            if( a == 3)
                b = 0;
            else
                b = a + 1;

            LVector normalPoint;
            normalPoint.x = GC -> stairsBottom -> corners[a].x +
                            GC -> stairsBottom -> vectors[a].x/2 +
                            GC -> stairsBottom -> cornersN[a].x * (-20.0f);

            normalPoint.z = GC -> stairsBottom -> corners[a].z +
                            GC -> stairsBottom -> vectors[a].z/2 +
                            GC -> stairsBottom -> cornersN[a].z * (-20.0f);

            drawnTriangle << QPoint(GC -> stairsBottom -> corners[a].x, GC -> stairsBottom -> corners[a].z)
                    << QPoint(normalPoint.x, normalPoint.z)
                    << QPoint(GC -> stairsBottom -> corners[b].x, GC -> stairsBottom -> corners[b].z);

            setDrawStyle(styleStairsTriangle);
            painter -> drawPolygon(drawnTriangle);

        }
        if(GC -> stairsTop)
        {
            //draw triangle symbolizing stairs beginning
            QPolygon drawnTriangle;


            int a = GC -> stairsFieldTopEdge;
            int b;
            if( a == 3)
                b = 0;
            else
                b = a + 1;

            LVector normalPoint;
            normalPoint.x = GC -> stairsTop -> corners[a].x +
                            GC -> stairsTop -> vectors[a].x/2 +
                            GC -> stairsTop -> cornersN[a].x * (-20.0f);

            normalPoint.z = GC -> stairsTop -> corners[a].z +
                            GC -> stairsTop -> vectors[a].z/2 +
                            GC -> stairsTop -> cornersN[a].z * (-20.0f);

            drawnTriangle << QPoint(GC -> stairsTop -> corners[a].x, GC -> stairsTop -> corners[a].z)
                    << QPoint(normalPoint.x, normalPoint.z)
                    << QPoint(GC -> stairsTop -> corners[b].x, GC -> stairsTop -> corners[b].z);

            setDrawStyle(styleStairsTriangle);
            painter -> drawPolygon(drawnTriangle);
        }
    }
}

void DesignWidget::addNewStairs()
{
    LBStairs *newStairs = new LBStairs;

    newStairs -> connBottom = GC -> stairsBottom;
    newStairs -> connTop = GC -> stairsTop;

    int a, b;
    a = GC -> stairsFieldBottomEdge;
    if(a == 3)
        b = 0;
    else
        b = a + 1;

    newStairs -> cornersBottom[0] = GC -> stairsBottom -> corners[a];
    newStairs -> cornersBottom[1] = GC -> stairsBottom -> corners[b];

    a = GC -> stairsFieldTopEdge;
    if(a == 3)
        b = 0;
    else
        b = a + 1;

    newStairs -> cornersTop[0] = GC -> stairsTop -> corners[a];
    newStairs -> cornersTop[1] = GC -> stairsTop -> corners[b];
    newStairs -> horizontalVector = GC -> stairsHorizontalVector;

    newStairs -> connectTo(GC -> stairsTree);
}


//check if chosenField is touching chosenField2 (they have to be set)
//in such way, that passage can be made. if so - set passageA & WH.passageB
bool
DesignWidget::checkTouching()
{
  //for every pair of edges from different sectors (using counting variables to set wallsIndex1 and wallIndex2
  for(int a = 0; a < 4; a++)
    {
      for(int b = 0; b < 4; b++)
	{
	  //considered corners
	  LVector cX[4];

	  if(a == 3) cX[1] = chosenField -> corners[0];
	  else
	    cX[1] = chosenField -> corners[a+1];
	  
	  if(b == 3) cX[3] = chosenField2 -> corners[0];
	  else
	    cX[3] = chosenField2 -> corners[b+1];
	  
	  cX[0] = chosenField -> corners[a];
	  cX[2] = chosenField2 -> corners[b];


          if((cX[0].x - cX[1].x)*(cX[2].z - cX[3].z) == 
	     (cX[2].x - cX[3].x)*(cX[0].z - cX[1].z))//initial condition: collinearity of two edges (but it's not sufficient)
	    {
	      //count how many points of one edge belongs to second edge and vice-versa
	      //2:0 - ok, 2:1 - ok, 2:2 - ok, 1:1 - ok if points are not equal

	      bool isIn[4];
	      //e.g isA: establish if cX[0] and cX[2] and cX[3] are collinear. if so, check if
	      // cX[0].x is betweeen cX[2].x and cX[3].x and cA.z between cX[2].z and cX[3].z

	      //A & B belongs to CD?
	      for(int cnt = 0; cnt < 2; cnt++)
		{
		  bool isXok, isZok;

		  //check which .x coor is first
		  if(cX[2].x < cX[3].x)
		    {isXok = (cX[cnt].x >= cX[2].x && cX[cnt].x <= cX[3].x);}
		  else
		    {isXok = (cX[cnt].x <= cX[2].x && cX[cnt].x >= cX[3].x);}

		  if(cX[2].z < cX[3].z)
		    {isZok = (cX[cnt].z >= cX[2].z && cX[cnt].z <= cX[3].z);}
		  else
		    {isZok = (cX[cnt].z <= cX[2].z && cX[cnt].z >= cX[3].z);}

		  isIn[cnt] = isXok && isZok;
		}

	      //C & D  belongs to AB?
	      for(int cnt = 2; cnt < 4; cnt++)
		{
		  bool isXok, isZok;

		  //check which .x coor is first
		  if(cX[0].x < cX[1].x)
		    {isXok = (cX[cnt].x >= cX[0].x && cX[cnt].x <= cX[1].x);}
		  else
		    {isXok = (cX[cnt].x <= cX[0].x && cX[cnt].x >= cX[1].x);}

		  if(cX[0].z < cX[1].z)
		    {isZok = (cX[cnt].z >= cX[0].z && cX[cnt].z <= cX[1].z);}
		  else
		    {isZok = (cX[cnt].z <= cX[0].z && cX[cnt].z >= cX[1].z);}

		  isIn[cnt] = isXok && isZok;
		}
	      /*
	      reportWidget -> 
		setText(
			QString::number(cX[0].x)+" "+QString::number(cX[0].z)+"\n"+
			QString::number(cX[1].x)+" "+QString::number(cX[1].z)+"\n"+
			QString::number(cX[2].x)+" "+QString::number(cX[2].z)+"\n"+
			QString::number(cX[3].x)+" "+QString::number(cX[3].z)+"\n"+

				      QString::number(isIn[0])+
				      QString::number(isIn[1])+
				      QString::number(isIn[2])+
				      QString::number(isIn[3])
				      );*/

	      //looks stupid, but at least it's clear ...
	      //////////////////////////////
	      if(isIn[0] && isIn[1])
		{
		  //A and B are defining passage
		  WH.passageA = cX[0];
		  WH.passageB = cX[1];
		  WH.wallIndex1 = a;
		  WH.wallIndex2 = b;
		  //printSuccess("<1>");
		  return true;
		}

	      //////////////////////////////
	      if(!isIn[0] && !isIn[1])
		{
		  if( !(isIn[2] && isIn[3]) )
		    {
		      //printError("<1>");
		      continue;
		    }

		  WH.passageA = cX[2];
		  WH.passageB = cX[3];
		  WH.wallIndex1 = a;
		  WH.wallIndex2 = b;
		  //printSuccess("<2>");
		  return true;
		}

	      //////////////////////////////
	      if(isIn[0] && !isIn[1])
		{
		  if(!isIn[2] && !isIn[3])
		    {
		      //printError("<2>");
		      continue;
		    }
		  if(isIn[2] & !isIn[3])
		    {
		      if(cX[0].x == cX[2].x && cX[0].z == cX[2].z)
			{
			  //printError("<3>");
			  continue;
			}

		      WH.passageA = cX[0];
		      WH.passageB = cX[2];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;

		      //printSuccess("<3>");
		      return true;
		    }
		  if(!isIn[2] && isIn[3])
		    {
		      if(cX[0].x == cX[3].x && cX[0].z == cX[3].z)
			{
			  //printError("<4>");
			  continue;
			}

		      WH.passageA = cX[0];
		      WH.passageB = cX[3];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;
		      //printSuccess("<4>");
		      return true;
		    }
		  if(isIn[2] && isIn[3])
		    {
		      WH.passageA = cX[2];
		      WH.passageB = cX[3];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;
		      //printSuccess("<5>");
		      return true;
		    }
		}

	      //////////////////////////////
	      if(!isIn[0] && isIn[1])
		{
		  if(!isIn[2] && !isIn[3])
		    {
		      //printError("<5>");
		      continue;
		    }
		  if(isIn[2] & !isIn[3])
		    {
		      if(cX[1].x == cX[2].x && cX[1].z == cX[2].z)
			{
			  //printError("<6>");
			  continue;
			}
		      WH.passageA = cX[1];
		      WH.passageB = cX[2];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;

		      //printSuccess("<6>");
		      return true;
		    }
		  if(!isIn[2] && isIn[3])
		    {
		      if(cX[1].x == cX[3].x && cX[1].z == cX[3].z)
			{
			  //printError("<7>");
			  continue;
			}

		      WH.passageA = cX[1];
		      WH.passageB = cX[3];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;

		      //printSuccess("<7>");
		      return true;
		    }
		  if(isIn[2] && isIn[3])
		    {
		      WH.passageA = cX[2];
		      WH.passageB = cX[3];
		      WH.wallIndex1 = a;
		      WH.wallIndex2 = b;

		      //printSuccess("<8>");
		      return true;
		    }
		}
	    }
	}
    }
  //  printError("lines not collinear");
  return false;
}

//launched after succesfully connected fields:
//higlight wall parts, that can be chosen to make a passage.
//check if one of them is pointed with a mouse - show this choice
void
DesignWidget::drawWallParts()
{
  //isPartPointed will be set to true in "WH.highlighParts()"
  WH.newLoop();

  //two points of actually drawn edge
  LVector A, B;

  //starting point of first drawn part
  A = WH.passageA;
  if(!chosenField || !chosenField2)
    {
      printError("something went wrong: chosenField and chosenField2 not set");
      return;
    }

  setDrawStyle(drawStyleHighlightParts);
  
  if(chosenField -> passageTree[0] -> hasChild())
    {
      //TODO: implement possibility of choosing only wall parts - not whole walls.
      //      without that user can create invalid passages


      //      while(1)
      //      {

      //      }
    }


  B = WH.passageB;
  WH.highlightParts(painter, mouseX, mouseY);
}

void
DesignWidget::drawBreakingHole()
{
  //TODO: check what things can be calculated only once (once after choosing wall part)

  setDrawStyle(drawStyleHighlightParts);
  painter -> drawLine(WH.passageA.x, WH.passageA.z,
	    WH.passageB.x, WH.passageB.z);

  LVector temp = WH.passageB - WH.passageA;
  LVector multiplied = LVector(0.0f, 1.0f, 0.0f);
  LVector normal1 = temp^multiplied;
  normal1.normalize();

  //reportWidget -> setText (QString::number(normal1.x)+QString::number(normal1.z));
  //  reportWidget -> setText(QString::number(MH.pointLineDistance
  //					  (1,1,2,2,2,1)));

  float pointDistance = MH.pointLineDistance(WH.passageA.x, WH.passageA.z, WH.passageA.x + normal1.x, WH.passageA.z + normal1.z, mouseX, mouseY);

  //  reportWidget -> setText(QString::number(MH.pointLineDistance(WH.passageA.x, WH.passageA.z, WH.passageA.x + normal1.x, WH.passageA.z + normal1.z, mouseX, mouseY)));

  float passLength = temp.Length();
  
  LVector mouseVec;
  mouseVec.x = mouseX - WH.passageA.x;
  mouseVec.z = mouseY - WH.passageA.z;

  //setting distPointer for the first time
  if(WH.distPointer == NULL)
    {
      WH.distPointer = &WH.dist1;
      WH.pointPointer = &WH.point1;
    }
  
  //check 2 conditions: mouse is pointing farther than passageA or passageB
  //(problem was, that equations is showing distance from both sides of wall part)

  //is mouse pointing outside passageA?
  if((-temp) % mouseVec >= 0)
    {
      *WH.pointPointer = WH.passageA;
      printSuccess(QString::number(0));
      *WH.distPointer = 0;
      //      printInfo("vec!");
    }
  else
    //is mouse poining outside passageB?
    if(pointDistance > passLength)
      {
	*WH.pointPointer = WH.passageB;
	printSuccess(QString::number(temp.Length()));
	*WH.distPointer = temp.Length();
	//	printError("distance!");
      }
  //mouse is geometrically betweeen passageA and passageB
    else
      {
	WH.pointPointer->x = WH.passageA.x + temp.x*pointDistance/passLength;
	WH.pointPointer->z = WH.passageA.z + temp.z*pointDistance/passLength;
	printSuccess(QString::number(pointDistance));
	*WH.distPointer = pointDistance;
	//	printSuccess("middle!");
      }
  
    setDrawStyle(drawStyleBigPoint);
    WH.drawPassagePoints(painter);
}

void
DesignWidget::resetOnRMB()
{
  chosenField = NULL;
  chosenField2 = NULL;
  *GC -> appState = none;
}

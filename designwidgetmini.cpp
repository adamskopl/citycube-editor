#include "designwidgetmini.h"

DesignWidgetMini::DesignWidgetMini(globalContainer *GC)
{
  resize(QSize(300, 300));
  this->GC = GC;

  setMouseTracking(true);
  setVariables();
}

void
DesignWidgetMini::setVariables()
{
  gridSize = 10.0f;
  windowCornerIndex = 0;
}

void
DesignWidgetMini::paintEvent(QPaintEvent *event)
{
  //  painter = new QPainter(this);
  painter = new QPainter(this);
  drawGrid();

  switch(*(GC -> appState))
    {
    case(addingFloor):
      {
	break;
      }
    case(connectingFields):
      {
	break;
      }
    case(breakingHole):
      {

	break;
      }
    case(definingStairs):
      {

	break;
      }
    case(definingWindow):
      {

	drawChosenWall();
	drawDefinedWindows();
	break;
      }
    default:
      {

	break;
      }
    }
  drawPointer();
  drawImages();  
  delete painter;
}

void 
DesignWidgetMini::drawImages()
{
  QRectF target(235, 235, 60.0, 60.0);
  QRectF source(0.0, 0.0, 80.0, 80.0);
  
  switch(*(GC -> appState))
    {
    default:
      {
	QImage image("logo_mini.png");
	painter -> drawImage(target, image, source);
	break;
      }
    }
}

void
DesignWidgetMini::setDrawStyle(drawStyle style)
{
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
    case(drawStyleWallWindow):
      {
	pen.setStyle(Qt::SolidLine);
	pen.setColor("#ff8c19");
	pen.setWidth(1);
	break;
      }
    }

  painter-> setBrush(brush);
  painter->setPen(pen);
}

void DesignWidgetMini::drawGrid()
{
  setDrawStyle(drawStyleGrid);
  painter->fillRect(0, 0, 300, 300, brush);  

  int crossX = 0, crossY = 0;

  for(int x = 0; x <= 300; x += gridSize)
    for(int y = 0; y <= 300; y += gridSize)
      {
        if(mouseX - x <= 5 && mouseY - y <=5
           && mouseX - x >= -4 && mouseY -y >= -4)
	  {
            crossX = x; crossY = y;
	  }
	else
	  {
	    painter->drawPoint(x, y);
	  }
      }

  selectedX = crossX;
  selectedY = crossY;
}

void
DesignWidgetMini::drawPointer()
{
  setDrawStyle(pointer);
  painter->drawRect(QRect(selectedX-5, selectedY-5, 10, 10));
}

void
DesignWidgetMini::mouseMoveEvent(QMouseEvent *event)
{
  mouseX = event->pos().x();
  mouseY = event->pos().y();

  update();
}


void
DesignWidgetMini::drawChosenWall()
{
  //scale wall to nice fit in 300x300

  //wall's dimens ions
  //  float wallW, wallH;


  //scale having on mind bigger dimension (leave 2 points from 2 sides of bigger dimension)

  //drawn dimensions will be scaled - so they will differ from real ones
  //  float drawnH, drawnW;
  //  float biggerDimension = 260.0f;

  //
  //  float scale = biggerDimension / wallW;

  //  float topMargin, leftMargin;

  //  printf("\n%f, %f\n", wallW, wallH);

  /*
    scale two dimensions with value dictated by bigger dimension 
    in this way second dimension will surely fit
  */

  setDrawStyle(drawStyleWallWindow);
  painter->drawRect(leftMargin, topMargin, drawnW, drawnH);

  //  printf("wallW%f, wallH%f, biggerDimension%f, scale%f, drawnW%f, drawnH%f, topMargin%f, leftMargin%f\n", wallW, wallH, biggerDimension, scale, drawnW, drawnH, topMargin, leftMargin);

}

void 
DesignWidgetMini::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
      {
	//left button
      case(1):
        {
	  switch(*(GC -> appState))
	    {
	    case(addingFloor):
	      {
		break;
	      }
	    case(connectingFields):
	      {
		break;
	      }
	    case(breakingHole):
	      {
		
		break;
	      }
	    case(definingStairs):
	      {
		
		break;
	      }
	    case(definingWindow):
	      {
		switch(windowCornerIndex)
		  {
		  case(0):
		    {
		      newWindowCorners[0].x = selectedX - leftMargin;
		      newWindowCorners[0].y = selectedY - topMargin;

		      windowCornerIndex++;
		      break;
		    }
		  case(1):
		    {
		      //create new Window
		      newWindowCorners[1].x = selectedX - leftMargin;
		      newWindowCorners[1].y = selectedY - topMargin;

		      for(int a=0; a<2; a++)
			{
			  newWindowCorners[a].z = 0;
			}

		      //dimensions of new window
		      float tempW = LVector(
					    newWindowCorners[0].x - newWindowCorners[1].x,
					    0.0f,
					    0.0f).Length();

		      float tempH = LVector(
					    0.0f,
					    newWindowCorners[0].y - newWindowCorners[1].y,
					    0.0f).Length();

					    float posX, posY;
		      /*
			calculate position making simple equation: 
			smaller coordination + half of dimension
		      */
		      if(newWindowCorners[0].x > newWindowCorners[1].x)
			{
			  posX = newWindowCorners[1].x + tempW/2;
			}
		      else
			{
			  posX = newWindowCorners[0].x + tempW/2;
			}
		      if(newWindowCorners[0].y > newWindowCorners[1].y)
			{
			  posY = newWindowCorners[1].y + tempH/2;
			}
		      else
			{
			  posY = newWindowCorners[0].y + tempH/2;
			}

		      LBWindow *tempWindow = new LBWindow(LVector(posX, posY, 0.0f), tempW, tempH);
		      tempWindow -> connectTo(editedField -> windowTree[wallIndex]);

		      windowCornerIndex = 0;
		      break;
		    }
		  default:
		    {
		      printf("ERROR! Corner Index has value different than 0 or 1\n");
		      break;
		    }
		  }
		break;
	      }
	    default:
	      {
		
		break;
	      }
	    }
	  break;
	}
	//right button
    case(2):
      {
	switch(*(GC->appState))
	  {
	  case(definingWindow):
	    {
	      if(windowCornerIndex == 1)
		{
		  windowCornerIndex = 0;
		}
	      else
		{
		  *(GC->appState) = none;
		}
	      break;
	    }
	  default:
	    {
	      break;
	    }
	  }
	break;
      }
      default:
	{
	  break; 
	}
      }
}

void
DesignWidgetMini::drawDefinedWindows()
{

  //draw window being defined right now
  if(windowCornerIndex == 1)
    {
      setDrawStyle(drawStyleDefinedField);

      float x = newWindowCorners[0].x+leftMargin;
      float y = newWindowCorners[0].y+topMargin;
      float x2 = selectedX; 
      float y2 = selectedY;

      if(selectedX - x < 0)
	{
	  x2 = x;
	  x = selectedX;
	}

      if(selectedY - y < 0)
	{
	  y2 = y;
	  y = selectedY;
	}

      float W = LVector(x - x2, 0.0f, 0.0f).Length();
      float H = LVector(0.0f, y - y2, 0.0f).Length();

      
      painter->drawRect(x, y, W, H);
    }//draw window being defined right now

  if(! editedField -> windowTree[wallIndex] -> hasChild())
    {
      return;
    }
  
  setDrawStyle(drawStyleWallWindow);
  LBWindow *tempWindow = (LBWindow *)(editedField -> windowTree[wallIndex] -> child);
  while(1)
    {

      float drawPosX = leftMargin + tempWindow->pos.x - tempWindow->width/2;
      float drawPosY = topMargin + tempWindow->pos.y - tempWindow->height/2;

      painter->drawRect(drawPosX, drawPosY, tempWindow->width, tempWindow->height);

      //draw
      if(! tempWindow -> isLast())
	{
	  tempWindow = (LBWindow*)(tempWindow -> next);
	}
      else
	{
	  break;
	}
    }
}

void 
DesignWidgetMini::beginNewEditing(LField *field, int wall)
{
  editedField = field;
  wallIndex = wall;
  windowCornerIndex = 0;

  {
    int a,b;
    a = wallIndex;
    if (a == 3)
      b = 0;
    else
      b = a+1;

    wallW = LVector(editedField->corners[a].x - editedField->corners[b].x, 0.0, editedField->corners[a].z - editedField->corners[b].z).Length();

    wallH = editedField -> walls[wallIndex];
  }

    biggerDimension = 260.0f;

    if(wallH > wallW)
    {
      drawnH = biggerDimension;
      scale = biggerDimension / wallH;
      drawnW = wallW * scale;
      topMargin = (300.0f - biggerDimension)/2.0f;
      leftMargin = 150.0f - drawnW/2;
    }
  else
    {
      drawnW = biggerDimension;
      scale = biggerDimension / wallW;
      drawnH = wallH * scale;
      topMargin = 150 - drawnH/2;
      leftMargin = (300.0f - biggerDimension)/2.0f;
    }
}

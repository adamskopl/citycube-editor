#include "lbwallhelper.h"

LBWallHelper::LBWallHelper(globalContainer *gc)
{
  GC = gc;
  
  partPointed = false;
  
  //negative values means that distances are not set
  dist1 = -1;
  dist2 = -1;
  
  distPointer = NULL;
  pointPointer = NULL;
}

/*void LBWallHelper::highlightParts(QPainter *painter, float mouseX, float mouseY)
{
  painter -> drawLine(passageA.x, passageA.z,
  		      passageB.x, passageB.z);      
  
  //check if mouse is pointing circle <opisanym> on particular wall part
  LVector temp;
  temp = passageB - passageA;
  temp.y = 0;
  float length = temp.Length();
  
  LVector centerPoint(passageA.x + temp.x/2, passageA.z + temp.z/2);
  LVector mousePoint(mouseX, mouseY);
  if(LVector(centerPoint - mousePoint).Length() > length/2)
    return;
  partPointed = true;
  
  painter -> drawEllipse(passageA.x + temp.x/2 - length/2, 
			 passageA.z + temp.z/2 - length/2, 
			 length , length);
			 }*/

 /*
void 
LBWallHelper::newLoop()
{
  partPointed = false;
}
 */

  /*void
LBWallHelper::drawPassagePoints(QPainter *painter)
{
  painter -> drawPoint(point1.x, point1.z);

  if(distPointer == &dist2)
    {
      painter -> drawPoint(point2.x, point2.z);
      painter -> drawLine(point1.x, point1.z, point2.x, point2.z);
    }
    }*/

void
LBWallHelper::reset()
{
  partPointed = false;

  //negative values means that distances are not set
  dist1 = -1;
  dist2 = -1;

  distPointer = NULL;
  pointPointer = NULL;  
}


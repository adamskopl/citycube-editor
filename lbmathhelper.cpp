#include "lbmathhelper.h"
#include <iostream>
using namespace std;

lbmathhelper::lbmathhelper()
{
}
/*
  calculate distance from point to the line (of course that distance is equal to vector which starts in point, ends on line and is perpendicular to the line)
  x1, y1, x2, y2 define line
  xm, ym define point
*/
float
lbmathhelper::pointLineDistance(float x1, float y1, float x2, float y2,
				float xm, float ym)
{
  if(x1 == x2)
    {
      return fabs(x1 - xm);
    }

  float L = (y2 - y1)/(x2 - x1);


  float distance = 
    ( fabs(ym - y1 + L*(x1-xm)) ) /
    ( sqrt(1 + L*L) );

  return distance;
}

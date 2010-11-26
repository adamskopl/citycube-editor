#include "lbmathhelper.h"
#include <iostream>
using namespace std;

lbmathhelper::lbmathhelper()
{
}

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

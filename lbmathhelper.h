#ifndef LBMATHHELPER_H
#define LBMATHHELPER_H

#include <cmath>

class lbmathhelper
{
public:
    lbmathhelper();

    float pointLineDistance(float x1, float y1, float x2, float y2, 
			    float mx, float my);
};

#endif // LBMATHHELPER_H

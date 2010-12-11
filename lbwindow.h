#ifndef LBWINDOW_H
#define LBWINDOW_H

#include "vector.h"
#include "object.h"

class LBWindow : public LObject
{
public:
  LBWindow(LVector pos, float w, float h);
  LBWindow(){}

    LVector pos;
    float width, height;
};

#endif // LBWINDOW_H

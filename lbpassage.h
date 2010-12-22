#ifndef LBPASSAGE_H
#define LBPASSAGE_H

#include "field.h"
#include "counter.h"

class LField;

class lbpassage : public LObject, public Counter<lbpassage>
{
 public:
  lbpassage(float, float, LField*, float doorsHeight = 0.0f);
  

  // distance of beginning or end from wall's vector's first point
  float d1, d2;
  // with which field passage is created?
  LObject *destField;

  //temporary doors solution - how tall they are?
  float doorsHeight;
};

#endif // LBPASSAGE_H

#ifndef LBPASSAGE_H
#define LBPASSAGE_H

#include "field.h"
#include "counter.h"

class LObject;

class lbpassage : public LObject, public Counter<lbpassage>
{
 public:
  lbpassage(int, float, float, LObject*, float doorsHeight = 0.0f);
  lbpassage(int, float, float, int destObjectID, float doorsHeight = 0.0f);
  

  // distance of beginning or end from wall's vector's first point
  float d1, d2;
  // with which object passage is created? (fields, stairs)
  LObject *destObject;
  int destObjectID;

  //temporary doors solution - how tall they are?
  float doorsHeight;
};

#endif // LBPASSAGE_H

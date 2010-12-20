#ifndef LBPASSAGE_H
#define LBPASSAGE_H

#include "field.h"
#include "counter.h"

class LField;

class lbpassage : public LObject, public Counter<lbpassage>
{
 public:
  lbpassage(float, float, LField*);
  

  // distance of beginning or end from wall's vector's first point
  float d1, d2;
  // with which field passage is created?
  LField *destField;
  
};

#endif // LBPASSAGE_H

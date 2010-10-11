#ifndef LBPASSAGE_H
#define LBPASSAGE_H

#include "field.h"

class lbpassage
{
 public:
  lbpassage();
  
 private:
  // distance of beginning or end from wall's vector's first point
  float d1, d2;
  // with which field passage is created?
  LField *destField;
  
};

#endif // LBPASSAGE_H

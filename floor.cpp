#include "floor.h"

LBFloor::LBFloor(int ID, float H)
{
  setID(ID);
  height = H;
  isItDrawn = true;
  isItRendered = true;
  //    FS = FSNormal;
}


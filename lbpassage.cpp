#include "lbpassage.h"

lbpassage::lbpassage(int ID, float D1, float D2, LObject* destObject, float doorsHeight): d1(D1), d2(D2), destObject(destObject), doorsHeight(doorsHeight)
{
  //doorsHeight == 0.0f means for now, that passage has no doors
  setID(ID);
  destObjectID = destObject->giveID();
}

lbpassage::lbpassage(int ID, float D1, float D2, int destObjectID, float doorsHeight): d1(D1), d2(D2), destObjectID(destObjectID), doorsHeight(doorsHeight)
{
  setID(ID);
  destObject = NULL;
}

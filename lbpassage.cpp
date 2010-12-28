#include "lbpassage.h"

lbpassage::lbpassage(float D1, float D2, LField* destField, float doorsHeight): d1(D1), d2(D2), destField(destField), doorsHeight(doorsHeight)
{
  //doorsHeight == 0.0f means for now, that passage has no doors

  destFieldID = destField->giveID();
}

lbpassage::lbpassage(float D1, float D2, int destFieldID, float doorsHeight): d1(D1), d2(D2), destFieldID(destFieldID), doorsHeight(doorsHeight)
{
  destField = NULL;
}

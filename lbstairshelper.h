#ifndef LBSTAIRSHELPER_H
#define LBSTAIRSHELPER_H

#include <QWidget>
#include <QPainter>
#include <cstdio>
#include "lbhelpersbase.h"

class lbStairsHelper : public LBHelpersBase
{
 private:
  //  globalContainer *GC;
  
 public:
  /*
    Pass pointer to globalContainer used in main program.
  */
  lbStairsHelper(globalContainer *);
  bool tryToPrepareStairs();
  //  void drawPassagePoints(QPainter*);

  //reset isPartPointed
  //  void newLoop();
  //  bool isPartPointed();

  //beginning and  ending of common wall part of connected fields with stairs
  //  LVector passageA, passageB;
  //which walls are chosen for connections? (stairsBottom stairsTop)
  //  int wallIndex1, wallIndex2;

  //vector for temporairly calculating translation of chosen edge in topStairs field
  LVector translateVector;

  //points defining new passages connecting stairs
  //  LVector point1, point2;
  //pointer pointing on oone of pointX
  //  LVector* pointPointer;

  //distances from corner defining new passage  connecting stairs
  //  float dist1, dist2;
  //pointer pointing on one of distX
  //  float *distPointer;

private:
  //    bool partPointed;

    //reset all values
    void reset();
};

#endif // LBSTAIRSHELPER_H

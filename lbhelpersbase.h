#ifndef LBHELPERSBASE_H
#define LBHELPERSBASE_H
#include <QPainter>
#include "vector.h"
#include "field.h"

class LBHelpersBase
{
public:
    LBHelpersBase();

    //void drawPassagePoints(QPainter*);

    virtual void newLoop();
    virtual bool isPartPointed();
    virtual void highlightParts(QPainter *, float mouseX, float mouseY);

    //beginning and  ending of common wall part of connected fields with stairs
    LVector passageA, passageB;
    //which walls are chosen for connections? (stairsBottom stairsTop)
    int wallIndex1, wallIndex2;

    LVector point1, point2;
    //pointer pointing on oone of pointX
    LVector* pointPointer;

    //distances from corner defining new passage  connecting stairs
    float dist1, dist2;
    //pointer pointing on one of distX
    float *distPointer;

    LField *field1, field2;
    virtual void drawPassagePoints(QPainter*);      
    virtual void addPassage(LField *chosen1, LField *chosen2);

 protected:
    bool partPointed;

    //reset all values
    virtual void reset();
};

#endif // LBHELPERSBASE_H

#ifndef LBWALLHELPER_H
#define LBWALLHELPER_H
#include <QWidget>
#include <QPainter>
#include "vector.h"
#include "field.h"
#include "lbpassage.h"

class LBWallHelper
{
public:
    LBWallHelper();
    //beginning and  ending of common wall part of connected fields
    LVector passageA, passageB;
    //which walls are chosen for connections? (chosenField and Chosenfield2)
    int wallIndex1, wallIndex2;

    void highlightParts(QPainter *, float mouseX, float mouseY);
    void drawPassagePoints(QPainter*);

    //reset isPartPointed
    void newLoop();
    bool isPartPointed();

    //points defining new passage
    LVector point1, point2;
    //pointer pointing on oone of pointX
    LVector* pointPointer;

    //distances from corner defining new passage
    float dist1, dist2;
    //pointer pointing on one of distX
    float *distPointer;

    //add new passage defined by dist1 and dist2 to 2 chosen fields
    void addPassage(LField *chosen1, LField *chosen2);
private:
    bool partPointed;

    //reset all values
    void reset();
};

#endif // LBWALLHELPER_H

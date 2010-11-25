#ifndef FLOOR_H
#define FLOOR_H
#include "object.h"
#include "counter.h"

class LBFloor : public LObject, public Counter<LBFloor>
{
    //floor is a root of fields belonging to it


public:
    LBFloor(float);

    float height;
    bool isItDrawn;
    bool isItRendered;

    void drawFloor();


};

#endif // FLOOR_H

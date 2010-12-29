#ifndef LBSTAIRS_H
#define LBSTAIRS_H

#include "object.h"
#include "field.h"

class LBStairs : public LObject, public Counter<LBStairs>
{
public:
    LBStairs(int ID);

    //connected fields (to bottom and top of the staris)
    LField *connBottom;
    LField *connTop;
    int connBottomID;
    int connTopID;

    LVector cornersBottom[2];
    LVector cornersTop[2];

    void selfDraw();

    LVector horizontalVector;
};

#endif // LBSTAIRS_H

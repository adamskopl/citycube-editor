#ifndef LBSTAIRS_H
#define LBSTAIRS_H

#include "object.h"

/*
  TODO: why the hell lbstairs will not compile, if field.h is not included ??
 */
#include "field.h"

class LBStairs : public LObject, public Counter<LBStairs>
{
public:
    LBStairs(int ID);

    //connected fields (to bottom and top of the staris)
    LObject *connBottom;
    LObject *connTop;
    int connBottomID;
    int connTopID;

    LVector cornersBottom[2];
    LVector cornersTop[2];

    void selfDraw();

    LVector horizontalVector;

    void deletePassagesTo(LObject *destObject);
};

#endif // LBSTAIRS_H

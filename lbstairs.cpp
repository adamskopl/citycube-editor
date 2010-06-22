#include "lbstairs.h"

LBStairs::LBStairs()
{
}

void LBStairs::selfDraw()
{

    triangle vBottom[2];
    triangle vTop[2];

    vBottom[0].point[0] = cornersBottom[0].x;
    vBottom[0].point[1] = cornersBottom[0].y;
    vBottom[0].point[2] = cornersBottom[0].z;
    vBottom[1].point[0] = cornersBottom[1].x;
    vBottom[1].point[1] = cornersBottom[1].y;
    vBottom[1].point[2] = cornersBottom[1].z;

    vTop[0].point[0] = cornersTop[0].x;
    vTop[0].point[1] = cornersTop[0].y;
    vTop[0].point[2] = cornersTop[0].z;
    vTop[1].point[0] = cornersTop[1].x;
    vTop[1].point[1] = cornersTop[1].y;
    vTop[1].point[2] = cornersTop[1].z;


    glColor4f(1.0,1.0,1.0,1.0);
    glPushMatrix();

    glBegin(GL_QUADS);
    {
        glVertex3fv(vBottom[0].point);
        glVertex3fv(vBottom[1].point);
        glVertex3fv(vTop[0].point);
        glVertex3fv(vTop[1].point);
    }

    glEnd();
    glPopMatrix();
}

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

    //these values should be calculated in constructor
    //to not recalculate same values every time

    float stairsHeight = cornersTop[0].y - cornersBottom[0].y;

    // assumed every step's height (it will be modified to fit stairs height)
    //1 pix = 5cm
    float desiredHeight = 4.0f;

    float stairsWidth = LVector(cornersBottom[0].x - cornersTop[0].x,
    				0.0f, cornersBottom[0].z - cornersTop[0].z).Length();

    lbmathhelper math;

    //    float stairsWidth = math.pointLineDistance(vBottom[0].point[2], vBottom[0].point[0], vTop[0].point[2], vTop[0].point[0], vTop[1].point[2], vTop[1].point[0]);

    int stepsNumber = stairsHeight / desiredHeight;
    float stepHeight = stairsHeight / stepsNumber;
    float stepWidth = stairsWidth / stepsNumber;

    //variables keeping current step's coordinates:

    //vertical part of step
    triangle verticalDraw[4];
    //horizontal part of step
    triangle horizontalDraw[4];

    /*

      3 ------ 2           3 ------ 2
      |        |          /        /
      0 ------ 1         0 ------ 1
     vertical part    horizontal part

      */

    /////////////////
    verticalDraw[0] = vBottom[0];
    verticalDraw[1] = vBottom[1];

    verticalDraw[2] = verticalDraw[1];
    verticalDraw[2].point[1] += stepHeight;

    verticalDraw[3] = verticalDraw[0];
    verticalDraw[3].point[1] += stepHeight;
    /////////////////
    horizontalDraw[0] = verticalDraw[3];
    horizontalDraw[1] = verticalDraw[2];

    horizontalDraw[2] = horizontalDraw[1];
    horizontalDraw[2].point[0] += horizontalVector.x * stepWidth;
    horizontalDraw[2].point[2] += horizontalVector.z * stepWidth;

    horizontalDraw[3] = horizontalDraw[0];
    horizontalDraw[3].point[0] += horizontalVector.x * stepWidth;
    horizontalDraw[3].point[2] += horizontalVector.z * stepWidth;
    /////////////////

    //printf("%f, %f\n", horizontalVector.x, horizontalVector.z);

    glShadeModel(GL_SMOOTH);
    /*
      glColor4f(0.0,0.0,0.0,1.0);
      glPushMatrix();
      glBegin(GL_LINE);
      glVertex3fv(vBottom[0].point);
      glVertex3fv(vTop[0].point);   
      glVertex3fv(vBottom[1].point);
      glVertex3fv(vTop[1].point);    
      glEnd();
    */

    
    for(int stepCnt = 0; stepCnt < stepsNumber; stepCnt++)
    {

      glBegin(GL_LINE_LOOP);
      {
        //draw vertical part of step
        glVertex3fv(verticalDraw[0].point);
        glVertex3fv(verticalDraw[1].point);
        glVertex3fv(verticalDraw[2].point);
	glVertex3fv(verticalDraw[3].point);
      }
      glEnd();
	
      glBegin(GL_LINE_LOOP);
      {
	//draw horizontal part of step
	glVertex3fv(horizontalDraw[0].point);
	glVertex3fv(horizontalDraw[1].point);
	glVertex3fv(horizontalDraw[2].point);
	glVertex3fv(horizontalDraw[3].point);
      }
      glEnd();
    

        //set parts of next step
        for(int setCnt = 0; setCnt < 4; setCnt++)
        {
            //update every vertice's coordinates
            verticalDraw[setCnt].point[0] += horizontalVector.x * stepWidth;
            horizontalDraw[setCnt].point[0] += horizontalVector.x * stepWidth;

            verticalDraw[setCnt].point[1] += stepHeight;
            horizontalDraw[setCnt].point[1] += stepHeight;

            verticalDraw[setCnt].point[2] += horizontalVector.z * stepWidth;
            horizontalDraw[setCnt].point[2] += horizontalVector.z * stepWidth;
        }
    }

    glPopMatrix();
}

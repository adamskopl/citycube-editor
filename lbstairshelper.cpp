#include "lbstairshelper.h"

lbStairsHelper::lbStairsHelper(globalContainer *GC):GC(GC)
{
  partPointed = false;
  
  //negative values means that distances are not set
  dist1 = -1;
  dist2 = -1;
  
  distPointer = NULL;
  pointPointer = NULL;
}

/*
  Launched only if *stairsBottom and stairsTop are set in globalconatiner.
  Try to connect chosen fields with stairs.

  Return 'false' if something fails and stairs can't be prepared.
*/
bool
lbStairsHelper::tryToPrepareStairs()
{

  if((GC -> stairsBottom == NULL) || (GC -> stairsTop == NULL))
    {
      printf("lbStairsHelper::tryToAddStairs: stairsBottom or stairsTop not set!\n");
      return false;
    }

  /*
    Try to find 2 parallel edges from different fields.
    If success, try
   */
  
  //for every pair of edges from different sectors (using counting variables to set wallsIndex1 and wallIndex2

  //taking edges from bottomField ...
  for(int a = 0; a < 4; a++)
    {
      //taking edges from topField
      for(int b = 0; b < 4; b++)
	{
	  //normal vector for stairsBottom and stairsTop
	  LVector bottomVector;
	  LVector topVector;

	  //considered corners ([0] and [1] are points from first edge. [2] and [3] from second)
	  LVector cX[4];

	  cX[0] = GC->stairsBottom -> corners[a];
	  if(a == 3) 
	    {
	      cX[1] = GC->stairsBottom -> corners[0];
	    }
	  else
	    {
	      cX[1] = GC->stairsBottom -> corners[a+1];
	    }
	  bottomVector = -(GC->stairsBottom->cornersN[a]);

	  cX[2] = GC->stairsTop -> corners[b];
	  if(b == 3) 
	    {
	      cX[3] = GC->stairsTop -> corners[0];
	    }
	  else
	    {
	      cX[3] = GC->stairsTop -> corners[b+1];  
	    }
	  topVector = -(GC->stairsTop->cornersN[b]);


	  /*
	    For now and later code is almost the same like for making holes in walls (DesignWidget::checkTouching()
	    
	    To rewrite te code we will make a little trick: we will translate whole second edge:
	    - translation vector has direction like normal vector of second considered edge
	    - translation vector's length is equal to distance from point belonging to second edge to line created by points of first edge

	    In this way we will have second edge's copy, which will be collinear with first edge. And idea used in connecting fields will be reused.
	   */

	  //as a point use first point of second edge. line is a line created by two points of first edge
	  

	  /*
	    First we are checking if two edges are parallel:
	    1. compare slopes:
	       - of line created by points of first edge
	       - of line created by points of second edge
	    2. if slopes are equal, so edges are parallel

	    Slope is change in y divided by change in x. Cross multiplying gives:
	  */
          if((cX[0].x - cX[1].x)*(cX[2].z - cX[3].z) == 
	     (cX[2].x - cX[3].x)*(cX[0].z - cX[1].z))
	    {
	      //check if normals are opposite - otherwise continue searching
	      if( !(bottomVector == -topVector) )
		{
		  continue;
		}
	      //	      printf("\nx1: %f, z1: %f, x2: %f, z2: %f\n", bottomVector.x, bottomVector.z, topVector.x, topVector.z);
	      
	      float dist = GC->math->pointLineDistance(cX[0].x, cX[0].z, cX[1].x, cX[1].z, cX[2].x, cX[2].z);
	      //	      printf("Distance form point to line: %f", dist);

	      LVector translateVector = topVector * dist;

	      cX[2] += translateVector;
	      cX[3] += translateVector;
	      
	      //needed for drawing and further calculations in DesignWidget
	      this->translateVector = translateVector;

	      /*	      float testDist = GC->math->pointLineDistance(cX[0].x, cX[0].z, cX[1].x, cX[1].z, cX[2].x, cX[2].z);
			      printf("Distance form point to line: %f", testDist);*/


	      /*/////////////////////////////////////*/
	      //part copied from DesignWidget::checkTouching() ...



	      //count how many points of one edge belongs to second edge and vice-versa
	      //2:0 - ok, 2:1 - ok, 2:2 - ok, 1:1 - ok if points are not equal

	      bool isIn[4];
	      //e.g isA: establish if cX[0] and cX[2] and cX[3] are collinear. if so, check if
	      // cX[0].x is betweeen cX[2].x and cX[3].x and cA.z between cX[2].z and cX[3].z

	      //A & B belongs to CD?
	      for(int cnt = 0; cnt < 2; cnt++)
		{
		  bool isXok, isZok;

		  //check which .x coor is first
		  if(cX[2].x < cX[3].x)
		    {isXok = (cX[cnt].x >= cX[2].x && cX[cnt].x <= cX[3].x);}
		  else
		    {isXok = (cX[cnt].x <= cX[2].x && cX[cnt].x >= cX[3].x);}

		  if(cX[2].z < cX[3].z)
		    {isZok = (cX[cnt].z >= cX[2].z && cX[cnt].z <= cX[3].z);}
		  else
		    {isZok = (cX[cnt].z <= cX[2].z && cX[cnt].z >= cX[3].z);}

		  isIn[cnt] = isXok && isZok;
		}

	      //C & D  belongs to AB?
	      for(int cnt = 2; cnt < 4; cnt++)
		{
		  bool isXok, isZok;

		  //check which .x coor is first
		  if(cX[0].x < cX[1].x)
		    {isXok = (cX[cnt].x >= cX[0].x && cX[cnt].x <= cX[1].x);}
		  else
		    {isXok = (cX[cnt].x <= cX[0].x && cX[cnt].x >= cX[1].x);}

		  if(cX[0].z < cX[1].z)
		    {isZok = (cX[cnt].z >= cX[0].z && cX[cnt].z <= cX[1].z);}
		  else
		    {isZok = (cX[cnt].z <= cX[0].z && cX[cnt].z >= cX[1].z);}

		  isIn[cnt] = isXok && isZok;
		}

	      //looks stupid, but at least it's clear ...
	      //////////////////////////////
	      if(isIn[0] && isIn[1])
		{
		  //A and B are defining passage
		  passageA = cX[0];
		  passageB = cX[1];
		  wallIndex1 = a;
		  wallIndex2 = b;
		  //printSuccess("<1>");
		  return true;
		}

	      //////////////////////////////
	      if(!isIn[0] && !isIn[1])
		{
		  if( !(isIn[2] && isIn[3]) )
		    {
		      //printError("<1>");
		      continue;
		    }

		  passageA = cX[2];
		  passageB = cX[3];
		  wallIndex1 = a;
		  wallIndex2 = b;
		  //printSuccess("<2>");
		  return true;
		}

	      //////////////////////////////
	      if(isIn[0] && !isIn[1])
		{
		  if(!isIn[2] && !isIn[3])
		    {
		      //printError("<2>");
		      continue;
		    }
		  if(isIn[2] & !isIn[3])
		    {
		      if(cX[0].x == cX[2].x && cX[0].z == cX[2].z)
			{
			  //printError("<3>");
			  continue;
			}

		      passageA = cX[0];
		      passageB = cX[2];
		      wallIndex1 = a;
		      wallIndex2 = b;

		      //printSuccess("<3>");
		      return true;
		    }
		  if(!isIn[2] && isIn[3])
		    {
		      if(cX[0].x == cX[3].x && cX[0].z == cX[3].z)
			{
			  //printError("<4>");
			  continue;
			}

		      passageA = cX[0];
		      passageB = cX[3];
		      wallIndex1 = a;
		      wallIndex2 = b;
		      //printSuccess("<4>");
		      return true;
		    }
		  if(isIn[2] && isIn[3])
		    {
		      passageA = cX[2];
		      passageB = cX[3];
		      wallIndex1 = a;
		      wallIndex2 = b;
		      //printSuccess("<5>");
		      return true;
		    }
		}

	      //////////////////////////////
	      if(!isIn[0] && isIn[1])
		{
		  if(!isIn[2] && !isIn[3])
		    {
		      //printError("<5>");
		      continue;
		    }
		  if(isIn[2] & !isIn[3])
		    {
		      if(cX[1].x == cX[2].x && cX[1].z == cX[2].z)
			{
			  //printError("<6>");
			  continue;
			}
		      passageA = cX[1];
		      passageB = cX[2];
		      wallIndex1 = a;
		      wallIndex2 = b;

		      //printSuccess("<6>");
		      return true;
		    }
		  if(!isIn[2] && isIn[3])
		    {
		      if(cX[1].x == cX[3].x && cX[1].z == cX[3].z)
			{
			  //printError("<7>");
			  continue;
			}

		      passageA = cX[1];
		      passageB = cX[3];
		      wallIndex1 = a;
		      wallIndex2 = b;

		      //printSuccess("<7>");
		      return true;
		    }
		  if(isIn[2] && isIn[3])
		    {
		      passageA = cX[2];
		      passageB = cX[3];
		      wallIndex1 = a;
		      wallIndex2 = b;

		      //printSuccess("<8>");
		      return true;
		    }
		}
	      /*/////////////////////////////////////*/
	    }
	}
    }

  return false;
}



/*void
lbStairsHelper::drawPassagePoints(QPainter *painter)
{
  painter -> drawPoint(point1.x, point1.z);

  if(distPointer == &dist2)
    {
      painter -> drawPoint(point2.x, point2.z);
      painter -> drawLine(point1.x, point1.z, point2.x, point2.z);
    }
    }*/
/*
void 
lbStairsHelper::newLoop()
{
  partPointed = false;
}
*/

void
lbStairsHelper::reset()
{
  partPointed = false;

  //negative values means that distances are not set
  dist1 = -1;
  dist2 = -1;

  distPointer = NULL;
  pointPointer = NULL;  
}

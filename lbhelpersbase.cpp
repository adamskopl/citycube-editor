#include "lbhelpersbase.h"

LBHelpersBase::LBHelpersBase()
{
}

void
LBHelpersBase::highlightParts(QPainter *painter,float mouseX,float mouseY)
{
  painter -> drawLine(passageA.x, passageA.z,
  		      passageB.x, passageB.z);      
  
  //check if mouse is pointing circle <opisanym> on particular wall part
  LVector temp;
  temp = passageB - passageA;
  temp.y = 0;
  float length = temp.Length();
  
  LVector centerPoint(passageA.x + temp.x/2, passageA.z + temp.z/2);
  LVector mousePoint(mouseX, mouseY);
  if(LVector(centerPoint - mousePoint).Length() > length/2)
    return;
  partPointed = true;
  
  painter -> drawEllipse(passageA.x + temp.x/2 - length/2, 
			 passageA.z + temp.z/2 - length/2, 
			 length , length);
}

bool
LBHelpersBase::isPartPointed()
{
  return partPointed;
}

void
LBHelpersBase::newLoop()
{
  partPointed = false;
}

void
LBHelpersBase::drawPassagePoints(QPainter *painter)
{
  painter->drawPoint(point1.x, point1.z);

  if(distPointer == &dist2)
    {
      painter -> drawPoint(point2.x, point2.z);
      painter -> drawLine(point1.x, point1.z, point2.x, point2.z);
    }
}

void
LBHelpersBase::addPassage(LField *chosen1, LField *chosen2)
{

  //distances for 2 new passages
  //for chosen1:
  float dist1a, dist2a;
  //for chosen2:
  float dist1b, dist2b;

  //dist 1 has to be a smaller value: that's how passage concept works
  if(dist1 > dist2)
    {
      float temp = dist2;
      dist2 = dist1;
      dist1 = temp;
    }    

  float partLength = LVector(passageA - passageB).Length();

  {
    float distFromA_f1, distFromB_f1;
    float distFromA_f2, distFromB_f2;

    //distances for both fields: how far passageA and passageB are from first corner defining chosen wall
    distFromA_f1 = chosen1 -> howFarPointIs(wallIndex1, passageA);
    distFromB_f1 = chosen1 -> howFarPointIs(wallIndex1, passageB);
    
    distFromA_f2 = chosen2 -> howFarPointIs(wallIndex2, passageA);
    distFromB_f2 = chosen2 -> howFarPointIs(wallIndex2, passageB);

    //dist1 and dist2 for field, which has opposite direction of vector
    float newDist1 = partLength - dist2;
    float newDist2 = partLength - dist1;

    //check for chosen1 what is closer to first corner defining chosen wall...

    //passageA is closer to corner in chosen1 (dist1 and dist2 are going in same direction as wall's definition)
    if(distFromA_f1 < distFromB_f1)
      {
	dist1a = distFromA_f1 + dist1;
	dist2a = distFromA_f1 + dist2;
	
	//for second field dist1 and dist2 are not going in the same direction as wall's definition
	dist1b = distFromB_f2 + newDist1;
	dist2b = distFromB_f2 + newDist2;
      }
    else
      //passageB is closer to corner in chosen1
      if(distFromA_f1 > distFromB_f1)
	{
	  dist1a = distFromB_f1 + newDist1;
	  dist2a = distFromB_f1 + newDist2;

	  dist1b = distFromA_f2 + dist1;
	  dist2b = distFromA_f2 + dist2;
	}
      else
	{
	  //error !!
	  reset();
	  return;
	}
  }


  //final passages for chosen1 and chosen2
  lbpassage *tempPass = new lbpassage(dist1a, dist2a);
  lbpassage *tempPass2 = new lbpassage(dist1b, dist2b);


    //okay ... now we will do crazy thing, because Adam wants fast effects:

    /*
      We will disconnect all ready passages to tempTree. And than we will connect
      them again, checking if it's time for our tempPass
     */

    ////////////SORT OPERATION 1//////////////
    
    //no child, no problem: just connect
    if(! (chosen1 -> passageTree[wallIndex1] -> hasChild()) )
      {
	tempPass -> connectTo(chosen1 -> passageTree[wallIndex1]);
      }
    else
      {
	lbpassage *tempTree = new lbpassage(0, 0);
	while( chosen1 -> passageTree[wallIndex1] -> hasChild() )
	  {
	    lbpassage *discPass = (lbpassage*)(chosen1 -> passageTree[wallIndex1] -> child);
	    discPass -> connectTo(tempTree);
	  }
	//all passages are in tempTree. connect them again, check where is place for
	//tempPass
	while(tempTree -> hasChild())
	  {
	    if(tempPass != NULL)
	      {
		lbpassage *tempTreeChild = ((lbpassage*)(tempTree -> child));
		if(tempPass -> d1 < tempTreeChild -> d1 )
		  {
		    tempPass -> connectTo(chosen1 -> passageTree[wallIndex1]);
		    tempPass = NULL;
		  }
	      }
	    tempTree -> child -> connectTo(chosen1 -> passageTree[wallIndex1]);
	  }

	//if tempPass is not yet connected, it goes to the end
	if(tempPass != NULL)
	  {
	    tempPass -> connectTo(chosen1 -> passageTree[wallIndex1]);
	  }
      }
    ////////////SORT OPERATION 1//////////////

    ////////////SORT OPERATION 2//////////////
    //no child, no problem: just connect
    if(! (chosen2 -> passageTree[wallIndex2] -> hasChild()) )
      {
	tempPass2 -> connectTo(chosen2 -> passageTree[wallIndex2]);
      }
    else
      {
	lbpassage *tempTree = new lbpassage(0, 0);
	while( chosen2 -> passageTree[wallIndex2] -> hasChild() )
	  {
	    lbpassage *discPass = (lbpassage*)(chosen2 -> passageTree[wallIndex2] -> child);
	    discPass -> connectTo(tempTree);
	  }
	//all passages are in tempTree. connect them again, check where is place for
	//tempPass
	while(tempTree -> hasChild())
	  {
	    if(tempPass2 != NULL)
	      {
		lbpassage *tempTreeChild = ((lbpassage*)(tempTree -> child));
		if(tempPass2 -> d1 < tempTreeChild -> d1 )
		  {
		    tempPass2 -> connectTo(chosen2 -> passageTree[wallIndex2]);
		    tempPass2 = NULL;
		  }
	      }
	    tempTree -> child -> connectTo(chosen2 -> passageTree[wallIndex2]);
	  }
	//if tempPass is not yet connected, it goes to the end
	if(tempPass2 != NULL)
	  {
	    tempPass2 -> connectTo(chosen2 -> passageTree[wallIndex2]);
	  }
      }
    ////////////SORT OPERATION 2//////////////

    //print all passages in chosen1 and chosen2
    {
      printf("----------------------------\n");
      printf("field1 :\n");
      lbpassage *helppassage;
      if(chosen1 -> passageTree[wallIndex1] -> hasChild())
	{
	  helppassage = (lbpassage*)chosen1 -> passageTree[wallIndex1] -> child; 
	}
      else
	{
	  return;
	}
      
      while(1)
      	{
	  printf("passage: %f, %f\n", helppassage->d1, helppassage->d2);

      	  if(! helppassage -> isLast())
	    {helppassage = (lbpassage*)(helppassage->next);}
	  else
	    {
	      break;
	    }
	}

      printf("----------------------------\n");
      printf("field2 :\n");
      if(chosen2 -> passageTree[wallIndex2] -> hasChild())
	{
	  helppassage = (lbpassage*)chosen2 -> passageTree[wallIndex2] -> child; 
	}
      else
	{
	  return;
	}
      
      while(1)
      	{
	  printf("passage: %f, %f\n", helppassage->d1, helppassage->d2);

      	  if(! helppassage -> isLast())
	    {helppassage = (lbpassage*)(helppassage->next);}
	  else
	    {
	      break;
	    }
	}
    }//print all passages in chosen1 and chosen2


    //TODO: test for LField::howFarPointIs
    //   printf("dist1: %f\n", chosen1 -> howFarPointIs(wallIndex1, passageA));
    //    printf("dist2: %f\n", chosen1 -> howFarPointIs(wallIndex1, passageB));
    //   printf("dist2: %f\n", chosen2 -> howFarPointIs(wallIndex2, passageA));


    //passage created - be reade for next ones (invoked from inheritating class)
    reset();
}

//invoked in different way for every class inheriting from this one
void
LBHelpersBase::reset(){}

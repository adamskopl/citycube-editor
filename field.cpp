#include "field.h"
#include "floor.h"
LField::LField()
{
  walls[0] = 10.0;
  walls[1] = 10.0;
  walls[2] = 10.0;
  walls[3] = 10.0;
}

LField::~LField()
{
  
}

LField::LField(LVector *C)
{
  statusField = noneField;
  
  //walls have 0 heights
  walls[0] = 0.0f;
  walls[1] = 0.0f;
  walls[2] = 0.0f;
  walls[3] = 0.0f;
  
  empty = true;
  
  corners[0] = C[0];
  corners[1] = C[1];
  corners[2] = C[2];
  corners[3] = C[3];
  
  calculateVectorsAndNormals();
  
  //////////////////////////////////////////////////////////////////////////
  //checking if field was defined with corners in clockwise order
  //choose point that is in center of field.
  
  if(corners[0].x > corners[2].x)
    centerPoint.x = corners[0].x - (corners[0].x - corners[2].x)/2;
  else
    centerPoint.x = corners[2].x - (corners[2].x - corners[0].x)/2;
  
  //centerPoint.y = ((LBFloor*)parent) -> height;
  
  if(corners[1].z > corners[3].z)
    centerPoint.z = corners[1].z - (corners[1].z - corners[3].z)/2;
  else
    centerPoint.z = corners[3].z - (corners[3].z - corners[1].z)/2;
  
  //and check if it really is in field
  if( ! isPointIn(centerPoint) )
    {
      /*
	change corners order and recalculate vectors and normals
	
        D----C       B----C
        |    |  -->  |    |
        A----B       A----D
      */
      
      LVector help = corners[1];
      corners[1] = corners[3];
      corners[3] = help;
      
      calculateVectorsAndNormals();
    }
  //////////////////////////////////////////////////////////////////////////
  
  connections[0] = connections[1] = connections[2] = connections[3] = NULL;
  
  //FOR COUNTING DISTANCE PART
  float dx, dz, length;
  //   calculating normals ...
  //up
  dz = C[0].z - C[1].z;
  dx = C[1].x - C[0].x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[0].x = dz / length;
  CornersN[0].z = dx / length;
  /*  printf("UP : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[0].x, CornersN[0].z);*/
  //right
  dz = C[1].z - C[2].z;
  dx = C[2].x - C[1].x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[1].x = dz / length;
  CornersN[1].z = dx / length;
  /*  printf("RIGHT : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[1].x, CornersN[1].z);*/
  
  //down
  dz = C[2].z - C[3].z;
  dx = C[3].x - C[2].x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[2].x = dz / length;
  CornersN[2].z = dx / length;
  /*  printf("DOWN : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[2].x, CornersN[2].z);*/
  
  //left
  dz = C[3].z - C[1].z;
  dx = C[1].x - C[3].x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[3].x = dz / length;
  CornersN[3].z = dx / length;
  /*  printf("LEFT : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[3].x, CornersN[3].z);*/
  
  /* 
     build 4 empty passage trees (for every wall)
     build 4 empty window trees (for every wall)
   */
  for(int a = 0; a < 4; a++)
    {
      passageTree[a] = new lbpassage(0, 0);
      windowTree[a] = new LBWindow();
    }
}


void LField::calculateVectorsAndNormals()
{
  //needed to calculate normals and maybe for other things in future
  vectors[0] = LVector(corners[1].x - corners[0].x, 0.0f, corners[1].z - corners[0].z);
  vectors[1] = LVector(corners[2].x - corners[1].x, 0.0f, corners[2].z - corners[1].z);
  vectors[2] = LVector(corners[3].x - corners[2].x, 0.0f, corners[3].z - corners[2].z);
  vectors[3] = LVector(corners[0].x - corners[3].x, 0.0f, corners[0].z - corners[3].z);
  
  //calculating normals - vector multiply of vector.x and vector(0.0f, 1.0f, 0.0f)
  LVector multiplied = LVector(0.0f, 1.0f, 0.0f);
  cornersN[0] = vectors[0]^multiplied; cornersN[0].normalize();
  cornersN[1] = vectors[1]^multiplied; cornersN[1].normalize();
  cornersN[2] = vectors[2]^multiplied; cornersN[2].normalize();
  cornersN[3] = vectors[3]^multiplied; cornersN[3].normalize();
}

//char LField::giveX(){return x;}
//char LField::giveY(){return y;}

/*void LField::othersDraw(){
  
  
  glPushMatrix();
  selfDraw();
  if (hasChild()){
  ((LField*)child)->othersDraw();
  
  }    
  glPopMatrix();
  
  
  if (hasParent() && !isLast())
  ((LField*)next)->othersDraw();
  
  }*/

void LField::selfDraw(){
  
  //  glShadeModel(GL_SMOOTH);

  //!!! READ MORE ABOUT 4 FUNCTIONS INVOKED BELOW !!!

  glEnable( GL_LINE_SMOOTH );
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  // Enable Blending
  glEnable(GL_BLEND);
  // Specifies pixel arithmetic
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  
  glPushMatrix();


  triangle vertex[4];
  
  vertex[0].point[0] = corners[0].x;
  vertex[0].point[1] = corners[0].y;
  vertex[0].point[2] = corners[0].z;
  
  vertex[1].point[0] = corners[1].x;
  vertex[1].point[1] = corners[1].y;
  vertex[1].point[2] = corners[1].z;
  
  vertex[2].point[0] = corners[2].x;
  vertex[2].point[1] = corners[2].y;
  vertex[2].point[2] = corners[2].z;
  
  vertex[3].point[0] = corners[3].x;
  vertex[3].point[1] = corners[3].y;
  vertex[3].point[2] = corners[3].z;



  //draw fields without walls
  glLineWidth(1.0f);  

  if(statusFields == chosenField || statusField == chosenField)
    {
      glColor4f(1.0f, 0.0f, 0.0f, 0.1f);   
    }
  else
    {
      glColor4f(0.0f, 0.0f, 0.0f, 0.1f);   
    }



  glBegin(GL_QUADS);
  {
    glVertex3fv(vertex[0].point);
    glVertex3fv(vertex[1].point);
    glVertex3fv(vertex[2].point);
    glVertex3fv(vertex[3].point);	
  }
  glEnd();

  glColor4f(0.0, 0.0, 0.0, 1.0);
  

  

  //for field's edge draw wallparts
  for(int cnt = 0; cnt < 4; cnt++)
    {
      int p1, p2; //indexes of vertices used for drawing wall
      
      p1 = cnt;
      if(p1 == 3) p2 = 0; else p2 = p1+1;


      LVector wallVector = corners[p2] - corners[p1];
      float wallLength = wallVector.Length();

      //points for storing actually considered wall's parts
      LVector pointA, pointB;

      pointA = corners[p1];

      if(passageTree[cnt] -> hasChild())
	{
	  lbpassage *helpPassage = (lbpassage*)(passageTree[p1] -> child);

	  while(1)
	    {
	      pointB = corners[p1] + wallVector * (helpPassage -> d1 / wallLength);

	      //render wall part
	      //	      glColor4f(0.85, 0.2, 0.0, 1.0);
	      glBegin(GL_LINE_LOOP);      
	      glVertex3f(pointA.x, pointA.y, pointA.z);
	      glVertex3f(pointB.x, pointB.y, pointB.z);
      
	      pointA.y += walls[cnt]; //wall's height
	      pointB.y += walls[cnt];//10.0;
      
	      //	      glColor4f(0.0, 0.0, 0.0, 1.0);
      
	      glVertex3f(pointB.x, pointB.y, pointB.z);
	      glVertex3f(pointA.x, pointA.y, pointA.z);
	      glEnd();
	      pointA.y -= walls[cnt]; //wall's height
	      pointB.y -= walls[cnt];//10.0;
	      //end of wall's part render
	      
	      pointA = corners[p1] + wallVector * (helpPassage -> d2 / wallLength);
	      
	      if( ! helpPassage -> isLast())
		{
		  helpPassage = (lbpassage*)(helpPassage -> next);
		}
	      else
		{
		  break;
		}
	    }
	}

      //render last wall part (render whole wall if we don't have passages yet)
      pointB = corners[p2];
      
      //      glColor4f(0.85, 0.2, 0.0, 1.0);

      glBegin(GL_LINE_LOOP);
      glVertex3f(pointA.x, pointA.y, pointA.z);
      glVertex3f(pointB.x, pointB.y, pointB.z);
      
      pointA.y += walls[cnt]; //wall's height
      pointB.y += walls[cnt];//10.0;
      
      //      glColor4f(0.0, 0.0, 0.0, 1.0);
      
      glVertex3f(pointB.x, pointB.y, pointB.z);
      glVertex3f(pointA.x, pointA.y, pointA.z);
      glEnd();
    }
  //  glEnd();
  

  //render windows:

  for(int cntWin = 0; cntWin < 4; cntWin++)
    {
      //wall has windows - draw them
      if( windowTree[cntWin]->hasChild() )
	{
	  /*
	    indexes of vertices used for calculating vector for proper window 
	    drawing
	  */
	  int p1, p2; 
      
	  p1 = cntWin;
	  if(p1 == 3) p2 = 0; else p2 = p1+1;

	  LVector wallVector = corners[p2] - corners[p1];
	  float wallLength = wallVector.Length();

	  LBWindow *helpWindow = (LBWindow*)(windowTree[p1] -> child);	  
	  
	  while(1)
	    {
	      //render helpWindow ...

	      /*
		window's 'X' coord divided by wall's length gives
		proportion that can be used to calcualte 'Z' coord
	      */
	      float div = helpWindow->pos.x/wallLength;

	      float cx = corners[p1].x;
	      float cy = corners[p1].y;
	      float cz = corners[p1].z;

	      LVector windowVector;
	      {
		windowVector.x = cx + wallVector.x * div;
		windowVector.y = cy + helpWindow->pos.y;
		windowVector.z = cz + wallVector.z * div;
	      }

	      triangle vertex[4];


	      /*
		proportions that help to calculate some coordinations
	      */
	      float div1 = (helpWindow->pos.x - helpWindow->width/2)/wallLength;
	      float div2 = (helpWindow->pos.x + helpWindow->width/2)/wallLength;

	      vertex[0].point[0] = cx + wallVector.x * div1;
	      vertex[0].point[1] = cy + windowVector.y + helpWindow->height/2;
	      vertex[0].point[2] = cz + wallVector.z * div1;

	      vertex[1].point[0] = cx + wallVector.x * div2;
	      vertex[1].point[1] = cy + windowVector.y + helpWindow->height/2;
	      vertex[1].point[2] = cz + wallVector.z * div2;

	      vertex[2].point[0] = cx + wallVector.x * div2;
	      vertex[2].point[1] = cy + windowVector.y - helpWindow->height/2;
	      vertex[2].point[2] = cz + wallVector.z * div2;

	      vertex[3].point[0] = cx + wallVector.x * div1;
	      vertex[3].point[1] = cy + windowVector.y - helpWindow->height/2;
	      vertex[3].point[2] = cz + wallVector.z * div1;


	      glBegin(GL_LINE_LOOP);
	      {
		glVertex3fv(vertex[0].point);
		glVertex3fv(vertex[1].point);
		glVertex3fv(vertex[2].point);
		glVertex3fv(vertex[3].point);
	      }
	      glEnd();

	      if( ! helpWindow -> isLast())
		{
		  helpWindow = (LBWindow*)(helpWindow -> next);
		}
	      else
		{
		  break;
		}
	    }
	}
    }

  glPopMatrix();
}

float LField::GiveHorizontalDistance(float X, float Z){
  vector_xz VLP, VTP;
  float fDotL, fDotT;
  vector_xz Corners[4];
  
  Corners[1].x = corners[1].x;
  Corners[1].z = corners[1].z;
  Corners[3].x = corners[3].x;
  Corners[3].z = corners[3].z;
  //  printf("%f %f %f %f \n",Corners[0].x, Corners[0].z, Corners[2].x, Corners[2].z);
  
  VLP.x = X - Corners[1].x;
  VLP.z = Z - Corners[1].z;
  
  VTP.x = X - Corners[3].x;
  VTP.z = Z - Corners[3].z;
  
  
  fDotL = VLP.x*CornersN[1].x + VLP.z*CornersN[1].z;
  
  fDotT = VTP.x*CornersN[3].x + VTP.z*CornersN[3].z;
  
  //  printf("distance : %f\n", fDotL / (fDotL + fDotT));
  return ( fDotL / (fDotL + fDotT) );
}

float LField::GiveVerticalDistance(float X, float Z){
  vector_xz VLP, VTP;
  float fDotL, fDotT;
  vector_xz Corners[4];
  
  Corners[0].x = corners[1].x;
  Corners[0].z = corners[1].z;
  Corners[2].x = corners[3].x;
  Corners[2].z = corners[3].z;
  //  printf("%f %f %f %f \n",Corners[0].x, Corners[0].z, Corners[2].x, Corners[2].z);
  
  VLP.x = X - Corners[0].x;
  VLP.z = Z - Corners[0].z;
  
  VTP.x = X - Corners[2].x;
  VTP.z = Z - Corners[2].z;
  
  
  fDotL = VLP.x*CornersN[0].x + VLP.z*CornersN[0].z;
  
  fDotT = VTP.x*CornersN[2].x + VTP.z*CornersN[2].z;
  
  //  printf("distance : %f\n", fDotL / (fDotL + fDotT));
  return ( fDotL / (fDotL + fDotT) );
}


void LField::heroEnters(void){
  empty = false;
}

void LField::heroLeaves(void){
  empty = true;
}

bool
LField::isPointIn(LVector point)
{
  LVector vectorP;
  
  for(int cnt = 0; cnt < 4; cnt ++)
    {
      vectorP.x = point.x - corners[cnt].x;
      vectorP.y = 0.0f;
      vectorP.z = point.z - corners[cnt].z;
      
      if(vectorP % cornersN[cnt] < 0)
	return false;
    }
  
  return true;
}

void LField::remove()
{
  
  //actualize connected fields
  for(int cnt = 0; cnt < 4; cnt++)
    {
      if(connections[cnt])
	{
	  for(int cnt1 = 0; cnt1 < 4; cnt1++)
	    {
	      if(connections[cnt]->connections[cnt1] == this)
		connections[cnt]->connections[cnt1] = NULL;
	    }
	}
      
    }
  disconnect();
  //disallocating memory done somewhere else
}

//determinate how far from wall's corner the point is
float
LField::howFarPointIs(int wallindex, LVector point)
{
  lbmathhelper MH;

  int a,b;
  a = wallindex;

  if(a == 3)
    {
      b = 0;
    }
  else
    {
      b = a+1;
    }

  LVector temp = corners[b] - corners[a];
  LVector multiplied = LVector(0.0f, 1.0f, 0.0f);
  LVector normal1 = temp^multiplied;
  normal1.normalize();


  float pointDistance = MH.pointLineDistance(corners[a].x, corners[a].z, corners[a].x + normal1.x, corners[a].z + normal1.z, point.x, point.z);

  return pointDistance;
}

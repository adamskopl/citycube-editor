#include "field.h"
#include "floor.h"
LField::LField()
{
    walls[0] = 10.0;
    walls[1] = 10.0;
    walls[2] = 10.0;
    walls[3] = 10.0;
}

LField::~LField(){}

LField::LField(char KIND, LVector *C): kind(KIND)
{


    //walls have 0 heights
    walls[0] = 0.0f;
    walls[1] = 0.0f;
    walls[2] = 0.0f;
    walls[3] = 0.0f;

    //no connections at the beginning ...

    conn_up = NULL;
    conn_right = NULL;
    conn_down = NULL;
    conn_left = NULL;

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

char LField::giveKind(){return kind;}
void LField::setKind(char KIND){kind = KIND;}

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

    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    if(empty)
        glColor4f(0.0,0.0,0.0,1.0);
    //    glColor4f(0.85, 0.2, 0.0, 1.0);
    else
        glColor4f(1.0,0.0,0.0,1.0);
    //    glColor4f(0.2,0.2,0.2,1.0);    
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

    glBegin(GL_QUADS);
    {
	glVertex3fv(vertex[0].point);
	glVertex3fv(vertex[1].point);
	glVertex3fv(vertex[2].point);
	glVertex3fv(vertex[3].point);	
    }
    glEnd();
    glLineWidth(3.0f);
    glColor4f(0.0, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);

    for(int cnt = 0; cnt < 4; cnt++)
    {
        if( connections[cnt] )
            continue;

        int p1, p2; //indexes of vertices used for drawing wall

        p1 = cnt;
        if(p1 == 3) p2 = 0; else p2 = p1+1;

        glColor4f(0.85, 0.2, 0.0, 1.0);

        glVertex3fv(vertex[p1].point);
        glVertex3fv(vertex[p2].point);

        vertex[p1].point[1] += walls[cnt]; //wall's height
        vertex[p2].point[1] += walls[cnt];//10.0;

        glColor4f(0.0, 0.0, 0.0, 1.0);

        glVertex3fv(vertex[p2].point);
        glVertex3fv(vertex[p1].point);

        vertex[p1].point[1] -= walls[cnt];
        vertex[p2].point[1] -= walls[cnt];
    }
    glEnd();

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

void LField::ConnectUp(LField *connection, char which_passage)
{
    if (conn_up != NULL) return;
    conn_up = connection;

    switch(which_passage){
    case(F_U):{connection -> ConnectUp(this, 0);break;}
    case(F_R):{connection -> ConnectRight(this, 0);break;}
    case(F_D):{connection -> ConnectDown(this, 0);break;}
    case(F_L):{connection -> ConnectLeft(this, 0);break;}
    case(0):{return;}

    default:
        {
            //error info
        }
    }
}
void LField::ConnectRight(LField *connection, char which_passage)
{

    if (conn_right != NULL) return;
    conn_right = connection;

    switch(which_passage){
    case(F_U):{connection -> ConnectUp(this, 0);break;}
    case(F_R):{connection -> ConnectRight(this, 0);break;}
    case(F_D):{connection -> ConnectDown(this, 0);break;}
    case(F_L):{connection -> ConnectLeft(this, 0);break;}
    case(0):{return;}

    default:
        {
            //error
        }

    }


}
void LField::ConnectDown(LField *connection, char which_passage)
{
    if (conn_down != NULL) return;
    conn_down = connection;

    switch(which_passage){
    case(F_U):{connection -> ConnectUp(this, 0);break;}
    case(F_R):{connection -> ConnectRight(this, 0);break;}
    case(F_D):{connection -> ConnectDown(this, 0);break;}
    case(F_L):{connection -> ConnectLeft(this, 0);break;}
    case(0):{return;}

    default:
        {
            //error
        }
    }

}
void LField::ConnectLeft(LField *connection, char which_passage)
{
    if (conn_left != NULL) return;
    conn_left = connection;

    switch(which_passage){
    case(F_U):{connection -> ConnectUp(this, 0);break;}
    case(F_R):{connection -> ConnectRight(this, 0);break;}
    case(F_D):{connection -> ConnectDown(this, 0);break;}
    case(F_L):{connection -> ConnectLeft(this, 0);break;}
    case(0):{return;}

    default:
        {
            //error
        }
    }
}

void LField::ConnectUp(LField *connection)
{
    conn_up = connection;
}
void LField::ConnectRight(LField *connection)
{
    conn_right = connection;
}
void LField::ConnectDown(LField *connection)
{
    conn_down = connection;
}
void LField::ConnectLeft(LField *connection)
{
    conn_left = connection;
}

char LField::Passage(char code)//F_U, F_R ...
{

    if(kind & code)
        return 0;
    else
        return 1;

}

LField * LField::giveUp(){
    //  if(conn_up == NULL)LError("giving non-existing connection ! up");

    return conn_up;
}
LField * LField::giveRight(){
    //  if(conn_right == NULL)LError("giving non-existing connection ! right");

    return conn_right;
}
LField * LField::giveDown(){
    //  if(conn_down == NULL)LError("giving non-existing connection ! down");

    return conn_down;
}
LField * LField::giveLeft(){
    //  if(conn_left == NULL)LError("giving non-existing connection ! left");

    return conn_left;
}

/*void LField::DrawMini(){
  //PUSH MATRIX NEEDED ???
  glPushMatrix();

  OnDrawMini();
  if (hasChild())
    ((LField*)child)->DrawMini();
  glPopMatrix();
  
  
  if (hasParent() && !isLast())
    ((LField*)next)->DrawMini();

}

void LField::OnDrawMini(){
  /*
  glColor4f(0.0,1.0,0.0,1.0);

  //map will be static, so count everything in constructor
  
  glBegin(GL_LINES);
      for(int a = 0, x = 8; a < 4; a++, x /= 2)
	if(kind & x){
	  switch(a){
	  case 0:{

	    glVertex3f(corners[0].x/10*8.82+500, corners[0].z/10*8.82,0.0);
	    glVertex3f(corners[1].x/10*8.82+500, corners[1].z/10*8.82,0.0);	    

	    break;}
	  case 1:{

	    glVertex3f(corners[1].x/10*8.82+500, corners[1].z/10*8.82,0.0);
	    glVertex3f(corners[2].x/10*8.82+500, corners[2].z/10*8.82,0.0);	    

	    break;}
	  case 2:{

	    glVertex3f(corners[2].x/10*8.82+500, corners[2].z/10*8.82,0.0);
	    glVertex3f(corners[3].x/10*8.82+500, corners[3].z/10*8.82,0.0);	    

	    break;}
	  case 3:{

	    glVertex3f(corners[3].x/10*8.82+500, corners[3].z/10*8.82,0.0);
	    glVertex3f(corners[0].x/10*8.82+500, corners[0].z/10*8.82,0.0);	    
	    
	    break;}
	  }
	}//draw wall
      glEnd();
  */

    /*
  glLineWidth(0.8);
  glBegin(GL_LINE_STRIP);
  glVertex3f(corners[0].x+500, corners[0].z,0.0);
  glVertex3f(corners[1].x+500, corners[1].z,0.0);
  glVertex3f(corners[2].x+500, corners[2].z,0.0);
  glVertex3f(corners[3].x+500, corners[3].z,0.0);
  glVertex3f(corners[0].x+500, corners[0].z,0.0);  
  glEnd();*/

    //}

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

    bool
            LField::connectionExists(LField *connection)
    {
        //check if any vector has a mirror image in connection
        for(int cnt = 0; cnt < 4; cnt++)
        {
            for(int cnt1 = 0; cnt1 < 4; cnt1++)
            {
                if(vectors[cnt] == -(connection->vectors[cnt1]))
                    return true;
            }
        }
        return false;
    }

    bool
            LField::connectTo(LField *connection)
    {
        int a1, a2, b1, b2;


        for(int cnt = 0; cnt < 4; cnt++)
        {
            a1 = cnt;
            if(cnt == 3) a2 = 0; else a2 = a1 + 1;

            for(int cnt1 = 0; cnt1 < 4; cnt1++)
            {
                b1 = cnt1;
                if(cnt1 == 3) b2 = 0; else b2 = b1 + 1;

                //check if any wall has a mirror image in 'connection'
                if(corners[a1] == connection -> corners[b2] &&
                   corners[a2] == connection -> corners[b1])
                {

                    //connect them and return
                    connections[cnt] = connection;

                    //hmm .. maybe a function, that would be doing connections,
                    //would be a better idea - and connections should be private
                    connection -> connections[cnt1] = this;

                    return true;
                }
            }
        }

        //failure
        return false;
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

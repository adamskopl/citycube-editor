#include "field.h"

EField::EField(){}

EField::EField(char KIND,CORNERS *C): kind(KIND)
{
  //no connections at the beginning ...
  conn_up = NULL;
  conn_right = NULL;
  conn_down = NULL;
  conn_left = NULL;


  up = 0;
  right = 0;
  down = 0;
  left = 0;
  
  empty = true;
  corners = *C;


  float dx, dz, length;
  //   calculating normals ...
  //up
  dz = C -> a.z - C -> b.z;
  dx = C -> b.x - C -> a.x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[0].x = dz / length;
  CornersN[0].z = dx / length;
  /*  printf("UP : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[0].x, CornersN[0].z);*/
  //right
  dz = C -> b.z - C -> c.z;
  dx = C -> c.x - C -> b.x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[1].x = dz / length;
  CornersN[1].z = dx / length;
  /*  printf("RIGHT : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[1].x, CornersN[1].z);*/

  //down
  dz = C -> c.z - C -> d.z;
  dx = C -> d.x - C -> c.x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[2].x = dz / length;
  CornersN[2].z = dx / length;
  /*  printf("DOWN : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[2].x, CornersN[2].z);*/

  //left
  dz = C -> d.z - C -> a.z;
  dx = C -> a.x - C -> d.x;
  length = sqrt(dz*dz + dx*dx);
  CornersN[3].x = dz / length;
  CornersN[3].z = dx / length;
  /*  printf("LEFT : length : %f, Nx : %f, Nz: %f \n",
      length, CornersN[3].x, CornersN[3].z);*/
  
  
}

char EField::giveKind(){return kind;}
void EField::setKind(char KIND){kind = KIND;}

//char EField::giveX(){return x;}
//char EField::giveY(){return y;}

void EField::Draw(){

  glPushMatrix();
  OnDraw();
  if (HasChild())
    ((EField*)childNode)->Draw();
  glPopMatrix();
  
  
  if (HasParent() && !IsLastChild())
    ((EField*)nextNode)->Draw();

}

void EField::OnDraw(){
  glPushMatrix();

  if(empty)
    glColor4f(0.0,0.0,0.0,1.0);
    //    glColor4f(0.85, 0.2, 0.0, 1.0);
  else
    glColor4f(0.0,0.0,0.0,1.0);
    //    glColor4f(0.2,0.2,0.2,1.0);    
    vector_t vertex[4];
      
      vertex[0].point[0] = corners.a.x;
      vertex[0].point[1] = corners.a.y;
      vertex[0].point[2] = corners.a.z;

      vertex[1].point[0] = corners.b.x;
      vertex[1].point[1] = corners.b.y;
      vertex[1].point[2] = corners.b.z;

      vertex[2].point[0] = corners.c.x;
      vertex[2].point[1] = corners.c.y;
      vertex[2].point[2] = corners.c.z;

      vertex[3].point[0] = corners.d.x;
      vertex[3].point[1] = corners.d.y;
      vertex[3].point[2] = corners.d.z;

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
      glShadeModel(GL_SMOOTH);
      for(int a = 0, x = 8; a < 4; a++, x /= 2)
	if(kind & x){
	  switch(a){
	  case 0:{
	    glColor4f(1.0, 1.0, 0.0, 1.0);
	    glVertex3fv(vertex[0].point);
	    glVertex3fv(vertex[1].point);

	    vertex[0].point[1] += 10.0;
	    vertex[1].point[1] += 10.0;	    
	    glColor4f(0.85, 0.2, 0.0, 1.0);
	    glVertex3fv(vertex[1].point);
	    glVertex3fv(vertex[0].point);

	    vertex[0].point[1] -= 10.0;
	    vertex[1].point[1] -= 10.0;	    
	    
	    break;}
	  case 1:{
	    glColor4f(1.0, 1.0, 0.0, 1.0);
	    glVertex3fv(vertex[1].point);
	    glVertex3fv(vertex[2].point);

	    vertex[1].point[1] += 10.0;
	    vertex[2].point[1] += 10.0;	    
	    glColor4f(0.85, 0.2, 0.0, 1.0);
	    glVertex3fv(vertex[2].point);
	    glVertex3fv(vertex[1].point);

	    vertex[1].point[1] -= 10.0;
	    vertex[2].point[1] -= 10.0;	    
	    
	    break;}
	  case 2:{
	    glColor4f(1.0,1.0,0.0,1.0);
	    glVertex3fv(vertex[2].point);
	    glVertex3fv(vertex[3].point);


	    vertex[2].point[1] += 10.0;
	    vertex[3].point[1] += 10.0;	    

	    glColor4f(0.85, 0.2, 0.0, 1.0);
	    glVertex3fv(vertex[3].point);
	    glVertex3fv(vertex[2].point);

	    vertex[2].point[1] -= 10.0;
	    vertex[3].point[1] -= 10.0;	    
	    
	    break;}
	  case 3:{
	    glColor4f(1.0,1.0,0.0,1.0);
	    glVertex3fv(vertex[3].point);
	    glVertex3fv(vertex[0].point);


	    vertex[3].point[1] += 10.0;
	    vertex[0].point[1] += 10.0;	    

	    glColor4f(0.85, 0.2, 0.0, 1.0);
	    glVertex3fv(vertex[0].point);
	    glVertex3fv(vertex[3].point);

	    vertex[3].point[1] -= 10.0;
	    vertex[0].point[1] -= 10.0;	    
	    
	    break;}
	  }
	}//draw wall
      glEnd();
      
      glPopMatrix();

}

float EField::GiveHorizontalDistance(float X, float Z){
  vector_xz VLP, VTP;
  float fDotL, fDotT;

  Corners[1].x = corners. b.x;
  Corners[1].z = corners. b.z;
  Corners[3].x = corners. d.x;
  Corners[3].z = corners. d.z;
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

float EField::GiveVerticalDistance(float X, float Z){
  vector_xz VLP, VTP;
  float fDotL, fDotT;

  Corners[0].x = corners. b.x;
  Corners[0].z = corners. b.z;
  Corners[2].x = corners. d.x;
  Corners[2].z = corners. d.z;
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


void EField::heroEnters(void){
  empty = false;
}

void EField::heroLeaves(void){
  empty = true;
}

void EField::ConnectUp(EField *connection, char which_passage)
{
  if (conn_up != NULL) return;
  conn_up = connection;
  up = connection -> index;

  
  switch(which_passage){
  case(F_U):{connection -> ConnectUp(this, 0);break;}
  case(F_R):{connection -> ConnectRight(this, 0);break;}
  case(F_D):{connection -> ConnectDown(this, 0);break;}
  case(F_L):{connection -> ConnectLeft(this, 0);break;}
  case(0):{return;}

  default: EError("which_passage wrong value !");
  }
}
void EField::ConnectRight(EField *connection, char which_passage)
{

  if (conn_right != NULL) return;
  conn_right = connection;
  right = connection -> index;
  
  switch(which_passage){
  case(F_U):{connection -> ConnectUp(this, 0);break;}
  case(F_R):{connection -> ConnectRight(this, 0);break;}
  case(F_D):{connection -> ConnectDown(this, 0);break;}
  case(F_L):{connection -> ConnectLeft(this, 0);break;}
  case(0):{return;}

  default: EError("which_passage wrong value !");
  }


}
void EField::ConnectDown(EField *connection, char which_passage)
{
  if (conn_down != NULL) return;
  conn_down = connection;
  down = connection -> index;
  
  switch(which_passage){
  case(F_U):{connection -> ConnectUp(this, 0);break;}
  case(F_R):{connection -> ConnectRight(this, 0);break;}
  case(F_D):{connection -> ConnectDown(this, 0);break;}
  case(F_L):{connection -> ConnectLeft(this, 0);break;}
  case(0):{return;}

  default: EError("which_passage wrong value !");
  }

}
void EField::ConnectLeft(EField *connection, char which_passage)
{
  if (conn_left != NULL) return;
  conn_left = connection;
  left = connection -> index;
  
  switch(which_passage){
  case(F_U):{connection -> ConnectUp(this, 0);break;}
  case(F_R):{connection -> ConnectRight(this, 0);break;}
  case(F_D):{connection -> ConnectDown(this, 0);break;}
  case(F_L):{connection -> ConnectLeft(this, 0);break;}
  case(0):{return;}

  default: EError("which_passage wrong value !");
  }
}

char EField::Passage(char code)//F_U, F_R ...
{

  if(kind & code)
    return 0;
  else
    return 1;

}

EField * EField::giveUp(){
  //  if(conn_up == NULL)EError("giving non-existing connection ! up");
  
  return conn_up;
}
EField * EField::giveRight(){
  //  if(conn_right == NULL)EError("giving non-existing connection ! right");
  
  return conn_right;
}
EField * EField::giveDown(){
  //  if(conn_down == NULL)EError("giving non-existing connection ! down");
  
  return conn_down;
}
EField * EField::giveLeft(){
  //  if(conn_left == NULL)EError("giving non-existing connection ! left");
  
  return conn_left;
}

void EField::DrawMini(){
  //PUSH MATRIX NEEDED ???
  glPushMatrix();

  OnDrawMini();
  if (HasChild())
    ((EField*)childNode)->DrawMini();
  glPopMatrix();
  
  
  if (HasParent() && !IsLastChild())
    ((EField*)nextNode)->DrawMini();

}

void EField::OnDrawMini(){
  glColor4f(0.0,1.0,0.0,1.0);

  //map will be static, so count everything in constructor
  
  glBegin(GL_LINES);
      for(int a = 0, x = 8; a < 4; a++, x /= 2)
	if(kind & x){
	  switch(a){
	  case 0:{

	    glVertex3f(corners.a.x/10*8.82+500, corners.a.z/10*8.82,0.0);
	    glVertex3f(corners.b.x/10*8.82+500, corners.b.z/10*8.82,0.0);	    

	    break;}
	  case 1:{

	    glVertex3f(corners.b.x/10*8.82+500, corners.b.z/10*8.82,0.0);
	    glVertex3f(corners.c.x/10*8.82+500, corners.c.z/10*8.82,0.0);	    

	    break;}
	  case 2:{

	    glVertex3f(corners.c.x/10*8.82+500, corners.c.z/10*8.82,0.0);
	    glVertex3f(corners.d.x/10*8.82+500, corners.d.z/10*8.82,0.0);	    

	    break;}
	  case 3:{

	    glVertex3f(corners.d.x/10*8.82+500, corners.d.z/10*8.82,0.0);
	    glVertex3f(corners.a.x/10*8.82+500, corners.a.z/10*8.82,0.0);	    
	    
	    break;}
	  }
	}//draw wall
      glEnd();


  /*
  glLineWidth(0.8);
  glBegin(GL_LINE_STRIP);
  glVertex3f(corners.a.x+500, corners.a.z,0.0);
  glVertex3f(corners.b.x+500, corners.b.z,0.0);
  glVertex3f(corners.c.x+500, corners.c.z,0.0);
  glVertex3f(corners.d.x+500, corners.d.z,0.0);
  glVertex3f(corners.a.x+500, corners.a.z,0.0);  
  glEnd();*/

}

void EField::Disconnect(char what)
{
  switch(what){
  case(F_U):{conn_up = NULL;}
    break;
  case(F_R):{conn_right = NULL;}
    break;
  case(F_D):{conn_down = NULL;}
    break;
  case(F_L):{conn_left = NULL;}
    break;

  }

}

#include <gl/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
const GLfloat Pi=3.1415926;
const int n=10;
const int m=5;
GLint isFlag=1;
GLint isPoints=1;
GLfloat Star[10][3];
GLfloat rOut = 0.5;
GLfloat xRot=0.0f,yRot=0.0f,zRot=90.0f;
GLfloat angle = 0.0f;
GLint startRotate=0;
GLint enableTimer=1;
//五角星内点外点
void pointsStar()
{
  GLfloat size= 5.0f;
  glPointSize(size);
  glBegin(GL_POINTS);
	  glPointSize(3.0f);
	  glVertex3f(0.0f,0.0f,0.0f);
	  for(int i=0;i<10;i++)
	  {
	      glColor3f(1.0f,i/5.0f,1.0f-i/5.0f);
		  glVertex3fv(Star[i]); 
	  }
  glEnd();
  
}
//直连线框五星红旗
void directLineStar(void)
{ GLfloat PointStar[5][3]={{0.5f,0.0f,0.0f}};
  glColor3f(1.0f,0.0f,0.0f);
  glLineWidth(3.0f);
  for(int i=1;i<m;i++)
  {
	  PointStar[i][0]=rOut*cos(2*Pi/m*i);
      PointStar[i][1]=rOut*sin(2*Pi/m*i);
      PointStar[i][2]=0.0f;
  }
  glClear(GL_COLOR_BUFFER_BIT); 
  glBegin(GL_LINE_LOOP);
  glVertex3fv(PointStar[0]); 
  glVertex3fv(PointStar[2]); 
  glVertex3fv(PointStar[4]); 
  glVertex3fv(PointStar[1]); 
  glVertex3fv(PointStar[3]); 
  glEnd(); 
  if(isPoints) pointsStar();
}
//彩色五角星
void colorStar()
{
  for(int i= 1;i<n;i+=2)
  {
	  glBegin(GL_POLYGON);
	    glColor3f((GLfloat)i/n,1.0,(GLfloat)(n-i)/n);
		glVertex3f(0.0f,0.0f,0.0f);	    
		glColor3f(1.0,1.0,(GLfloat)(n-i)/n);
		glVertex3fv(Star[i]);
		glColor3f(1.0,(GLfloat)i/n,(GLfloat)(n-i)/n);
		glVertex3fv(Star[(i+1)%n]);
	    glColor3f((GLfloat)i/n,1.0,1.0);
		glVertex3fv(Star[(i+2)%n]);
	  glEnd();
  }
  if(isPoints) pointsStar();
}

//线框和多边形
void wireOrPolygonStar()
{
  glColor3f(1.0f,0.0f,0.0f);
  if(isFlag==3)
  glBegin(GL_LINE_LOOP);
  if(isFlag==4)
    glBegin(GL_POLYGON);
  for(int i=0;i<10;i++)
  {	//glColor3f((GLfloat)i/10,1.0,(GLfloat)(n-i)/n);
		glVertex3fv(Star[(i+1)%10]);
  }
  glEnd(); 
  if(isPoints) pointsStar();
}

//五角星窗体显示回调函数
void display(void)
{ glColor3f(1.0f,0.0f,0.0f);
  GLfloat rIn=(rOut*cos(2*Pi/5))/cos(2*Pi/n);
  for(int i=0;i<10;i+=2)
  {
	  Star[i][0]=rOut*cos(2*Pi/5*i/2);
      Star[i][1]=rOut*sin(2*Pi/5*i/2);
	  Star[i][2]=0.0f;
	  Star[i+1][0]=rIn*cos(2*Pi/5*i/2+2*Pi/n);
      Star[i+1][1]=rIn*sin(2*Pi/5*i/2+2*Pi/n);
	  Star[i+1][2]=0.0f;
  }
  glClear(GL_COLOR_BUFFER_BIT); 
  glPushMatrix();
  glRotatef(xRot,1.0f,0.0f,0.0f);
  glRotatef(yRot,0.0f,1.0f,0.0f);
  glRotatef(zRot,0.0f,0.0f,1.0f);
  glLineWidth(2.0f);
  switch(isFlag)
  {
  case 1:
	  directLineStar(); break;
  case 2:
	  colorStar();break;
  case 3: case 4:
	  wireOrPolygonStar();break;
  case 5:
	  pointsStar(); break;
  default:
      colorStar();break;
  }
  glPopMatrix();
  glFlush(); 
}

//视口和投影变换
void reshape(GLint w, GLint h)
{  GLfloat range=1.0f;
   if(h<=0) h =1;
   GLfloat ratio = (GLfloat)w/(GLfloat)h;
   glViewport(0,0,w,h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if(w>h)
	   glOrtho(-range*ratio,ratio,-range,range,-range,range);
   else
	   glOrtho(-range,range,-range/ratio,range/ratio,-range,range);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}
void menuFunc(int value)
{
	isFlag = value;
	glutPostRedisplay();
}
void subMenuFunc(int value)
{
	isPoints = value;
	glutPostRedisplay();
}
void keyboardProcess(unsigned char key,int x,int y)
{
	isFlag = key-48;
	glutPostRedisplay();
}
void keySpecialProcess(int key,int x, int y )
{
    angle=2.0;
	switch(key)
	{
	case GLUT_KEY_LEFT:
		xRot+=angle;break;
	case GLUT_KEY_RIGHT:
		xRot-=angle;break;
	case GLUT_KEY_UP:
		yRot+=angle;break;
	case GLUT_KEY_DOWN:
		yRot-=angle;break;
	case GLUT_KEY_PAGE_UP:
		zRot+=angle;break;
	case GLUT_KEY_PAGE_DOWN:
		zRot-=angle;break;
	}
	if(xRot>360) xRot-=360.0f;
    if(xRot<=0) xRot=360.0f;
	if(yRot>360) yRot-=360.0f;
    if(yRot<=0) yRot=360.0f;
	if(zRot>360) zRot-=360.0f;
    if(zRot<=0) zRot=360.0f;
	glutPostRedisplay();
}

void idleRotate()
{
	zRot+=5.0f;
	if(zRot>360.0f) zRot-=360.0f;
	glutPostRedisplay();
}

void timerRotate(int value)
{
	yRot+=5.0f;
	if(yRot>360.0f) yRot-=360.0f;
	glutPostRedisplay();
	printf("%d",value);
	if(enableTimer)
       glutTimerFunc(50,timerRotate,1);
}

void mouseProcess(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON)   //启动
    	if(state==GLUT_DOWN)
		{	glutIdleFunc(idleRotate);
		    glutTimerFunc(50,timerRotate,0);}
	if(button == GLUT_MIDDLE_BUTTON) //停止
		if(state==GLUT_DOWN)
		{	glutIdleFunc(NULL);
		    enableTimer = 0;
		}
}

void main(int argc, char *argv[])
{
  int mainMenuHandle, subMenuHandle;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowPosition(300,100);
  glutInitWindowSize(500,500);
  glutCreateWindow("2D图形");
  
  subMenuHandle = glutCreateMenu(subMenuFunc);
  glutAddMenuEntry("角点开",1);
  glutAddMenuEntry("角点关",0);
  
  mainMenuHandle= glutCreateMenu(menuFunc);
  glutAddMenuEntry("直连线框五角星",1);
  glutAddMenuEntry("彩色五角星",2);
  glutAddMenuEntry("空心五角星",3);
  glutAddMenuEntry("实心五角星",4);
  glutAddMenuEntry("单独显示角点",5);

  glutAddSubMenu("角点开关",subMenuHandle);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutKeyboardFunc(keyboardProcess);
  glutSpecialFunc(keySpecialProcess);

  glutMouseFunc(mouseProcess);
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

}
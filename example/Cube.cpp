#include <GL/glut.h>
void disp()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(30,1,1,1);
    glutWireCube(0.8);
//	glutSolidCube(0.8);
	glFlush();
}
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
   glutInitWindowPosition(300,100);
   glutInitWindowSize(500,500);
   glutCreateWindow("Test");
   glutDisplayFunc(&disp);
   glutMainLoop();
    return 0;
}

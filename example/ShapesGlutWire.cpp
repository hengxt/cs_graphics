#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static int iShape = 1;

///////////////////////////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value)
{
    iShape = value;

	glutPostRedisplay();
}


// Called to draw scene
void RenderScene(void)
	{
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    switch(iShape)
        {
        case 1:
            glutWireSphere(1.0f, 25, 25);
            break;

        case 2:
            glutWireCube(1.0f);
            break;

        case 3:
            glutWireCone(0.30f, 1.1f, 20, 20);
            break;

        case 4:
            glutWireTorus(0.3f, 1.0f, 10, 25);
            break;

        case 5:
            glutWireDodecahedron();
            break;

        case 6:
            glutWireOctahedron();
            break;

        case 7:
            glutWireTetrahedron();
            break;

        case 8:
            glutWireIcosahedron();
            break;

        case 9:
            glutWireTeapot(1.0f);
            break;

        }


	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

	// Set drawing color to blue
	glColor3ub(50, 255, 255);
	}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	// Refresh the Window
	glutPostRedisplay();
	}

void ChangeSize(int w, int h)
	{
	GLfloat nRange = 1.9f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

int main(int argc, char* argv[])
	{
	int nSolidMenu;
	int nWireMenu;
	int nMainMenu;
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GLUT Shapes");
	
	// Create the Menu
	nWireMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Sphere",1);
	glutAddMenuEntry("Cube",2);
	glutAddMenuEntry("Cone",3);
	glutAddMenuEntry("Torus",4);
	glutAddMenuEntry("Dodecahedron",5);
	glutAddMenuEntry("Octahedron",6);
	glutAddMenuEntry("Tetrahedron",7);
	glutAddMenuEntry("Icosahedron",8);
	glutAddMenuEntry("Teapot",9);

//	nMainMenu = glutCreateMenu(ProcessMenu);
//	glutAddSubMenu("Wire", nWireMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}

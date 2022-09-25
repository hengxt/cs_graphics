#include <GL/glut.h>
#include<cmath>

using namespace std;

const GLfloat Pi = 3.1415926;
const int n = 10;
const int m = 5;
GLint isFlag = 1;
GLint isPoints = 1;
GLfloat Star[10][3];
GLfloat rOut = 0.5;
GLfloat xRot = 0.0f, yRot = 0.0f, zRot = 90.0f;
GLfloat angle = 0.0f;
GLint enableTimer = 1;

//五角星内点外点
void pointsStar() {
    GLfloat size = 5.0f;
    glPointSize(size);
    glBegin(GL_POINTS);
    glPointSize(3.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 10; i++) {
        glColor3f(1.0f, (float) i / 5.0f, 1.0f - (float) i / 5.0f);
        glVertex3fv(Star[i]);
    }
    glEnd();

}

//直连线框五星红旗
void directLineStar() {
    GLfloat PointStar[5][3] = {{0.5f, 0.0f, 0.0f}};
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    for (int i = 1; i < m; i++) {
        auto ii = (float) i;
        PointStar[i][0] = rOut * cos(2 * Pi / m * ii);
        PointStar[i][1] = rOut * sin(2 * Pi / m * ii);
        PointStar[i][2] = 0.0f;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(PointStar[0]);
    glVertex3fv(PointStar[2]);
    glVertex3fv(PointStar[4]);
    glVertex3fv(PointStar[1]);
    glVertex3fv(PointStar[3]);
    glEnd();
    if (isPoints) pointsStar();
}

//彩色五角星
void colorStar() {
    for (int i = 1; i < n; i += 2) {
        glBegin(GL_POLYGON);
        glColor3f((GLfloat) i / n, 1.0, (GLfloat) (n - i) / n);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(1.0, 1.0, (GLfloat) (n - i) / n);
        glVertex3fv(Star[i]);
        glColor3f(1.0, (GLfloat) i / n, (GLfloat) (n - i) / n);
        glVertex3fv(Star[(i + 1) % n]);
        glColor3f((GLfloat) i / n, 1.0, 1.0);
        glVertex3fv(Star[(i + 2) % n]);
        glEnd();
    }
    if (isPoints) pointsStar();
}

//线框和多边形
void wireOrPolygonStar() {
    glColor3f(1.0f, 0.0f, 0.0f);
    if (isFlag == 3)
        glBegin(GL_LINE_LOOP);
    if (isFlag == 4)
        glBegin(GL_POLYGON);
    for (int i = 0; i < 10; i++) {    //glColor3f((GLfloat)i/10,1.0,(GLfloat)(n-i)/n);
        glVertex3fv(Star[(i + 1) % 10]);
    }
    glEnd();
    if (isPoints) pointsStar();
}

///// 主控视图
void display() {
    glColor3f(1.0f, 0.0f, 0.0f);
    GLfloat rIn = (rOut * cos(2 * Pi / 5)) / cos(2 * Pi / n);
    for (int i = 0; i < 10; i += 2) {
        auto ii = (float) i;
        Star[i][0] = rOut * cos(2 * Pi / 5 * ii / 2);
        Star[i][1] = rOut * sin(2 * Pi / 5 * ii / 2);
        Star[i][2] = 0.0f;
        Star[i + 1][0] = rIn * cos(2 * Pi / 5 * ii / 2 + 2 * Pi / n);
        Star[i + 1][1] = rIn * sin(2 * Pi / 5 * ii / 2 + 2 * Pi / n);
        Star[i + 1][2] = 0.0f;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glLineWidth(2.0f);
    switch (isFlag) {
        case 1:
            directLineStar();
            break;
        case 2:
            colorStar();
            break;
        case 3:
        case 4:
            wireOrPolygonStar();
            break;
        case 5:
            pointsStar();
            break;

        case 21:
            glutWireSphere(1.0f, 25, 25);
            break;
        case 22:
            glutWireCube(1.0f);
            break;
        case 23:
            glutWireCone(0.30f, 1.1f, 20, 20);
            break;
        case 24:
            glutWireTorus(0.3f, 1.0f, 10, 25);
            break;
        case 25:
            glutWireDodecahedron();
            break;
        case 26:
            glutWireOctahedron();
            break;
        case 27:
            glutWireTetrahedron();
            break;
        case 28:
            glutWireIcosahedron();
            break;
        case 29:
            glutWireTeapot(1.0f);
            break;

        default:
            colorStar();
            break;
    }
    glPopMatrix();
    glFlush();
}

//视口和投影变换
void reshape(int w, int h) {
    GLfloat nRange = 1.9f;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset projection matrix stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    auto ww = (float) w;
    auto hh = (float) h;
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * hh / ww,
                nRange * hh / ww, -nRange, nRange);
    else
        glOrtho(-nRange * ww / hh, nRange * ww / hh, -nRange,
                nRange, -nRange, nRange);

    // Reset Model view matrix stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// 菜单控制
void menuFunc(int value) {
    isFlag = value;
    glutPostRedisplay();
}

void subMenuFunc(int value) {
    isPoints = value;
    glutPostRedisplay();
}

// 键盘控制
void keyboardProcess(unsigned char key, __attribute__((unused)) int x, __attribute__((unused)) int y) {
    isFlag = key - 48;
    glutPostRedisplay();
}

void keySpecialProcess(int key, __attribute__((unused))int x, __attribute__((unused))int y) {
    angle = 2.0;
    switch (key) {
        case GLUT_KEY_LEFT:
            yRot -= angle; // 左
            break;
        case GLUT_KEY_RIGHT:
            yRot += angle; // 右
            break;
        case GLUT_KEY_UP:
            xRot -= angle;  // 上
            break;
        case GLUT_KEY_DOWN:
            xRot += angle; // 下
            break;
        case GLUT_KEY_PAGE_UP:
            zRot += angle;
            break;
        case GLUT_KEY_PAGE_DOWN:
            zRot -= angle;
            break;
        case GLUT_KEY_F5:
            xRot = 0.0f, yRot = 0.0f, zRot = 90.0f;
            break;
        default:
            break;
    }
    if (xRot > 360) xRot -= 360.0f;
    if (xRot <= 0) xRot = 360.0f;
    if (yRot > 360) yRot -= 360.0f;
    if (yRot <= 0) yRot = 360.0f;
    if (zRot > 360) zRot -= 360.0f;
    if (zRot <= 0) zRot = 360.0f;
    glutPostRedisplay();
}

// 鼠标动画
void idleRotate() {
    zRot += 5.0f;
    if (zRot > 360.0f) zRot -= 360.0f;
    glutPostRedisplay();
}

void timerRotate(__attribute__((unused))int value) {
    yRot += 5.0f;
    if (yRot > 360.0f) yRot -= 360.0f;
    glutPostRedisplay();
//    printf("%d", value);
    if (enableTimer)
        glutTimerFunc(50, timerRotate, 1);
}

void mouseProcess(int button, int state,
                  __attribute__((unused))int x, __attribute__((unused))int y) {
    if (button == GLUT_LEFT_BUTTON)   //启动
        if (state == GLUT_DOWN) {
            glutIdleFunc(idleRotate);
            glutTimerFunc(50, timerRotate, 0);
        }
    if (button == GLUT_MIDDLE_BUTTON) //停止
        if (state == GLUT_DOWN) {
            glutIdleFunc(nullptr);
            enableTimer = 0;
        }
}

// 绘制标题栏
void createGLUTMenu() {
    int sub1MenuHandle,sub2MenuHandle, nWireMenu;
    sub2MenuHandle = glutCreateMenu(subMenuFunc);
    glutAddMenuEntry("open", 1);
    glutAddMenuEntry("close", 0);

    sub1MenuHandle = glutCreateMenu(menuFunc);
    glutAddMenuEntry("directWireframe", 1);
    glutAddMenuEntry("multicolor", 2);
    glutAddMenuEntry("hollow", 3);
    glutAddMenuEntry("solid", 4);
    glutAddMenuEntry("displayCornersIndividually", 5);
    glutAddSubMenu("point", sub2MenuHandle);

    nWireMenu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Sphere", 21);
    glutAddMenuEntry("Cube", 22);
    glutAddMenuEntry("Cone", 23);
    glutAddMenuEntry("Torus", 24);
    glutAddMenuEntry("Dodecahedron", 25);
    glutAddMenuEntry("Octahedron", 26);
    glutAddMenuEntry("Tetrahedron", 27);
    glutAddMenuEntry("Icosahedron", 28);
    glutAddMenuEntry("Teapot", 29);

    __attribute__((unused)) int mainMenuHandle = glutCreateMenu(menuFunc);
    glutAddSubMenu("pentagram", sub1MenuHandle);
    glutAddSubMenu("wire", nWireMenu);
}

// 主入口
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(300, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2020010661_hxt");

    // 绘制菜单
    createGLUTMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // 键盘鼠标映射
    glutKeyboardFunc(keyboardProcess);
    glutSpecialFunc(keySpecialProcess);

    glutMouseFunc(mouseProcess);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
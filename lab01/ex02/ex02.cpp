#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.0, 1.0, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLES);
	glVertex2i(160, 80);
	glVertex2i(480, 80);
	glVertex2i(320, 400);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 0.0, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(5.0);

	glBegin(GL_TRIANGLES);
	glVertex2i(160, 80);
	glVertex2i(480, 80);
	glVertex2i(320, 400);
	glEnd();

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

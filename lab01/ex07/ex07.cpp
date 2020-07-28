
#include "..\lab01\Dependencies\glew\glew.h"
#include "..\lab01\Dependencies\freeglut\freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawRectangle(GLint x, GLint y, GLint width, GLint height)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2i(x, y);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x + width, y);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(x + width, y + height);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x, y + height);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLint w = 400, h = 200;
	GLint x = (screenWidth - w) / 2;
	GLint y = (screenHeight - h) / 2;
	drawRectangle(x, y, w, h);

	glFlush();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
}

int main(int agrc, char** argv)
{
	glutInit(&agrc, argv);
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



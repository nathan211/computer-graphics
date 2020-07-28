#include "..\lab01\Dependencies\glew\glew.h"
#include "..\lab01\Dependencies\freeglut\freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawSquare(GLint x, GLint y, GLint a)
{
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + a, y);
	glVertex2i(x + a, y + a);
	glVertex2i(x, y + a);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLint size = 200;
	GLint x = (screenWidth - size) / 2; // 220
	GLint y = (screenHeight - size) / 2; // 140
	drawSquare(x, y, size);

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



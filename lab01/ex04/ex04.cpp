#include "..\lab01\Dependencies\glew\glew.h"
#include "..\lab01\Dependencies\freeglut\freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void triangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0); // red
	glVertex2i(150, 150);
	glColor3f(0.0, 1.0, 0.0); // green
	glVertex2i(350, 150);
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex2i(250, 350);
	glEnd();

	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	triangle();
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



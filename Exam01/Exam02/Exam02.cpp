#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

int i = 0;

void DisplayFunc(void) {
	static float alpha = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 0, -10);
	glRotatef(30, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);

	glBegin(GL_QUADS);

	glColor3f(1, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0); glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, -1);

	glColor3f(0, 1, 0); glVertex3f(1, -1, -1);
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 1, 0); glVertex3f(1, 1, 1);
	glColor3f(0, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 1); glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1); glVertex3f(1, -1, -1);

	glColor3f(1, 1, 0); glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(1, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, -1);

	glColor3f(0, 1, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, -1, 1);

	glEnd();


	if (alpha >= 720) 
		i = 1;
	if(i == 0)
		alpha = alpha + 0.3;
	else
		alpha = alpha - 0.3;

	glFlush();
	glutSwapBuffers();

	glutPostRedisplay();
}

void ReshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(20, width / (float)height, 5, 15);
	glViewport(width/3, height/3, 150, 150);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	int foo;
	foo = x + y;
	if ('q' == key || 'Q' == key || 27 == key)
		exit(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spinning cube");

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);


	glutMainLoop();

	return 0;
}
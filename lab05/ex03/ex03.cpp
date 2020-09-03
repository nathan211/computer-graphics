#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#ifdef _MSC_VER /* for MSVC */
# pragma comment (lib, "opengl32.lib")
# pragma comment (lib, "glu32.lib")
# pragma comment (lib, "glew32.lib")
# pragma comment (lib, "freeglut.lib")
#endif
#define WND_WIDTH 640 /* chiều rộng cửa sổ */
#define WND_HEIGHT 360 /* chiều cao cửa sổ */
#define WND_TITLE "Lab05-3" /* tiêu đề cửa sổ */
#define VS_FILE "vertex3.glsl" /* tập tin mã nguồn vertex shader */
#define FS_FILE "fragment3.glsl" /* tập tin mã nguồn fragment shader */
typedef enum objectMode { CUBE, SPHERE, TORUS, TEAPOT } OBJECT_MODE;
/* tham số cho fragment shader */
vec3 light = { 0.0f, 1.0f, 1.0f }; /* vị trí nguồn sáng */
vec3 ambient = { 0.1f, 0.1f, 0.1f }; /* màu ambient */
vec3 diffuse = { 1.0f, 0.5f, 0.0f }; /* màu diffuse */
vec3 specular = { 1.0f, 1.0f, 1.0f }; /* màu specular */
float Ka = 0.1f; /* hệ số ambient */
float Kd = 1.0f; /* hệ số diffuse */
float Ks = 1.0f; /* hệ số specular */
float shininess = 32.0f; /* hệ số bóng bề mặt */
vec3 camera = { 0.0f, 0.0f, 5.0f }; /* vị trí camera */
float xAngle = 0.0f; /* góc quay vật thể */
float yAngle = 0.0f;
float zAngle = 0.0f;
int xMotion = 0; /* theo dõi di chuyển chuột */
int yMotion = 0;
GLSL_PROGRAM* prog = NULL; /* đối tượng chương trình shader */
OBJECT_MODE obj = TEAPOT; /* vật thể hiện tại đang hiển thị */
void resize(int width, int height) { /* thay đổi kích thước cửa sổ */
	if (height == 0) height = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / height, 1.0f, 100.0f);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
}
void render() { /* dựng hình */
 /* truyền các tham số vào fragment shader */
	glslSetUniform3fv(prog, "lightPosition", light);
	glslSetUniform3fv(prog, "diffuseColor", diffuse);
	glslSetUniform1f(prog, "shininess", shininess);
	glslSetUniform1f(prog, "Ka", Ka);
	glslSetUniform1f(prog, "Kd", Kd);
	glslSetUniform1f(prog, "Ks", Ks);

	glClearColor(0.05f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camera.x, 0.0f, camera.z,
		camera.x, 0.0f, camera.z - 1.0f,
		0.0f, 1.0f, 0.0f);
	/* vẽ nguồn sáng */
	glslDeactivate(prog);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(light.x, light.y, light.z);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.05, 4, 4);
	glPopMatrix();
	glslActivate(prog);
	/* vẽ khung cảnh */
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
	switch (obj) {
	case CUBE: glutSolidCube(1.5f); break;
	case SPHERE: glutSolidSphere(1.0f, 24, 24); break;
	case TORUS: glutSolidTorus(0.5, 1.0f, 24, 24); break;
	case TEAPOT: glutSolidTeapot(1.0f); break;
	}
	glutSwapBuffers();
}
void input(unsigned char key, int x, int y) { /* xử lý sự kiện bàn phím */
	switch (key) {
	case 27: exit(0);
	case 'a':
	case 'A': camera.x -= 0.1f; light.x += 0.1f; break;
	case 'd':
	case 'D': camera.x += 0.1f; light.x -= 0.1f; break;
	case 'w':
	case 'W': camera.z -= 0.1f; light.z += 0.1f; break;
	case 's':
	case 'S': camera.z += 0.1f; light.z -= 0.1f; break;
	case 'X': light.x += 0.1f; break;
	case 'Y': light.y += 0.1f; break;
	case 'Z': light.z += 0.1f; break;
	case 'x': light.x -= 0.1f; break;
	case 'y': light.y -= 0.1f; break;
	case 'z': light.z -= 0.1f; break;
	case 'R': if (diffuse.r < 1.0f) diffuse.r += 0.01f; break;
	case 'G': if (diffuse.g < 1.0f) diffuse.g += 0.01f; break;
	case 'B': if (diffuse.b < 1.0f) diffuse.b += 0.01f; break;
	case 'r': if (diffuse.r >= 0.0f) diffuse.r -= 0.01f; break;
	case 'g': if (diffuse.g >= 0.0f) diffuse.g -= 0.01f; break;
	case 'b': if (diffuse.b >= 0.0f) diffuse.b -= 0.01f; break;
	case 'H': if (shininess < 200.0f) shininess += 1.0f; break;
	case 'h': if (shininess > 6.0f) shininess -= 1.0f; break;
	case '[': if (Kd >= 0.0f) Kd -= 0.05f; break;
	case ']': if (Kd < 1.0f) Kd += 0.05f; break;
	case '{': if (Ks >= 0.0f) Ks -= 0.05f; break;
	case '}': if (Ks < 1.0f) Ks += 0.05f; break;
	case '<': if (Ka >= 0.0f) Ka -= 0.05f; break;
	case '>': if (Ka < 1.0f) Ka += 0.05f; break;
	case '1': obj = CUBE; break;
	case '2': obj = SPHERE; break;
	case '3': obj = TORUS; break;
	case '4': obj = TEAPOT; break;
	default: break;
	}
}
void mouse(int button, int state, int x, int y) { /* xử lý sự kiện chuột */
	if (state == 0 && button == 0) { /* nút trái được nhấn */
		xMotion = x;
		yMotion = y;
	}
}
void motion(int x, int y) { /* theo dõi chuyển động chuột */
	if (xMotion) {
		if (xMotion > x) yAngle -= 2.0f;
		if (xMotion < x) yAngle += 2.0f;
		xMotion = x;
	}
	if (yMotion) {
		if (yMotion > y) xAngle -= 1.0f;
		if (yMotion < y) xAngle += 1.0f;
		yMotion = y;
	}
}
void idle() { /* xử lý khi không có sự kiện gì xảy ra */
	glutPostRedisplay();
}
GLboolean init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
	glutCreateWindow(WND_TITLE);
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutKeyboardFunc(input);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	if (GLEW_OK != glewInit()) return GL_FALSE;
	if (!(prog = glslCreate())) printf("No GLSL supported.\n");
	glslCompileFile(prog, VERTEX_SHADER, VS_FILE);
	glslCompileFile(prog, FRAGMENT_SHADER, FS_FILE);
	glslLink(prog);
	glslActivate(prog);
	glslSetUniform3fv(prog, "ambientColor", ambient);
	glslSetUniform3fv(prog, "specularColor", specular);
	return GL_TRUE;
}
void done() {
	glslDestroy(prog);
}
void run() {
	glutMainLoop();
}
int main(int argc, char** argv) {
	init(argc, argv);
	run();
	return 0;
}

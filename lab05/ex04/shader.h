#ifndef __SHADER_H__
#define __SHADER_H__
#include "Dependencies/glew/glew.h"
/* Định nghĩa kiểu dữ liệu vec3 tương đương với GLSL */
typedef struct {
	union {
		struct { float x, y, z; }; // truy xuất thông qua xyz
		struct { float r, g, b; }; // truy xuất thông qua rgb
		float data[3]; // truy xuất thông qua chỉ số
	};
} vec3;
/* kiểu đối tượng shader cần thao tác */
typedef enum glslShader { VERTEX_SHADER, FRAGMENT_SHADER } GLSL_SHADER;
/* đối tượng chương trình shader GLSL*/
typedef struct glslProgram {
	GLuint program;
	GLboolean linked;
} GLSL_PROGRAM;
/* các hàm xử lý trên đối tượng chương trình shader */
GLSL_PROGRAM* glslCreate();
void glslDestroy(GLSL_PROGRAM* p);
GLboolean glslCompileFile(GLSL_PROGRAM* p, GLSL_SHADER type,
	const GLchar* fileName);
GLboolean glslCompileString(GLSL_PROGRAM* p, GLSL_SHADER type,
	const GLchar* source);
GLboolean glslLink(GLSL_PROGRAM* p);
GLboolean glslActivate(GLSL_PROGRAM* p);
void glslDeactivate(GLSL_PROGRAM* p);
/* các hàm thao tác trên biến uniform */
GLint glslGetUniform(GLSL_PROGRAM* p, const GLchar* name);
GLboolean glslSetUniform1f(GLSL_PROGRAM* p, const GLchar* name, GLfloat v);
GLboolean glslSetUniform3f(GLSL_PROGRAM* p, const GLchar* name,
	GLfloat x, GLfloat y, GLfloat z);
GLboolean glslSetUniform3fv(GLSL_PROGRAM* p, const GLchar* name, const vec3 v);
#endif


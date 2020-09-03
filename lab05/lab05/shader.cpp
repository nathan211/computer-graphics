#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

GLSL_PROGRAM* glslCreate() {
	GLSL_PROGRAM* p;
	if (!(p = (GLSL_PROGRAM*)malloc(sizeof(GLSL_PROGRAM)))) return NULL;
	p->linked = GL_FALSE;
	if (!(p->program = glCreateProgram())) {
		free(p);
		p = NULL;
	}
	return p;
}
void glslDestroy(GLSL_PROGRAM* p) {
	if (!p) return;
	glUseProgram(0);
	glDeleteProgram(p->program);
	free(p);
}
GLboolean glslCompileFile(GLSL_PROGRAM* p, GLSL_SHADER type, const GLchar* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	GLchar* source = NULL;
	GLint count = 0;
	GLboolean result;
	if (!fp || !p) return GL_FALSE;
	fseek(fp, 0, SEEK_END);
	count = ftell(fp);
	rewind(fp);
	if (count > 0) {
		source = (GLchar*)malloc(sizeof(GLchar) * (count + 1));
		count = fread(source, sizeof(GLchar), count, fp);
		source[count] = '\0';
	}
	fclose(fp);
	result = glslCompileString(p, type, source);
	free(source);
	return result;
}
GLboolean glslCompileString(GLSL_PROGRAM* p, GLSL_SHADER type, const GLchar* source)
{
	GLuint shader = 0;
	GLint result = GL_FALSE;
	if (!p) return GL_FALSE;
	switch (type) {
	case VERTEX_SHADER: shader = glCreateShader(GL_VERTEX_SHADER); break;
	case FRAGMENT_SHADER: shader = glCreateShader(GL_FRAGMENT_SHADER); break;
	}
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength) {
			char* log = (char*)malloc(logLength);
			int size = 0;
			glGetShaderInfoLog(shader, logLength, &size, log);
			printf("%s\n", log);
			free(log);
		}
	}
	else {
		glAttachShader(p->program, shader);
		glDeleteShader(shader);
	}
	return result;
}
GLboolean glslLink(GLSL_PROGRAM* p) {
	GLint result = GL_FALSE;
	if (!p) return GL_FALSE;
	if (p->linked) return GL_TRUE;
	glLinkProgram(p->program);
	glGetProgramiv(p->program, GL_LINK_STATUS, &result);
	p->linked = GL_TRUE;
	return result;
}
GLboolean glslActivate(GLSL_PROGRAM* p) {
	if (!p || !p->linked) return GL_FALSE;
	glUseProgram(p->program);
	return GL_TRUE;
}
void glslDeactivate(GLSL_PROGRAM* p) {
	glUseProgram(0);
}
GLint glslGetUniform(GLSL_PROGRAM* p, const GLchar* name) {
	return glGetUniformLocation(p->program, name);
}
GLboolean glslSetUniform1f(GLSL_PROGRAM* p, const GLchar* name, GLfloat v) {
	GLint loc = glslGetUniform(p, name);
	if (loc < 0) return GL_FALSE;
	glUniform1f(loc, v);
	return GL_TRUE;
}
GLboolean glslSetUniform3f(GLSL_PROGRAM* p, const GLchar* name,
	GLfloat x, GLfloat y, GLfloat z) {
	GLint loc = glslGetUniform(p, name);
	if (loc < 0) return GL_FALSE;
	glUniform3f(loc, x, y, z);
	return GL_TRUE;
}
GLboolean glslSetUniform3fv(GLSL_PROGRAM* p, const GLchar* name, const vec3 v) {
	return glslSetUniform3f(p, name, v.x, v.y, v.z);
}


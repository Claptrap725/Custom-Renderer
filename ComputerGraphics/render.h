#pragma once

#include "glew/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// defining our vertex structure
struct vertex
{
	glm::vec4 pos;
	glm::vec4 color;
	glm::vec2 uv;
};

struct transform
{
	// position on object
	glm::vec3 pos;
	// rotation in degrees
	glm::vec3 rot;
	// scale of object
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::mat4 matrix()
	{
		glm::mat4 mat = glm::identity<glm::mat4>();

		mat = glm::scale(mat, scale);
		mat = glm::translate(mat, pos);
		mat = glm::rotate(mat, glm::radians(rot.z), glm::vec3(0, 0, 1));
		mat = glm::rotate(mat, glm::radians(rot.x), glm::vec3(1, 0, 0));
		mat = glm::rotate(mat, glm::radians(rot.y), glm::vec3(0, 1, 0));

		return mat;
	}
};

// an object to represent our mesh
struct geometry
{
	GLuint vao, vbo, ibo;
	GLuint size;
	transform transform;
};

// an object to represent our shader
struct shader
{
	GLuint program;
};

struct texture
{
	GLuint handle;
	unsigned int width, height, channels;
};

// function to make and unmake the above types
geometry loadGeometry(const char * path);
geometry makeGeometry(vertex * verts, size_t vertCount, unsigned int* indices, size_t indxCount);
void freeGeometry(geometry & geo);

shader makeShader(const char *vertSource, const char *fragSource);
void freeShader(shader & sha);

texture loadTexture(const char * filePath);
texture makeTexture(unsigned int width, unsigned int height, unsigned int channels, const unsigned char* pixels);
void freeTexture(texture &tex);

void draw(const shader & sha, const geometry & geo);

void setUniform(const shader& sha, GLuint location, const glm::mat4& value);
void setUniform(const shader & sha, const glm::mat4 & camProj, const glm::mat4 & camView, const glm::mat4 & triModel);
void setUniform(const shader& sha, GLuint location, const texture &tex, int textureSlot);

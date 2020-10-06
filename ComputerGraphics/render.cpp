#include "render.h"

#include <vector>
#include <iostream>

#include "glm/ext.hpp"
#include "tinyObj/tiny_obj_loader.h"
#include "stb_image/stb_image.h"


geometry loadGeometry(const char * filePath)
{
	tinyobj::attrib_t vertexAttributes;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string error;

	bool success = tinyobj::LoadObj(&vertexAttributes, &shapes, &materials, &error, filePath);

	if (!success)
	{
		std::cout << error << std::endl;
		return geometry();
	}

	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;

	size_t offset = 0;
	for (size_t i = 0; shapes[0].mesh.num_face_vertices.size(); i++)
	{
		unsigned char faceVertices = shapes[0].mesh.num_face_vertices[i];

		assert(faceVertices == 3 && "unsupported number of face vertices");

		for (unsigned char j = 0; j < faceVertices; j++)
		{
			tinyobj::index_t idx = shapes[0].mesh.indices[offset + j];

			tinyobj::real_t posX = vertexAttributes.vertices[3 * idx.vertex_index + 0];
			tinyobj::real_t posY = vertexAttributes.vertices[3 * idx.vertex_index + 1];
			tinyobj::real_t posZ = vertexAttributes.vertices[3 * idx.vertex_index + 2];

			//tinyobj::real_t norR = vertexAttributes.normals[3 * ]

			tinyobj::real_t colR = 1.0f;
			tinyobj::real_t colG = 0.2f;
			tinyobj::real_t colB = 0.2f;

			tinyobj::real_t texU = vertexAttributes.texcoords[3 * idx.texcoord_index + 0];
			tinyobj::real_t texV = vertexAttributes.texcoords[3 * idx.texcoord_index + 1];

			vertices.push_back(vertex{ {posX, posY, posZ, 1.0f}, {colR, colG, colB, 1.0f}, {texU, texV} });
			indices.push_back(faceVertices * i * j);
		}

		offset += faceVertices;
	}

	return makeGeometry(vertices.data(), vertices.size(), indices.data(), indices.size());
}

geometry makeGeometry(vertex * verts, size_t vertCount, unsigned int * indices, size_t indxCount)
{
	// make an instance geometry
	geometry newGeo = {};
	newGeo.size = indxCount;

	// generate buffers and VAO
	glGenBuffers(1, &newGeo.vbo);
	glGenBuffers(1, &newGeo.ibo);
	glGenVertexArrays(1, &newGeo.vao);
	
	// bind the VAO and buffers
	// note: order matter
	glBindVertexArray(newGeo.vao);
	glBindBuffer(GL_ARRAY_BUFFER, newGeo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeo.ibo);

	// populate the buffers (aka send the data over)
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indxCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	// describe the data contained within the buffers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));

	// unbind the buffers (VAO the the buffers)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// return the geometry

	return newGeo;
}

void freeGeometry(geometry & geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);

	geo = {};
}

shader makeShader(const char * vertSource, const char * fragSource)
{
	// make a shader program
	shader newShad = {};
	newShad.program = glCreateProgram();

	// create the shaders (not the same as a shader program)
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

	// compile the shaders
	glShaderSource(vert, 1, &vertSource, 0);
	glShaderSource(frag, 1, &fragSource, 0);
	glCompileShader(vert);
	glCompileShader(frag);

	// attatch the shaders
	glAttachShader(newShad.program, vert);
	glAttachShader(newShad.program, frag);

	// link the shader program
	glLinkProgram(newShad.program);

	// delete the shaders
	glDeleteShader(vert);
	glDeleteShader(frag);

	// return the shader
	return newShad;
}

void freeShader(shader & sha)
{
	glDeleteProgram(sha.program);
	sha = {};
}

texture loadTexture(const char * filePath)
{
	assert(filePath != nullptr && "File path was invalid.");

	int imageWidth = 0, imageHeight = 0, imageFormat = 0;
	unsigned char * pixels = nullptr;

	stbi_set_flip_vertically_on_load(true);
	pixels = stbi_load(filePath, &imageWidth, &imageHeight, &imageFormat, STBI_default);

	assert(pixels != nullptr && "Image failed to load.");

	texture newTexture = makeTexture(imageWidth, imageHeight, imageFormat, pixels);
	assert(newTexture.handle != 0 && "Failed to create texture.");

	stbi_image_free(pixels);

	return newTexture;
}

texture makeTexture(unsigned int width, unsigned int height, unsigned int channels, const unsigned char * pixels)
{
	assert(channels > 0 && channels < 5);

	GLenum oglFormat = GL_RED;
	switch (channels)
	{
	case 1:
		oglFormat = GL_RED;
		break;
	case 2:
		oglFormat = GL_RG;
		break;
	case 3:
		oglFormat = GL_RGB;
		break;
	case 4:
		oglFormat = GL_RGBA;
		break;
	}

	texture retVal = { 0, width, height, channels };

	glGenTextures(1, &retVal.handle);
	glBindTexture(GL_TEXTURE_2D, retVal.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, oglFormat, width, height, 0, oglFormat, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retVal;
}

void freeTexture(texture & tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = {};
}

void draw(const shader & sha, const geometry & geo)
{
	glUseProgram(sha.program);
	glBindVertexArray(geo.vao);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}

void setUniform(const shader & sha, GLuint location, const glm::mat4 & value)
{
	glProgramUniformMatrix4fv(sha.program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void setUniform(const shader & sha, GLuint location, const texture & tex, int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, tex.handle);

	glProgramUniform1i(sha.program, location, textureSlot);
}

void setUniform(const shader & sha, const glm::mat4 & camProj, const glm::mat4 & camView, const glm::mat4 & triModel)
{
	glProgramUniformMatrix4fv(sha.program, 0, 1, GL_FALSE, glm::value_ptr(camProj));
	glProgramUniformMatrix4fv(sha.program, 1, 1, GL_FALSE, glm::value_ptr(camView));
	glProgramUniformMatrix4fv(sha.program, 2, 1, GL_FALSE, glm::value_ptr(triModel));
}
#pragma once
#include "render.h"

geometry GetTriangle()
{
	vertex triVerts[] =
	{
		{{1, 0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},		// 0 bot right
		{{0, 1, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},		// 1 top
		{{0, 0, 1, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}}		// 2 bot left
	};

	unsigned int triIndices[] = { 0,1,2 };

	return makeGeometry(triVerts, 3, triIndices, 3);
}

geometry GetTriangle(vertex triVerts[3], unsigned int triIndices[3])
{
	return makeGeometry(triVerts, 3, triIndices, 3);
}

geometry GetQuad()
{
	vertex quadVerts[] =
	{
		{{0.5, -0.5, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},	// 0 bot right
		{{0.5, 0.5, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 1}, {0.0f,0.0f,-1.0f} },	// 1 top right
		{{-0.5, 0.5, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0, 1}, {0.0f,0.0f,-1.0f} },	// 2 top left
		{{-0.5, -0.5, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0, 0}, {0.0f,0.0f,-1.0f} }	// 3 bot left
	};

	unsigned int quadIndices[] = { 0,1,2, 0,3,2 };

	return makeGeometry(quadVerts, 4, quadIndices, 6);
}

geometry GetQuad(vertex quadVerts[4], unsigned int quadIndices[6])
{
	return makeGeometry(quadVerts, 4, quadIndices, 6);
}

geometry GetQuad(float width, float height)
{
	vertex quadVerts[] =
	{
		{{width / 2, -height / 2, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},		// 0 bot right
		{{width / 2, height / 2, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},		// 1 top right
		{{-width / 2, height / 2, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}},		// 2 top left
		{{-width / 2, -height / 2, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1, 0}, {0.0f,0.0f,-1.0f}}			// 3 bot left
	};

	unsigned int quadIndices[] = { 0,1,2, 0,3,2 };

	return makeGeometry(quadVerts, 4, quadIndices, 6);
}

geometry GetQuad(float posX, float posY, float width, float height)
{
	vertex quadVerts[] =
	{
		{{posX + width / 2, posY - height / 2, 0, 1}},		// 0 bot right
		{{posX + width / 2, posY + height / 2, 0, 1}},		// 1 top right
		{{posX - width / 2, posY + height / 2, 0, 1}},		// 2 top left
		{{posX - width / 2, posY - height / 2, 0, 1}}		// 3 bot left
	};

	unsigned int quadIndices[] = { 0,1,2, 0,3,2 };

	return makeGeometry(quadVerts, 4, quadIndices, 6);
}

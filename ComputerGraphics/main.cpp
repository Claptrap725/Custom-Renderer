#include <iostream>
#include "context.h"
#include "render.h"
#include "shaders.h"
#include "shapes.h"
#include "glfw/glfw3.h"


int main()
{
	context game;
	float windowWidth = 800;
	float windowheight = 800;
	game.init(windowWidth, windowheight, "It's a window.");

	glm::mat4 camProj = glm::perspective(glm::radians(80.0f), windowWidth / windowheight, 0.1f, 100.0f);
	glm::mat4 camVeiw = glm::lookAt(glm::vec3(0, 1, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	texture em = loadTexture("res\\me.jpg");

	geometry quad = GetQuad();
	quad.transform.pos = glm::vec3(3, 3, 0);
	quad.transform.rot = glm::vec3(0, 0, 0);
	quad.transform.scale = glm::vec3(3, 3, 1);

	shader basicShader = GetShaderByColor(COLORYELLOW);
	setUniform(basicShader, 3, em, 0);


	while (!game.shouldClose())
	{
		// implement game logic
		game.tick();
		//quad.transform.rot += glm::vec3(0, 0, 1);
		//if (glfwGetKey(game.GetWindow(), GLFW_KEY_W) == 1)
		//	quad.transform.pos += glm::vec3(0.0f, 0.01f, 0.0f);
		//if (glfwGetKey(game.GetWindow(), GLFW_KEY_S) == 1)
		//	quad.transform.pos += glm::vec3(0.0f, -0.01f, 0.0f);
		//if (glfwGetKey(game.GetWindow(), GLFW_KEY_D) == 1)
		//	quad.transform.pos += glm::vec3(0.01f, 0.0f, 0.0f);
		//if (glfwGetKey(game.GetWindow(), GLFW_KEY_A) == 1)
		//	quad.transform.pos += glm::vec3(-0.01f, 0.0f, 0.0f);
		//
		//setUniform(basicShader, camProj, camVeiw, quad.transform.matrix());

		game.clear();

		// implement render logic here
		draw(basicShader, quad);
	}

	freeGeometry(quad);
	freeShader(basicShader);
	game.term();

	return 0;
}
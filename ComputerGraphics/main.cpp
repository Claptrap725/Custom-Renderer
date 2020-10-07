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

	geometry quad = GetQuad();
	quad.transform.pos = glm::vec3(0.5f, 0, 0);
	quad.transform.rot = glm::vec3(0, 0, 0);
	quad.transform.scale = glm::vec3(15, 15, 1);

	texture me = loadTexture("res\\Profile picture.png");
	shader basicShader = GetShaderBasic();
	setUniform(basicShader, 3, me, 0);

	geometry vase = loadGeometry("res\\SimpleVase.obj");
	vase.transform.pos = glm::vec3(0, 0, 0);
	vase.transform.rot = glm::vec3(0, 0, 0);
	vase.transform.scale = glm::vec3(5, 5, 1);
	shader red = GetShaderByColor(COLORRED);

	while (!game.shouldClose())
	{
		// implement game logic
		game.tick();
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_W))
		vase.transform.rot += glm::vec3(-0.3, 0, 0);
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_S))
		vase.transform.rot += glm::vec3(0.3, 0, 0);
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_E))
			vase.transform.rot += glm::vec3(0, 0.3, 0);
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_Q))
			vase.transform.rot += glm::vec3(0, -0.3, 0);
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_D))
			vase.transform.rot += glm::vec3(0, 0, -0.3);
		if (glfwGetKey(game.GetWindow(), GLFW_KEY_A))
			vase.transform.rot += glm::vec3(0, 0, 0.3);
		

		//setUniform(basicShader, camProj, camVeiw, quad.transform.matrix());
		//setUniform(red, camProj, camVeiw, vase.transform.matrix());
		setUniform(basicShader, camProj, camVeiw, vase.transform.matrix());
		game.clear();

		// implement render logic here
		//draw(basicShader, quad);
		draw(basicShader, vase);
	}

	freeGeometry(quad);
	freeShader(basicShader);
	game.term();

	return 0;
}
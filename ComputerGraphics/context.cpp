#include "context.h"

#include <iostream>

#include "glew/GL/glew.h"		// must come before glfw
#include "glfw/glfw3.h"


// Error callback called by OpenGL whenever a problem occurs (vendor-dependent)
void APIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message,
	const void *userParam)
{
	std::cerr << message << std::endl;
}

bool context::init(int width, int height, const char* title)
{
	// init glfw
	int glfwStatus = glfwInit();
	if (glfwStatus == GLFW_FALSE)
	{
		std::cout << "An error occurred with GLFW.";
		return false;
	}

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(window);


	// init glew
	int glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cout << "An error occured with GLEW.";
		return false;
	}

	// print diagnostics
	std::cout << "OpenGL Version: %s\n" << (const char*)glGetString(GL_VERSION);
	std::cout << "Renderer: %s\n" << (const char*)glGetString(GL_RENDERER);
	std::cout << "Vender: %s\n" << (const char*)glGetString(GL_VENDOR);
	std::cout << "GLSL: %s\n" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

	// set up defaults
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	// return true if success
	return true;
}


void context::tick()
{
	// update glfw
	glfwPollEvents();
	glfwSwapBuffers(window);

	// update delta time
}

void context::term()
{
	glfwDestroyWindow(window);
	window = nullptr;

	glfwTerminate();
}

void context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool context::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

GLFWwindow * context::GetWindow()
{
	return window;
}




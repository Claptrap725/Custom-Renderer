#pragma once
#include "render.h"
#include <string>

#define COLORRED glm::vec4(1.0f,0.0f,0.0f,1.0f)
#define COLORGREEN glm::vec4(0.0f,1.0f,0.0f,1.0f)
#define COLORBLUE glm::vec4(0.0f,0.0f,1.0f,1.0f)
#define COLORBLACK glm::vec4(0.0f,0.0f,0.0f,1.0f)
#define COLORWHITE glm::vec4(1.0f,1.0f,1.0f,1.0f)
#define COLORCYAN glm::vec4(0.0f,1.0f,1.0f,1.0f)
#define COLORYELLOW glm::vec4(1.0f,1.0f,0.0f,1.0f)
#define COLORMAGENTA glm::vec4(1.0f,0.0f,1.0f,1.0f)
#define COLORDARKGRAY glm::vec4(0.2f,0.2f,0.2f,1.0f)
#define COLORGRAY glm::vec4(0.5f,0.5f,0.5f,1.0f)
#define COLORLIGHTGRAY glm::vec4(0.8f,0.8f,0.8f,1.0f)

shader GetShaderBasic()
{
	const char * basicVertexShader =
		"#version 430\n"
		"layout (location = 0) in vec4 position;\n"

		"layout (location = 0) uniform mat4 proj;\n"
		"layout (location = 1) uniform mat4 view;\n"
		"layout (location = 2) uniform mat4 model;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main()\n"
		"{"
			"gl_Position = proj * view * model * position;"
			"vColor = color;\n"
			"vUV = uv;\n"
		"}";

	const char * basicFragShader =
		"#version 430\n"
		"in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"out vec4 outoutColor;\n"
		"uniform sampler2D mainTexture;\n"
		"void main()\n"
		"{"
			"outputColor = texture(mainTexture, vUV);"
		"}";

	return makeShader(basicVertexShader, basicFragShader);
}

shader GetShaderByColor(glm::vec4 color)
{
	std::string colorText = "vec4(" + std::to_string(color.x) + ", " + std::to_string(color.y) + ", " + std::to_string(color.z) + ", " + std::to_string(color.w) + ")";

	const char * basicVertexShader =
		"#version 430\n"
		"layout (location = 0) in vec4 position;\n"

		"layout (location = 0) uniform mat4 proj;\n"
		"layout (location = 1) uniform mat4 view;\n"
		"layout (location = 2) uniform mat4 model;\n"
		"void main()\n"
		"{"
		"gl_Position = proj * view * model * position;"
		"}";

	std::string basicFragShader =
		"#version 430\n"
		"out vec4 vertColor;\n"
		"void main()\n"
		"{"
			"vertColor = " + colorText + ";"
		"}";

	return makeShader(basicVertexShader, basicFragShader.c_str());

}

shader GetClipShaderBasic()
{
	const char * basicVertexShader =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"void main() {gl_Position = position; vColor = position;}";

	const char * basicFragShader =
		"#version 410\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vec4(0.2f,0.2f,0.2f,1.0f);}";

	return makeShader(basicVertexShader, basicFragShader);
}

shader GetClipShaderColorByPosition()
{
	const char * basicVertexShader =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"out vec4 vColor;\n"
		"void main() {gl_Position = position; vColor = position;}";

	const char * basicFragShader =
		"#version 410\n"
		"in vec4 vColor;\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vColor;}";

	return makeShader(basicVertexShader, basicFragShader);
}

shader GetClipShaderColorByPosition(glm::vec4 offset)
{

	std::string offsetText = "vec4(" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ", " + std::to_string(offset.z) + ", " + std::to_string(offset.w) + ")";

	const char * basicVertexShader =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"out vec4 vColor;\n"
		"void main() {gl_Position = position; vColor = position;}";

	std::string basicFragShader =
		"#version 410\n"
		"in vec4 vColor;\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vColor + " + offsetText + ";}";

	return makeShader(basicVertexShader, basicFragShader.c_str());
}

shader GetClipShaderByColor(glm::vec4 color)
{

	std::string colorText = "vec4(" + std::to_string(color.x) + ", " + std::to_string(color.y) + ", " + std::to_string(color.z) + ", " + std::to_string(color.w) + ")";

	const char * basicVertexShader =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"out vec4 vColor;\n"
		"void main() {gl_Position = position; vColor = position;}";

	std::string basicFragShader =
		"#version 410\n"
		"in vec4 vColor;\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = " + colorText + ";}";

	return makeShader(basicVertexShader, basicFragShader.c_str());
}
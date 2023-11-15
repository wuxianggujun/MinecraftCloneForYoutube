#include "core.hpp"
#include "core/Window.hpp"
#include "core/Input.hpp"
#include "challenges/Cubes.hpp"
#include "renderer/ShaderProgram.hpp"
#include <iostream>

using namespace MinecraftClone;

const int windowWidth = 1920;
const int windowHeight = 1080;
const char* windowTitle = "OpenGL Template";

void GLAPIENTRY errorMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (type == GL_DEBUG_TYPE_ERROR)
	{
		std::cerr << ("GL CALLBACK: **GL ERROR** type = 0x%x, severity = 0x%x, message = %s\n",
			type, severity, message) << std::endl;
	}
}

void glfwErrorCallback(int error, const char* description)
{
	std::cerr <<("GLFW CALLBACK: **GLFW ERROR** Error: %d description: %s\n", error, description) << std::endl;
}

int main()
{
    // 设置错误回调
	glfwSetErrorCallback(glfwErrorCallback);
	if(!glfwInit()){
		std::cerr <<("GLFW failed to initialize") << "\n";
		return -1;
	}

    // 调用window类的静态方法createWindow创建窗口
	Window* window = Window::createWindow(windowWidth, windowHeight, windowTitle);
	if (window == nullptr)
	{
		std::cerr << ("Failed to create GLFW window") <<"\n";
		glfwTerminate();
		return -1;
	}
    // 初始化并设置回调接口
	window->installMainCallbacks();

    // 加载glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << ("Failed to initialize GLAD.") << "\n";
		glfwTerminate();
		return -1;
	}

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorMessageCallback, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, windowWidth, windowHeight);

	float dt = 0.016f;
	float frameStart = 0.0f;

	Cubes::init(*window);

	bool showPlayer = false;
	bool showTerrain = false;
	float keyDebounce = 0.1f;
	while (!glfwWindowShouldClose(window->nativeWindow))
	{
		dt = glfwGetTime() - frameStart;
		frameStart = glfwGetTime();

		glClearColor(39.0f/255.0f, 40.0f/255.0f, 34.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		keyDebounce -= dt;

		Cubes::update(dt);

		glfwSwapBuffers(window->nativeWindow);
		glfwPollEvents();
	}

	Cubes::destroy();

	Window::freeWindow(window);
	glfwTerminate();
	return 0;
}
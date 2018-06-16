#pragma once

#include <iostream>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// glm
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Star.h"
#include "Planet.h"

class Application
{
private:
	// Window dimensions
	const GLuint WIDTH = 1280, HEIGHT = 720;

	Star sun;
	Planet planet_a, planet_b, planet_c, planet_d;

	bool pause;
	bool pressed[1024];
	static void mouse_callback(GLFWwindow* window, double x, double y);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void display();
	void moveWASD();

public:
	Camera camera;

	Application();
	virtual ~Application();
	void run();
};


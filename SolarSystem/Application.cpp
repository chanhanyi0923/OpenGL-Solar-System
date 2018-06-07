#include "Application.h"

extern Application *app;


Application::Application():
	camera(glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
	sun(glm::vec3(1, 1, 0)),
	planet_a(glm::vec3(1, 1, 1), 30, 10, 2),
	planet_b(glm::vec3(0, 1, 1), 12, 40, 6),
	planet_c(glm::vec3(1, 0, 1), 45, 3, 1)
{
}


Application::~Application()
{
}


void Application::moveWASD()
{
	static GLfloat last_time;
	GLfloat current_time = glfwGetTime();
	GLfloat delta_time = current_time - last_time;
	last_time = current_time;

	if (this->pressed[GLFW_KEY_W]) {
		this->camera.processKeyboard(Camera::FORWARD, delta_time);
	}
	if (this->pressed[GLFW_KEY_S]) {
		this->camera.processKeyboard(Camera::BACKWARD, delta_time);
	}
	if (this->pressed[GLFW_KEY_A]) {
		this->camera.processKeyboard(Camera::LEFT, delta_time);
	}
	if (this->pressed[GLFW_KEY_D]) {
		this->camera.processKeyboard(Camera::RIGHT, delta_time);
	}
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			app->pressed[key] = true;
		} else if (action == GLFW_RELEASE) {
			app->pressed[key] = false;
		}
	}
}


void Application::mouse_callback(GLFWwindow* window, double x, double y)
{
	static double last_x = x, last_y = y;
	app->camera.processMouseMovement(x - last_x, last_y - y);
	last_x = x;
	last_y = y;
}


void Application::display()
{
	glfwPollEvents();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 200.0f);
	glm::mat4 view = camera.getViewMatrix();

	sun.render(view, projection, camera.getPosition());
}


void Application::run()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 8 Chen Hanyi", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Application::mouse_callback);
	glfwSetKeyCallback(window, Application::key_callback);

	if (glewInit() != GLEW_OK) {
		throw std::exception("Failed to initialize GLEW");
	}

	// Define the viewport dimensions
	int width = this->WIDTH, height = this->HEIGHT;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	// initialize solar system
	Light light(glm::vec3(0, 0, 0), glm::vec3(1.000f, 0.938f, 0.510f));
	sun.init();
	planet_a.init(&light);
	planet_b.init(&light);
	planet_c.init(&light);
	sun.addChild(&planet_a);
	sun.addChild(&planet_c);
	planet_a.addChild(&planet_b);

	// Game loop
	GLfloat current_time = 0, last_time = 0, period = 1e-3;
	while (!glfwWindowShouldClose(window)) {
		current_time = glfwGetTime();
		if (current_time - last_time > period) {
			sun.update(glm::mat4(1.0));
			last_time = current_time;
		}

		this->moveWASD();
		this->display();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}


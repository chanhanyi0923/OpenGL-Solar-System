#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Light.h"

class Sphere
{
private:
	glm::vec3 color;
	Light * light;
	Shader sphere_shader;
	GLuint VAO, VBO;
	std::vector<GLfloat> vertices;
	void lighting(glm::vec3 camera_position);

public:
	Sphere(glm::vec3 color);
	virtual ~Sphere();
	void init(const char * frag, const char * vs);
	void render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);
	void setLight(Light *light_ptr);
};


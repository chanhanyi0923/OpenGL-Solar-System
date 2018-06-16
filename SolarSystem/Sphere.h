#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Light.h"
#include "Texture.h"

class Sphere
{
public:
	enum Type { color_type, texture_type };

private:
	Type type;
	glm::vec3 color;
	Light * light;
	Texture * texture;
	Shader sphere_shader;
	GLuint VAO, VBO;
	std::vector<GLfloat> vertices;
	void lighting(glm::vec3 camera_position);

public:
	Sphere();
	virtual ~Sphere();
	void setType(Sphere::Type type);
	void init(const char * frag, const char * vs);
	void render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);
	void setLight(Light *light_ptr);
	void setColor(glm::vec3 color);
	void setTexture(Texture * texture_ptr);
};


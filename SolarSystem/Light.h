#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
private:
	glm::vec3 position, color;

public:
	Light(glm::vec3 position, glm::vec3 color);
	virtual ~Light();
	glm::vec3 getPosition();
	glm::vec3 getColor();
};


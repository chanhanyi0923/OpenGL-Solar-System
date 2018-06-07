#pragma once

#include "Sphere.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Ball
{
private:
	glm::mat4 model;
	GLfloat z_angle, radius;
	std::vector<Ball*> children;

	// for revolution
	GLfloat speed, angle;

protected:
	Sphere sphere;

public:
	Ball(glm::vec3 color, GLfloat radius, GLfloat z_angle, GLfloat speed);
	virtual ~Ball();
	void update(glm::mat4 parent_model);
	void render(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);
	void addChild(Ball *b);
};


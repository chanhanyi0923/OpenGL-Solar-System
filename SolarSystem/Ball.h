#pragma once

#include "Sphere.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Ball
{
private:
	glm::mat4 model;

	GLfloat size;
	std::vector<Ball*> children;

	// for revolution
	// current angle
	GLfloat angle;
	// fixed
	GLfloat speed, z_angle, radius;

protected:
	Sphere sphere;

public:
	Ball(GLfloat size, GLfloat radius, GLfloat z_angle, GLfloat speed);
	virtual ~Ball();
	void setType(Sphere::Type type);
	void setColor(glm::vec3 color);
	void setTexture(Texture * texture_ptr);
	void update(glm::mat4 parent_model);
	void render(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);
	void addChild(Ball *b);
};


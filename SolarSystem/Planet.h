#pragma once

#include "Ball.h"

class Planet :
	public Ball
{
public:
	Planet(glm::vec3 color, GLfloat radius, GLfloat z_angle, GLfloat speed);
	virtual ~Planet();
	void init(Light * light_ptr);
};


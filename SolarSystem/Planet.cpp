#include "Planet.h"


Planet::Planet(glm::vec3 color, GLfloat radius, GLfloat z_angle, GLfloat speed):
	Ball(color, radius, z_angle, speed)
{
}


Planet::~Planet()
{
}


void Planet::init(Light * light_ptr)
{
	this->sphere.init("planet.frag", "planet.vs");
	this->sphere.setLight(light_ptr);
}


#include "Star.h"


Star::Star(glm::vec3 color):
	Ball(color, 0, 0, 0)
{
}


Star::~Star()
{
}


void Star::init()
{
	this->sphere.init("star.frag", "star.vs");
}


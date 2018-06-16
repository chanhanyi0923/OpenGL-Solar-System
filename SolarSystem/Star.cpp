#include "Star.h"


Star::Star():
	Ball(3, 0, 0, 0)
{
}


Star::~Star()
{
}


void Star::init()
{
	this->sphere.init("star.frag", "star.vs");
}


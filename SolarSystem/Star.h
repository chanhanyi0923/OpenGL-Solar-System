#pragma once
#include "Ball.h"
class Star :
	public Ball
{
public:
	Star(glm::vec3 color);
	virtual ~Star();
	void init();
};


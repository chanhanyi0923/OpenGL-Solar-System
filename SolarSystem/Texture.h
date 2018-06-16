#pragma once

#include <GL/glew.h>

class Texture
{
	static GLuint count;
	GLuint id, data;
public:
	Texture();
	~Texture();
	void load(const char *filename);
	GLuint get();
	GLuint getId();
};


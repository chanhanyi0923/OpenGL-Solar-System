#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
private:
	GLuint program, vertex_shader, fragment_shader;
	bool vs, fs;
	std::string openFile(const char *filename);

public:
	Shader();
	virtual ~Shader();
	void loadVertexShader(const char *filename);
	void loadFragmentShader(const char *filename);
	void createProgram();
	void use();
	GLuint get();
};

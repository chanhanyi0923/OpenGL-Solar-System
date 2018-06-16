#include "Texture.h"

#include <stdexcept>
#include <SOIL/SOIL.h>

Texture::Texture()
{
	this->id = Texture::count++;
}


Texture::~Texture()
{
}


GLuint Texture::get()
{
	return this->data;
}


GLuint Texture::getId()
{
	return this->id;
}


void Texture::load(const char *filename)
{
	glGenTextures(1, &this->data);
	glBindTexture(GL_TEXTURE_2D, this->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr) {
		throw std::exception("Texture load failed.");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


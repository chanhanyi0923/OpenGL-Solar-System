#include <exception>
#include <iostream>

#include "Application.h"
#include "Texture.h"

Application *app;
GLuint Texture::count = 0;

int main(int argc, char *argv[])
{
	app = new Application;
	try {
		app->run();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	delete app;

	return 0;
}


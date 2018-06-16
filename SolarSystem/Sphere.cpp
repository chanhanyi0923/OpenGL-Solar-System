#include "Sphere.h"


Sphere::Sphere():
	type(Type::color_type), color(glm::vec3(0.0f, 0.0f, 0.0f)), light(nullptr), texture(nullptr), VAO(0), VBO(0)
{
	const float PI = acos(-1);
	const GLfloat radius = 4.0f;
	const int gradation = 20;

	GLfloat x, y, z, alpha, beta;

	for (alpha = 0.0f; alpha < PI; alpha += PI / gradation) {
		for (beta = 0.0f; beta < 2.0f * PI; beta += PI / gradation) {
			x = radius * cos(beta) * sin(alpha);
			y = radius * sin(beta) * sin(alpha);
			z = radius * cos(alpha);

			// position
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// normal
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// texture
			vertices.push_back(beta / (2.0f * PI));
			vertices.push_back(alpha / PI);


			x = radius * cos(beta) * sin(alpha + PI / gradation);
			y = radius * sin(beta) * sin(alpha + PI / gradation);
			z = radius * cos(alpha + PI / gradation);

			// position
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// normal
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// texture
			vertices.push_back(beta / (2.0f * PI));
			vertices.push_back((alpha + PI / gradation) / PI);
		}
	}
}


Sphere::~Sphere()
{
}


void Sphere::setType(Sphere::Type type)
{
	this->type = type;
}


void Sphere::setLight(Light *light_ptr)
{
	this->light = light_ptr;
}


void Sphere::setColor(glm::vec3 color)
{
	this->color = color;
}


void Sphere::setTexture(Texture *texture_ptr)
{
	this->texture = texture_ptr;
}


void Sphere::lighting(glm::vec3 camera_position)
{
	if (light != nullptr) {
		GLint viewPosLoc = glGetUniformLocation(sphere_shader.get(), "viewPos");
		glUniform3f(viewPosLoc, camera_position.x, camera_position.y, camera_position.z);

		GLint lightColorLoc = glGetUniformLocation(sphere_shader.get(), "lightColor");
		GLint lightPosLoc = glGetUniformLocation(sphere_shader.get(), "lightPos");

		const glm::vec3 &light_color = this->light->getColor();
		const glm::vec3 &light_pos = this->light->getPosition();

		glUniform3f(lightColorLoc, light_color.x, light_color.y, light_color.z);
		glUniform3f(lightPosLoc, light_pos.x, light_pos.y, light_pos.z);
	}
}


void Sphere::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position)
{
	sphere_shader.use();

	GLint modelLoc = glGetUniformLocation(sphere_shader.get(), "model");
	GLint viewLoc = glGetUniformLocation(sphere_shader.get(), "view");
	GLint projLoc = glGetUniformLocation(sphere_shader.get(), "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// set type (color or texture)
	GLint typeLoc = glGetUniformLocation(sphere_shader.get(), "singleColor");
	glUniform1i(typeLoc, this->type == Type::color_type ? 1 : 0);

	GLint objectColorLoc = glGetUniformLocation(sphere_shader.get(), "objectColor");
	glUniform3f(objectColorLoc, this->color.x, this->color.y, this->color.z);

	if (this->texture != nullptr) {
		glActiveTexture(GL_TEXTURE0 + this->texture->getId());
		glBindTexture(GL_TEXTURE_2D, this->texture->get());
		glUniform1i(glGetUniformLocation(sphere_shader.get(), "textureData"), this->texture->getId());
	}

	this->lighting(camera_position);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glBindVertexArray(0);
}


void Sphere::init(const char * frag, const char * vs)
{
	sphere_shader.loadFragmentShader(frag);
	sphere_shader.loadVertexShader(vs);
	sphere_shader.createProgram();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

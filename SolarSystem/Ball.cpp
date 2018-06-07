#include "Ball.h"


Ball::Ball(glm::vec3 color, GLfloat radius, GLfloat z_angle, GLfloat speed):
	sphere(color), radius(radius), z_angle(z_angle), speed(speed)
{
}


Ball::~Ball()
{
}


void Ball::update(glm::mat4 parent_model = glm::mat4(1.0))
{
	const GLfloat eps = 1e-6f;
	const GLfloat step = 1e-3f;
	this->model = parent_model;

	if (this->z_angle > eps) {
		this->model = glm::rotate(this->model, this->z_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (this->radius > eps) {
		this->model = glm::rotate(this->model, this->speed * this->angle, glm::vec3(0.0f, 1.0f, 0.0f));
		this->model = glm::translate(this->model, glm::vec3(this->radius, 0.0f, 0.0f));
	}

	for (Ball *child : this->children) {
		child->update(this->model);
	}

	this->angle += step;
}


void Ball::render(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position)
{
	this->sphere.render(this->model, view, projection, camera_position);
	for (Ball *child : this->children) {
		child->render(view, projection, camera_position);
	}
}


void Ball::addChild(Ball *b)
{
	this->children.push_back(b);
}


#include "Camera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	GLfloat yaw = -90.f, // default value
	GLfloat pitch = 0.0f // default value
): front(glm::vec3(0.0f, 0.0f, -1.0f))
{

	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;

	this->movement_speed = 12.0f; // default value
	this->mouse_sensitivity = 0.25f; // default value

	this->updateVectors();
}


Camera::~Camera()
{
}


glm::vec3 Camera::getPosition()
{
	return this->position;
}


glm::vec3 Camera::getCenter()
{
	return this->position + this->front;
}


glm::vec3 Camera::getUp()
{
	return this->up;
}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}


void Camera::processKeyboard(Movement direction, GLfloat delta_time)
{
	GLfloat velocity = this->movement_speed * delta_time;
	if (direction == FORWARD) {
		this->position += this->front * velocity;
	} else if (direction == BACKWARD) {
		this->position -= this->front * velocity;
	} else if (direction == LEFT) {
		this->position -= this->right * velocity;
	} else if (direction == RIGHT) {
		this->position += this->right * velocity;
	}
}


void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
	xoffset *= this->mouse_sensitivity;
	yoffset *= this->mouse_sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	} else if (this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}

	this->updateVectors();
}


void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->world_up));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}


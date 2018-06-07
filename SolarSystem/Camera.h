#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	glm::vec3 position, front, up, right, world_up;
	GLfloat yaw, pitch, movement_speed, mouse_sensitivity;
public:
	enum Movement { FORWARD, BACKWARD, LEFT, RIGHT };
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	virtual ~Camera();
	glm::mat4 getViewMatrix();
	void processKeyboard(Movement direction, GLfloat deltaTime);
	void processMouseMovement(GLfloat xoffset, GLfloat yoffset);
	void updateVectors();

	glm::vec3 getPosition();
	glm::vec3 getCenter();
	glm::vec3 getUp();
};


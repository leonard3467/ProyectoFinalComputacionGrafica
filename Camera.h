#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <iostream>  // Para std::cout y std::endl
#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	void setPosition(const glm::vec3& newPosition);
	void setOrientation(float newYaw, float newPitch);
	void setMovementSpeed(float newSpeed);
	void setTurnSpeed(float newTurnSpeed);
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	GLint getModoCamara(){return ModoCamara;}
	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;
	GLint ModoCamara=1;
	bool lastKeyState = false;
	bool keyProcessed = false;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};


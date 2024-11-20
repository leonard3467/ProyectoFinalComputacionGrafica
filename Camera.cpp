#include "Camera.h"

Camera::Camera() {}
// Establece una nueva posición para la cámara
void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

// Establece nueva orientación (yaw y pitch) para la cámara
void Camera::setOrientation(float newYaw, float newPitch) {
    yaw = newYaw;
    pitch = newPitch;
    update();  // Actualiza la dirección de la cámara basándose en los nuevos valores de yaw y pitch
}

// Establece una nueva velocidad de movimiento
void Camera::setMovementSpeed(float newSpeed) {
    moveSpeed = newSpeed;
}

// Establece una nueva velocidad de giro
void Camera::setTurnSpeed(float newTurnSpeed) {
    turnSpeed = newTurnSpeed;
}
Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
    GLfloat velocity = moveSpeed * deltaTime;

    // Detectar una sola pulsación en la tecla '5' para cambiar de modo
    if (keys[GLFW_KEY_5] && !lastKeyState)
    {
      
        ModoCamara += 1;
        if (ModoCamara > 4)
        {
            ModoCamara = 1;
        }
    }
    lastKeyState = keys[GLFW_KEY_5]; // Actualizar el estado de la tecla 5

    // Lógica específica para cada modo
    if (ModoCamara == 2) // Modo 2: Cámara ortográfica
    {
        // Movimiento en el plano XZ
        glm::vec3 forwardXZ = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

        if (keys[GLFW_KEY_W])
        {
            position += forwardXZ * velocity;
        }
        if (keys[GLFW_KEY_S])
        {
            position -= forwardXZ * velocity;
        }
        if (keys[GLFW_KEY_A])
        {
            position -= right * velocity;
        }
        if (keys[GLFW_KEY_D])
        {
            position += right * velocity;
        }
    }
    else if (ModoCamara == 4) // Modo 4: Perspectiva con posición dinámica
    {
             // Movimiento en perspectiva usando WASD
        if (keys[GLFW_KEY_W])
        {
            PosicionCamara4 += front * velocity; 
        }
        if (keys[GLFW_KEY_S])
        {
            PosicionCamara4 -= front * velocity; 
        }
        if (keys[GLFW_KEY_A])
        {
            PosicionCamara4 -= right * velocity; 
        }
        if (keys[GLFW_KEY_D])
        {
            PosicionCamara4 += right * velocity; 
        }
 
        
    }
    else // Otros modos (incluido Modo 1 y Modo 3)
    {
        if (keys[GLFW_KEY_W])
        {
            position += front * velocity;
        }
        if (keys[GLFW_KEY_S])
        {
            position -= front * velocity;
        }
        if (keys[GLFW_KEY_A])
        {
            position -= right * velocity;
        }
        if (keys[GLFW_KEY_D])
        {
            position += right * velocity;
        }
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}

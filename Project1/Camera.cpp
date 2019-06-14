#include "Camera.h"

Camera::Camera(glm::vec3 startPos, glm::vec3 upperStartVector, GLfloat startYaw, GLfloat startPitch, GLfloat speed, GLfloat rotation)
{
	position = startPos;
	worldUpperVector = upperStartVector;
	yaw = startYaw;
	pitch = startPitch;
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraSpeed = speed;
	rotationSpeed = rotation;

	update();
}
void Camera::update()
{
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	rightAxis = glm::normalize(glm::cross(direction, worldUpperVector));		//iloczyn wektorowy kierunku kamery oraz wektora górnego (œwiata)
	topAxis = glm::normalize(glm::cross(rightAxis, direction));			//iloczyn wektorowy prawej osi kamery oraz kierunku kamery (prawdziwy kierunek "do góry")
}

void Camera::MouseControl(GLfloat deltaX, GLfloat deltaY)
{
	deltaX = deltaX * rotationSpeed;
	deltaY = deltaY * rotationSpeed;

	yaw += deltaX;
	pitch += deltaY;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	update();
}

void Camera::KeyboardControl(bool* keys, GLfloat timeUnit)
{
	GLfloat deltaPos = cameraSpeed * timeUnit;

	if (keys[GLFW_KEY_W]) position += direction * deltaPos;
	if (keys[GLFW_KEY_S]) position -= direction * deltaPos;
	if (keys[GLFW_KEY_A]) position -= rightAxis * deltaPos;
	if (keys[GLFW_KEY_D]) position += rightAxis * deltaPos;
}


glm::mat4 Camera::ComputeCameraMatrix()
{
	return glm::lookAt(position, position + direction, topAxis);		//pozycja + kierunek --- zapewnia ¿e kamera bêdzie skierowana na punkt docelowy
}
#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>

using namespace std;

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 topAxis;
	glm::vec3 rightAxis;
	glm::vec3 worldUpperVector;

	GLfloat yaw;	// left/right
	GLfloat pitch;	// up/down

	GLfloat cameraSpeed;
	GLfloat rotationSpeed;

	void update();

public:
	Camera(glm::vec3 startPos, glm::vec3 upperStartVector, GLfloat startYaw, GLfloat startPitch, GLfloat speed, GLfloat rotation);

	void KeyboardControl(bool* keys, GLfloat timeUnit);
	void MouseControl(GLfloat deltaX, GLfloat deltaY);

	glm::mat4 ComputeCameraMatrix();
};



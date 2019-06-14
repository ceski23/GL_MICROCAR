#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Light
{
public:
	Light();
	Light(GLfloat intensivity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void use(GLfloat intensivityLoc, GLfloat colorLoc, GLfloat diffuseIntensityLoc, GLfloat directionLoc);
	void move(GLfloat xDir, GLfloat yDir, GLfloat zDir);

private:
	glm::vec3 color;
	GLfloat intensivity;
	glm::vec3 direction;
	GLfloat diffuseIntensity;

	GLfloat xDir = 0.0f;
	GLfloat yDir = 0.0f;
	GLfloat zDir = 0.0f;
};


#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	intensivity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	intensivity = aIntensity;
	diffuseIntensity = dIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	this->xDir = xDir;
	this->yDir = yDir;
	this->zDir = zDir;
}

void Light::move(GLfloat xDir, GLfloat yDir, GLfloat zDir)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void Light::use(GLfloat intensivityLoc, GLfloat colorLoc, GLfloat diffuseIntensityLoc, GLfloat directionLoc)
{
	glUniform3f(colorLoc, color.x, color.y, color.z);
	glUniform1f(intensivityLoc, intensivity);
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
}

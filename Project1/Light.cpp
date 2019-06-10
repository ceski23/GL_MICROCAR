#include "Light.h"



Light::Light()
{
	kolor = vec3(1.0f, 1.0f, 1.0f);
	intensywnoscSwiatla = 1.0f;

	direction = vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	czerwony = red;
	zielony = green;
	niebieski = blue;
	kolor = vec3(czerwony, zielony, niebieski);
	intensywnoscSwiatla = aIntensity;

	direction = vec3(xDir, yDir, zDir);
	//
	this->xDir = xDir;
	this->yDir = yDir;
	this->zDir = zDir;
	//
	diffuseIntensity = dIntensity;
}
void Light::kontrolaKlawiszy(bool* keys)
{

}
void Light::zmianaPozycjiSwiatla(GLfloat xDir, GLfloat yDir, GLfloat zDir)
{
	direction = vec3(xDir, yDir, zDir);
}
void Light::uzycieSwiatla(GLfloat lokIntensywnosciSwiatla, GLfloat lokKoloruSwiatla, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(lokKoloruSwiatla, kolor.x, kolor.y, kolor.z);
	glUniform1f(lokIntensywnosciSwiatla, intensywnoscSwiatla);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light()
{
}

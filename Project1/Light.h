#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensywnoscS, GLfloat xDir,GLfloat yDir,GLfloat zDir, GLfloat dIntensity);
	~Light();

	void uzycieSwiatla(GLfloat lokIntesywnosciSwiatla, GLfloat lokKoloruSwiatla, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	void kontrolaKlawiszy(bool* keys);
	void zmianaPozycjiSwiatla(GLfloat xDir, GLfloat yDir, GLfloat zDir);

private:
	vec3 kolor;
	GLfloat czerwony = 1.0f;
	GLfloat zielony = 1.0f;
	GLfloat niebieski = 1.0f;
	GLfloat intensywnoscSwiatla;
	GLfloat xDir = 0.0f;
	GLfloat yDir = 0.0f;
	GLfloat zDir = 0.0f;
	vec3 direction;
	GLfloat diffuseIntensity;

};


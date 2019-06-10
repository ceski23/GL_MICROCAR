#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

using namespace std;
using namespace glm;

class Camera
{
private:
	vec3 pozycja;			//pozycja startowa kamery !
	vec3 kierunek;			//kierunek kamery
	vec3 vekGorny;				//g�rna o� kamery
	vec3 vekPrawy;			//prawy wektor kamery
	vec3 vekGornySwiata;			//g�rna o� �wiata

	GLfloat yaw;		//obr�t (k�ta kamery) lewo-prawo
	GLfloat pitch;		//obr�t (k�ta kamery) g�ra-d� 

	GLfloat szybkoscRuchu;
	GLfloat szybkoscObracania;

	void update();

public:
	Camera();
	Camera(vec3 pozycjaStartowa,vec3 gornyVecStartowy, GLfloat yawStartowy, GLfloat pitchStartowy, GLfloat szybkoscRuchu, GLfloat szybkoscObracania);

	void KontrolaKlawiszy(bool* klawisze, GLfloat jednostkaCzasu);
	void KontrolaMyszy(GLfloat zmianaX, GLfloat zmianaY);

	mat4 ObliczMacierzKamery();

	~Camera();


};



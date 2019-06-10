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
	vec3 vekGorny;				//górna oœ kamery
	vec3 vekPrawy;			//prawy wektor kamery
	vec3 vekGornySwiata;			//górna oœ œwiata

	GLfloat yaw;		//obrót (k¹ta kamery) lewo-prawo
	GLfloat pitch;		//obrót (k¹ta kamery) góra-dó³ 

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



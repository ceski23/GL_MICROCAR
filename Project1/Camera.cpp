#include "Camera.h"

Camera::Camera() {}

Camera::Camera(vec3 pozycjaStartowa,vec3 gornyVecStartowy, GLfloat yawStartowy, GLfloat pitchStartowy, GLfloat szybkoscRuchu, GLfloat szybkoscObracania)
{
	pozycja = pozycjaStartowa;		//pozycja kamery
	vekGornySwiata = gornyVecStartowy;				//wektor "zwyk³y" skierowany do góry (wynosi prawie zawsze (0.0, 1.0, 0.0)
	yaw = yawStartowy;
	pitch = pitchStartowy;
	kierunek = glm::vec3(0.0f, 0.0f, -1.0f);

	this->szybkoscRuchu = szybkoscRuchu;
	this->szybkoscObracania = szybkoscObracania;

	update();
}
void Camera::update()
{
	kierunek.x = cos(radians(yaw)) * cos(radians(pitch));
	kierunek.y = sin(radians(pitch));
	kierunek.z = sin(radians(yaw)) * cos(radians(pitch));
	kierunek = normalize(kierunek);

	vekPrawy = normalize(cross(kierunek, vekGornySwiata));		//iloczyn wektorowy kierunku kamery oraz wektora górnego (œwiata)
	vekGorny = normalize(cross(vekPrawy, kierunek));			//iloczyn wektorowy prawej osi kamery oraz kierunku kamery (prawdziwy kierunek "do góry")
}

void Camera::KontrolaMyszy(GLfloat zmianaX, GLfloat zmianaY)
{
	zmianaX = zmianaX * szybkoscObracania;
	zmianaY = zmianaY * szybkoscObracania;

	yaw += zmianaX;
	pitch += zmianaY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	update();
}

void Camera::KontrolaKlawiszy(bool* klawisze, GLfloat jednostkiCzasu)
{
	GLfloat jednostkiRuchu = szybkoscRuchu * jednostkiCzasu;

	if (klawisze[GLFW_KEY_W])
		pozycja += kierunek * jednostkiRuchu;
	if (klawisze[GLFW_KEY_S])
		pozycja -= kierunek * jednostkiRuchu;
	if (klawisze[GLFW_KEY_A])
		pozycja -= vekPrawy * jednostkiRuchu;
	if (klawisze[GLFW_KEY_D])
		pozycja += vekPrawy * jednostkiRuchu;
}


glm::mat4 Camera::ObliczMacierzKamery()
{
	return lookAt(pozycja, pozycja + kierunek, vekGorny);		//pozycja + kierunek --- zapewnia ¿e kamera bêdzie skierowana na punkt docelowy
}


Camera::~Camera()
{
}

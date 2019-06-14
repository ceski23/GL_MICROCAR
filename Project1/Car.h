#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GLFW\glfw3.h>
#include "Controllable.h"
#include "Model.h"

class Car : Controllable
{
public:
	Car(GLfloat maxSpeed = 20);
	void computeMovement(GLfloat deltaTime);
	void loadModels();
	void render(GLuint uniformModel);

	virtual void reactToInput(bool* keys) override;

//private:
	GLfloat position[3] = { 0.0f, 0.0f, 0.0f };
	GLfloat azymuth = 0.0f;
	GLfloat wheelRotation = 0.0f;
	GLfloat velocity = 0.0f;
	GLfloat hoodDegree = 0.0f;
	GLfloat flapDegree = 0.0f;
	GLfloat turnAngle = 0.0f;

	bool hideBody = false;

	GLfloat maxSpeed;

	// MODELS
	Model jointModel;
	Model bodyModel;
	Model chassisModel;
	Model hoodModel;
	Model doorsModel;
	Model windowsModel;
	Model wheelModel;
};


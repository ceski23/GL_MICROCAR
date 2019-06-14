#include "Car.h"

Car::Car(GLfloat maxSpeed)
{
	this->maxSpeed = maxSpeed;
	loadModels();
}

void Car::computeMovement(GLfloat deltaTime)
{
	GLfloat angle = (velocity * deltaTime) / 1.0f;
	wheelRotation += glm::degrees(angle);
	wheelRotation = fmod(wheelRotation, 360.0f);

	GLfloat roadLength = (velocity * deltaTime);
	position[0] += roadLength * sin(glm::radians(azymuth * 0.5));
	position[1] += roadLength * cos(glm::radians(azymuth * 0.5));
}

void Car::loadModels()
{
	jointModel = Model();
	jointModel.LoadModel("Models/jointNew.obj");

	bodyModel = Model();
	bodyModel.LoadModel("Models/nadwozieRdy.obj");

	chassisModel = Model();
	chassisModel.LoadModel("Models/podwozieCzarka.obj");

	hoodModel = Model();
	hoodModel.LoadModel("Models/maska.obj");

	doorsModel = Model();
	doorsModel.LoadModel("Models/tylneDrzwi.obj");

	windowsModel = Model();
	windowsModel.LoadModel("Models/okna.obj");

	wheelModel = Model();
	wheelModel.LoadModel("Models/koloCzarka3.obj");
}

void Car::render(GLuint uniformModel)
{
	glm::mat4 model(1.0f);

	// PODWOZIE
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
	model = glm::translate(model, glm::vec3(0.0f + position[0], 1.33f, -0.85f + position[1]));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	chassisModel.RenderModel();

	// KO£O LP
	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
	model = glm::translate(model, glm::vec3(1.83f + position[0], 0.52f, 3.3f + position[1]));
	model = glm::rotate(model, glm::radians(turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	wheelModel.RenderModel();

	// KO£O PP
	glTranslatef(2.0f, 2.0f, 2.0f);
	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
	model = glm::translate(model, glm::vec3(-1.83f + position[0], 0.52f, 3.3f + position[1]));
	model = glm::rotate(model, glm::radians(GLfloat(180.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	wheelModel.RenderModel();

	// KO£O LT
	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
	model = glm::translate(model, glm::vec3(1.83f + position[0], 0.52f, -3.74f + position[1]));
	model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	wheelModel.RenderModel();

	// KO£O PT
	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
	model = glm::translate(model, glm::vec3(-1.83f + position[0], 0.52f, -3.74f + position[1]));
	model = glm::rotate(model, glm::radians(GLfloat(180.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	wheelModel.RenderModel();

	// JOINTY
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f + position[0], 0.85f, 4.38f + position[1]));
	model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jointModel.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f + position[0], 0.85f, 4.38f + position[1]));
	model = glm::rotate(model, glm::radians((GLfloat)180.0), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians((GLfloat)5.0), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-wheelRotation + 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jointModel.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f + position[0], 0.55f, 1.06f + position[1]));
	model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jointModel.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f + position[0], 0.55f, 1.06f + position[1]));
	model = glm::rotate(model, glm::radians((GLfloat)180.0), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-wheelRotation + (GLfloat)90.0), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jointModel.RenderModel();


	if (!hideBody) {
		// NADWOZIE
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(0.0f + position[0], 1.33f, -0.85f + position[1]));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bodyModel.RenderModel();

		// MASKA
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(0.0f + position[0], 3.17f, 2.372f + position[1]));
		model = glm::rotate(model, glm::radians(-hoodDegree), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hoodModel.RenderModel();

		// TYLNE DRZWI
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(-0.05f + position[0], 5.17f, -6.4f + position[1]));
		model = glm::rotate(model, glm::radians(flapDegree), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		doorsModel.RenderModel();

		// OKNA
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
			model = glm::translate(model, glm::vec3(0.0f + position[0], 1.33f, -0.85f + position[1]));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			windowsModel.RenderModel();
		glDisable(GL_BLEND);
	}
}

void Car::reactToInput(bool* keys)
{
	if (keys[GLFW_KEY_UP] && velocity < maxSpeed) velocity += 0.1f;
	if (keys[GLFW_KEY_DOWN] && velocity > -maxSpeed) velocity -= 0.1f;
	if (keys[GLFW_KEY_SPACE]) velocity = 0.0f;

	if (keys[GLFW_KEY_1] && hoodDegree < 90.0f) hoodDegree += 1.0f;
	if (keys[GLFW_KEY_2] && hoodDegree > 0.0f) hoodDegree -= 1.0f;

	if (keys[GLFW_KEY_3] && flapDegree < 90.0f) flapDegree += 1.0f;
	if (keys[GLFW_KEY_4] && flapDegree > 0.0f) flapDegree -= 1.0f;

	if (keys[GLFW_KEY_LEFT] && turnAngle < 30.0f) turnAngle += 0.2f;
	if (keys[GLFW_KEY_RIGHT] && turnAngle > -30.0f) turnAngle -= 0.2f;

	hideBody = keys[GLFW_KEY_B];
}


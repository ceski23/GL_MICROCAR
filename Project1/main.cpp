#pragma once
#define STB_IMAGE_IMPLEMENTATION	//odpalenie stb_image do czytania zdjêæ jako tekstury 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <sstream>

#include <GL\glew.h>

#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Mesh.h"
#include "Floor.h"
#include "Car.h"


GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat timeCounter = 0.0f;
int frameCount = 0;


// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";



void computeFPS(GLFWwindow* pWindow)
{
	GLfloat now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;
	timeCounter += deltaTime;
	frameCount++;

	if (timeCounter >= 1.0) {
		double fps = double(frameCount) / timeCounter;

		std::stringstream ss;
		ss << " [" << fps << " FPS]";

		glfwSetWindowTitle(pWindow, ss.str().c_str());

		frameCount = 0;
		timeCounter = 0;
	}
}

int main()
{
	Window mainWindow(1200, 800);
	mainWindow.Initialize();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0;
	GLuint uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	std::vector<Shader> shaderList;
	shaderList.push_back(*shader1);

	Camera camera(glm::vec3(-7.0f, 7.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -50.0f, -20.0f, 10.0f, 0.3f);
	Light mainLight(0.5f, 2.0f, -1.0f, -2.0f, 1.0f);

	Floor floor(20.0f);
	Car car;

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		computeFPS(mainWindow.mainWindow);

		// Get + Handle User Input
		glfwPollEvents();

		camera.KeyboardControl(mainWindow.getsKeys(), deltaTime);
		camera.MouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformDirection = shaderList[0].GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();

		mainLight.use(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);		

		floor.render(camera, projection, uniformProjection, uniformView, uniformModel);

		car.reactToInput(mainWindow.getsKeys());
		car.computeMovement(deltaTime);
		car.render(uniformModel);

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
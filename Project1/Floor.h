#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

class Floor
{
public:
	Floor(GLfloat size);
	void render(Camera camera, glm::mat4 projection, GLuint uniformProjection, GLuint uniformView, GLuint uniformModel);

private:
	Mesh mesh;
	Texture texture = Texture("Textures/floor.png");
};


#include "Floor.h"

Floor::Floor(GLfloat size)
{
	unsigned int floorIndices[] = {
		0,2,1,
		1,2,3
	};

	GLfloat floorVertices[] = {
		-size,  0.0f, -size,   0.0f,  0.0f,   0.0f,  0.0f,  0.0f,
		 size,  0.0f, -size,  size,  0.0f,	0.0f,  0.0f,  0.0f,
		-size,  0.0f,  size,   0.0f,  size,	0.0f,  0.0f,  0.0f,
		 size,  0.0f,  size,  size,  size,  0.0f,  0.0f,  0.0f
	};

	mesh.CreateMesh(floorVertices, floorIndices, 32, 6);

	texture.LoadTextureA();
}

void Floor::render(Camera camera, glm::mat4 projection, GLuint uniformProjection, GLuint uniformView, GLuint uniformModel)
{
	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, -0.35f, 0.0f));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.ComputeCameraMatrix()));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	mesh.RenderMesh();
}

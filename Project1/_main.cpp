#include "MainInclude.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

Mesh *floorMesh;

Model engine;
Model joint;
Model kolo;
Model nadwozie, maska, tylneDrzwi, okna;
Model podwozie;


GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLfloat degree = 0.0f;
GLfloat speed = 1.0f;
// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


void CreateFloor()
{
	unsigned int floorIndices[] = {
		0,2,1,
		1,2,3
	};

	GLfloat floorVertices[] = {
		-20.0f,0.0f,-20.0f,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		20.0f,0.0f,-20.0f,20.0f,0.0f,	 0.0f,0.0f,0.0f,
		-20.0f,0.0f,20.0f,0.0f,20.0f,	 0.0f,0.0f,0.0f,
		20.0f,0.0f,20.0f,20.0f,20.0f,	 0.0f,0.0f,0.0f
	};
	floorMesh = new Mesh();
	floorMesh->CreateMesh(floorVertices, floorIndices, 32, 6);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1200, 800);
	mainWindow.Initialise();

	CreateFloor();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/grass.png");
	dirtTexture.LoadTextureA();

	mainLight = Light(1.0f,1.0f,1.0f,1.0f,2.0f,-1.0f,-2.0f,1.0f);
	joint = Model();
	joint.LoadModel("Models/jointNew.obj");

	nadwozie = Model();
	nadwozie.LoadModel("Models/nadwozieRdy.obj");
	podwozie = Model();
	podwozie.LoadModel("Models/podwozie2.obj");
	maska = Model();
	maska.LoadModel("Models/maska.obj");
	tylneDrzwi = Model();
	tylneDrzwi.LoadModel("Models/tylneDrzwi.obj");
	okna = Model();
	okna.LoadModel("Models/okna.obj");


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity=0, uniformAmbientColour=0,
		uniformDirection = 0, uniformDiffuseIntensity = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; 
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		camera.KontrolaKlawiszy(mainWindow.getsKeys(), deltaTime);
		camera.KontrolaMyszy(mainWindow.getXChange(), mainWindow.getYChange());
		mainLight.kontrolaKlawiszy(mainWindow.getsKeys());
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

		mainLight.uzycieSwiatla(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

		bool *keys=mainWindow.getsKeys();
		if (degree > 359.0f)
		{
			degree = 0.0f;
		}
		if (keys[GLFW_KEY_Y]) speed += 1.0f;
		if (keys[GLFW_KEY_T]) speed -= 1.0f;

		degree += deltaTime * 10 * speed;

		glm::mat4 model(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, -0.35f, 0.0f));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.ObliczMacierzKamery()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		floorMesh->RenderMesh();



////////////////////////////////////////////////////////////////////////////////////
		


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.33f, -4.35f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		nadwozie.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.33f, -4.35f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		podwozie.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 3.17f, -1.128f));
		model = glm::rotate(model, glm::radians(-degree), glm::vec3(1.0f, 0.0f, 0.0f));	//DORÓBCIE SOBIE NA KLAWISZ PODNOSZENIE MASKI
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		maska.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.05f, 5.17f, -9.9f));
		model = glm::rotate(model, glm::radians(degree), glm::vec3(1.0f, 0.0f, 0.0f));	//DORÓBCIE SOBIE NA KLAWISZ PODNOSZENIE TYLNYCH DRZWI
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tylneDrzwi.RenderModel();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.33f, -4.35f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		okna.RenderModel();
		glDisable(GL_BLEND);



///////////////////////////////////////////////////////////////////////////////////

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
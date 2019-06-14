#include "Main.h"

#define M_PI 3.1415926535897932384626433832795

const float toRadians = M_PI / 180.0f;
const float toDegrees = 180.0f / M_PI;

Window mainWindow;
std::vector<Shader> shaderList;
//Camera camera;

Texture floorTexture;

Light mainLight;

Mesh *floorMesh;

Model engine;
Model joint;
Model kolo;
Model nadwozie;
Model podwozie;
Model maska;
Model tylneDrzwi;
Model okna;


//////////////// FPS ////////////////
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat timeCounter = 0.0f;
int frameCount = 0;
/////////////////////////////////////


GLfloat wheelRotation = 0.0f;
GLfloat velocity = 0.0f;

GLfloat maskDegree = 0.0f;
GLfloat flapDegree = 0.0f;
GLfloat turnAngle = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


GLfloat pos[2] = { 0.0f, 0.0f };
GLfloat azymuth = 0.0f;

void computeMovement() {
	GLfloat angle = (velocity * deltaTime) / 1.0f;
	wheelRotation += angle * toDegrees;
	wheelRotation = fmod(wheelRotation, 360.0f);

	double roadLength = velocity * deltaTime;
	/*pos[0] += roadLength * sin((azymuth * 0.5) * toRadians);
	pos[1] += roadLength * cos((azymuth * 0.5) * toRadians);*/

	/*azymuth += turnAngle * deltaTime * (velocity * 0.1f);
	azymuth = fmod(azymuth, 360.0f);*/
}


void CreateFloor(float size)
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

	floorMesh = new Mesh();
	floorMesh->CreateMesh(floorVertices, floorIndices, 32, 6);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void showFPS(GLFWwindow* pWindow)
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
	mainWindow = Window(1200, 800);
	mainWindow.Initialise();

	CreateFloor(100.0f);
	CreateShaders();

	//camera = Camera(glm::vec3(0.0f, 70.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 00.0f, -90.0f, 5.0f, 0.5f);
	Camera camera = Camera(glm::vec3(-7.0f, 7.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -50.0f, -20.0f, 10.0f, 0.3f);

	floorTexture = Texture("Textures/floor.png");
	floorTexture.LoadTextureA();

	mainLight = Light(0.5f,2.0f,-1.0f,-2.0f,1.0f);
	joint = Model();
	joint.LoadModel("Models/jointNew.obj");

	nadwozie = Model();
	nadwozie.LoadModel("Models/nadwozieRdy.obj");
	podwozie = Model();
	podwozie.LoadModel("Models/podwozieCzarka.obj");
	maska = Model();
	maska.LoadModel("Models/maska.obj");
	tylneDrzwi = Model();
	tylneDrzwi.LoadModel("Models/tylneDrzwi.obj");
	okna = Model();
	okna.LoadModel("Models/okna.obj");
	kolo = Model();
	kolo.LoadModel("Models/koloCzarka3.obj");


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity=0, uniformAmbientColour=0,
		uniformDirection = 0, uniformDiffuseIntensity = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		showFPS(mainWindow.mainWindow);

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

		bool *keys=mainWindow.getsKeys();		
		
		if (keys[GLFW_KEY_UP] && velocity < 20.0f)
			velocity += 0.1f;
		
		if (keys[GLFW_KEY_DOWN] && velocity > -20.0f)
			velocity -= 0.1f;

		if (keys[GLFW_KEY_SPACE])
			velocity = 0.0f;


		if (keys[GLFW_KEY_1] && maskDegree < 90.0f)
			maskDegree += 1.0f;

		if (keys[GLFW_KEY_2] && maskDegree > 0.0f)
			maskDegree -= 1.0f;


		if (keys[GLFW_KEY_3] && flapDegree < 90.0f)
			flapDegree += 1.0f;

		if (keys[GLFW_KEY_4] && flapDegree > 0.0f)
			flapDegree -= 1.0f;


		if (keys[GLFW_KEY_LEFT] && turnAngle < 30.0f)
			turnAngle += 0.2f;

		if (keys[GLFW_KEY_RIGHT] && turnAngle > -30.0f)
			turnAngle -= 0.2f;



		glm::mat4 model(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, -0.35f, 0.0f));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.ComputeCameraMatrix()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		floorTexture.UseTexture();
		floorMesh->RenderMesh();

		computeMovement();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.33f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		engine.RenderModel();
		
		if (!keys[GLFW_KEY_B])
		{
			// NADWOZIE
			model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
			model = glm::translate(model, glm::vec3(0.0f + pos[0], 1.33f, -0.85f + pos[1]));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			nadwozie.RenderModel();

			// MASKA
			model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
			model = glm::translate(model, glm::vec3(0.0f + pos[0], 3.17f, 2.372f + pos[1]));
			model = glm::rotate(model, glm::radians(-maskDegree), glm::vec3(1.0f, 0.0f, 0.0f));	
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			maska.RenderModel();

			// TYLNE DRZWI
			model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
			model = glm::translate(model, glm::vec3(-0.05f + pos[0], 5.17f, -6.4f + pos[1]));
			model = glm::rotate(model, glm::radians(flapDegree), glm::vec3(1.0f, 0.0f, 0.0f));	
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			tylneDrzwi.RenderModel();

			// OKNA
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
			model = glm::translate(model, glm::vec3(0.0f + pos[0], 1.33f, -0.85f + pos[1]));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			okna.RenderModel();
			glDisable(GL_BLEND);
		}

		// PODWOZIE
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(0.0f + pos[0], 1.33f, -0.85f + pos[1]));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		podwozie.RenderModel();

		// KO£O LP
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(1.83f + pos[0], 0.52f, 3.3f + pos[1]));
		model = glm::rotate(model, glm::radians(turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		kolo.RenderModel();

		// KO£O PP
		glTranslatef(2.0f, 2.0f, 2.0f);
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(-1.83f + pos[0], 0.52f, 3.3f + pos[1]));
		model = glm::rotate(model, glm::radians(GLfloat(180.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		kolo.RenderModel();

		// KO£O LT
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(1.83f + pos[0], 0.52f, -3.74f + pos[1]));
		model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		kolo.RenderModel();

		// KO£O PT
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(azymuth), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.7f));		// PRZESUNIECIE
		model = glm::translate(model, glm::vec3(-1.83f + pos[0], 0.52f, -3.74f + pos[1]));
		model = glm::rotate(model, glm::radians(GLfloat(180.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-wheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		kolo.RenderModel();



////////////////////////////////////////////////////////////////////////////////////
		// Dodaæ 3.5 do osi Z
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f + pos[0], 0.85f, 4.38f + pos[1])); // -2.82f
		model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		joint.RenderModel();

		model = glm::mat4(1.0f);																				//jointy
		model = glm::translate(model, glm::vec3(0.0f + pos[0], 0.85f, 4.38f + pos[1]));
		model = glm::rotate(model, glm::radians((GLfloat)180.0), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((GLfloat)5.0), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-wheelRotation+ (GLfloat)90.0), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		joint.RenderModel();

		model = glm::mat4(1.0f);																				//jointy
		model = glm::translate(model, glm::vec3(0.0f + pos[0], 0.55f, 1.06f + pos[1]));
		model = glm::rotate(model, glm::radians((GLfloat)-5.0), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(wheelRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		joint.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f + pos[0], 0.55f, 1.06f + pos[1]));
		model = glm::rotate(model, glm::radians((GLfloat)180.0), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-wheelRotation+(GLfloat)90.0), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		joint.RenderModel();
///////////////////////////////////////////////////////////////////////////////////

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
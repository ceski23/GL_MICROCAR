#pragma once
#define STB_IMAGE_IMPLEMENTATION	//odpalenie stb_image do czytania zdjêæ jako tekstury 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <sstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

#include "Model.h"
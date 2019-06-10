#pragma once
#include <GL/glew.h>
#include "stbCheck.h"
class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	bool LoadTexture();
	bool LoadTextureA();	//for alpha channels
	void UseTexture();
	void ClearTexture();
	~Texture();
private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};


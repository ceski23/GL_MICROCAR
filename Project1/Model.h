#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"
using namespace std;

class Model
{
public:
	void LoadModel(const string& fileName);
	void RenderModel();
	void ClearModel();

private:

	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	void LoadMaterials(const aiScene *scene);

	vector<Mesh*> meshList;
	vector<Texture*> textureList;
	vector<unsigned int> meshToTex;
};


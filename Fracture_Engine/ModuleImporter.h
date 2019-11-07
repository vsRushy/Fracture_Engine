#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "IL/ilu.h"
#include "IL/ilut.h"

#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment (lib, "Devil/libx86/ILU.lib")
#pragma comment (lib, "Devil/libx86/ILUT.lib")

#define TEXTURE_ROOT_PATH "Assets/Textures/"

#define LIBRARY_MESH_PATH "Library/Meshes/"
#define LIBRARY_TEXTURE_PATH "Library/Textures/"

#include "Mesh.h"

class GameObject;

class Texture;

class ModuleImporter : public Module
{
public:
	ModuleImporter(bool start_enabled = true);
	~ModuleImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadDroppedFile(const char* path);

	void LoadModel(const char* path);
	void LoadSceneNode(const aiScene*, aiNode* node, GameObject* parent);
	Texture* LoadTexture(const char* path);

	Mesh* LoadMesh(aiMesh* ai_mesh);

	bool SaveMesh(Mesh* mesh, const char* file_name, std::string& file_output);
	bool SaveTexture();
};

#endif /* __MODULE_IMPORTER__ */
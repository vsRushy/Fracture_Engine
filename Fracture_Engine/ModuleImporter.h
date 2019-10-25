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

class GameObject;
class Mesh;

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
	void LoadSceneNode(const aiScene*, aiNode* node);
	Texture* LoadTexture(const char* path);


	Texture* LoadTextureCheckered();

	// ------------------

	Mesh* LoadMesh(aiMesh* ai_mesh);

	GameObject* g_o = nullptr;

private:
	const char* texture_root_path = "";
};
#endif /* __MODULE_IMPORTER__ */
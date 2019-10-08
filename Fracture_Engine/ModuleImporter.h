#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Module.h"
#include "Globals.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

struct Mesh
{
	uint id_vertices = -1; // unique vertex in VRAM
	uint num_vertices = 0u;
	float* vertices = nullptr;

	uint id_indices = -1; // index in VRAM
	uint num_indices = 0u;
	uint* indices = nullptr;

	uint id_normals = -1;
	uint num_normals = 0u;
	float* normals = nullptr;

	uint id_uvs = -1;
	uint num_uvs = 0u;
	float* uvs = nullptr;

	uint id_colors = -1;
	uint num_colors = 0u;
	float* colors = nullptr;

	// ------------------------------------------------

	void DrawMeshVertices(const float& size) const;
	void DrawMeshNormals(const float& width) const;
};

class ModuleImporter : public Module
{
public:
	ModuleImporter(bool start_enabled = true);
	~ModuleImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(const char*);
private:

};
#endif /* __MODULE_IMPORTER__ */
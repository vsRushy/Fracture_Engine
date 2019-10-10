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

struct Mesh
{
	~Mesh();

	// ------------------------------------------------

	bool draw_mesh_lines = false;
	float mesh_lines_width = 3.0f;
	
	bool draw_mesh_vertices = false;
	float mesh_vertices_size = 9.0f;

	bool draw_mesh_vertex_normals = false;
	float mesh_vertex_normals_width = 2.0f;

	bool draw_mesh_face_normals = false;
	float mesh_face_normals_width = 2.0f;

	// ------------------------------------------------

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

	uint id_textures = -1;

	// ------------------------------------------------

	float* center_face_point = nullptr;
	float* center_face_normal_point = nullptr;

	// ------------------------------------------------
	void DrawMeshLines(const float& size) const;
	void DrawMeshVertices(const float& size) const;
	void DrawMeshVertexNormals(const float& width) const;
	void DrawMeshFaceNormals(const float& width) const;
};

class ModuleImporter : public Module
{
public:
	ModuleImporter(bool start_enabled = true);
	~ModuleImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(const char* path);
	uint LoadTexture(const char* path);

	void AssignTextureToModel(Mesh* mesh, uint texture_id);
private:

};
#endif /* __MODULE_IMPORTER__ */
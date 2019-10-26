#ifndef __MESH_H__
#define __MESH_H__

#include "Globals.h"

class aiMesh;
class par_shapes_mesh;

class Mesh
{
public:
	Mesh();
	~Mesh();

	/* To load from Assimp */
	void LoadVertices(aiMesh* mesh);
	void LoadFaces(aiMesh* mesh);
	void LoadNormals(aiMesh* mesh);
	void LoadUVs(aiMesh* mesh);

	/* To load from Par Shapes */
	void LoadVertices(par_shapes_mesh* mesh);
	void LoadFaces(par_shapes_mesh* mesh);
	void LoadNormals(par_shapes_mesh* mesh);
	void LoadUVs(par_shapes_mesh* mesh);

	void CreateBuffers();

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
	uint uvs_dimension = 0u;
	float* uvs = nullptr;

	// ------------------------------------------------

	float* center_face_point = nullptr;
	float* center_face_normal_point = nullptr;
};

#endif /* __MESH_H__ */
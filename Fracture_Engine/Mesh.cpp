#include "Mesh.h"
#include "Assimp/include/scene.h"
#include "glmath.h"
#include "GL/glew.h"

#include "Application.h"
#include "ModuleFileSystem.h"

#include "PerfTimer.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	RELEASE_ARRAY(vertices);
	RELEASE_ARRAY(indices);
	RELEASE_ARRAY(normals);
	RELEASE_ARRAY(uvs);

	RELEASE_ARRAY(center_face_point);
	RELEASE_ARRAY(center_face_normal_point);

	/*glDeleteBuffers(num_vertices, &id_vertices);
	glDeleteBuffers(num_indices, &id_indices);
	glDeleteBuffers(num_normals, &id_normals);
	glDeleteBuffers(num_uvs, &id_uvs);*/
}

Mesh* Mesh::LoadMesh(aiMesh* ai_mesh)
{
	PerfTimer timer;
	timer.Start();

	Mesh* m = new Mesh();

	m->LoadVertices(ai_mesh);
	m->LoadFaces(ai_mesh);
	m->LoadNormals(ai_mesh);
	m->LoadUVs(ai_mesh);

	m->CreateBuffers();

	LOG(LOG_INFORMATION, "Mesh loaded in %lf milliseconds", timer.ReadMs());

	return m;
}

Mesh* Mesh::LoadMesh(par_shapes_mesh* p_s_mesh)
{
	Mesh* m = new Mesh();

	/*par_shapes_unweld(p_s_mesh, true);
	par_shapes_compute_normals(p_s_mesh);*/

	m->LoadVertices(p_s_mesh);
	m->LoadFaces(p_s_mesh);
	m->LoadNormals(p_s_mesh);
	m->LoadUVs(p_s_mesh);

	m->CreateBuffers();

	return m;
}

Mesh* Mesh::LoadOwnMesh(std::string name)
{
	PerfTimer timer;
	timer.Start();

	Mesh* own_mesh = new Mesh();

	char* buff;
	std::string path;
	path.append(LIBRARY_MESH_PATH).append(name.c_str());;
	if (App->file_system->Load(path.c_str(), &buff) != 0)
	{
		char* cursor = buff;

		uint ranges[4];
		uint bytes = sizeof(ranges);
		memcpy(ranges, cursor, bytes);

		own_mesh->num_indices = ranges[0];
		own_mesh->num_vertices = ranges[1];
		own_mesh->num_normals = ranges[2];
		own_mesh->num_uvs = ranges[3];

		cursor += bytes;
		bytes = sizeof(uint) * own_mesh->num_indices;
		own_mesh->indices = new uint[own_mesh->num_indices];
		memcpy(own_mesh->indices, cursor, bytes);

		cursor += bytes;
		bytes = sizeof(float) * own_mesh->num_vertices * 3;
		own_mesh->vertices = new float[own_mesh->num_vertices * 3];
		memcpy(own_mesh->vertices, cursor, bytes);

		cursor += bytes;
		bytes = sizeof(float) * own_mesh->num_normals * 3;
		own_mesh->normals = new float[own_mesh->num_normals * 3];
		memcpy(own_mesh->normals, cursor, bytes);

		cursor += bytes;
		bytes = sizeof(float) * own_mesh->num_uvs * 2;
		own_mesh->uvs = new float[own_mesh->num_uvs * 2];
		memcpy(own_mesh->uvs, cursor, bytes);

		own_mesh->CreateBuffers();

		RELEASE_ARRAY(buff);
	}

	LOG(LOG_INFORMATION, "Own mesh loaded in %lf milliseconds", timer.ReadMs());

	return own_mesh;
}

void Mesh::LoadVertices(aiMesh* mesh)
{
	num_vertices = mesh->mNumVertices;
	vertices = new float[num_vertices * 3];
	memcpy(vertices, mesh->mVertices, sizeof(float) * num_vertices * 3);
	LOG(LOG_INFORMATION, "New mesh with %d vertices", num_vertices);
}

void Mesh::LoadVertices(par_shapes_mesh* mesh)
{
	num_vertices = (uint)mesh->npoints;
	vertices = new float[num_vertices * 3];
	memcpy(vertices, mesh->points, sizeof(float) * num_vertices * 3);
	LOG(LOG_INFORMATION, "New mesh with %d vertices", num_vertices);
}

void Mesh::LoadFaces(par_shapes_mesh* mesh)
{
	num_indices = mesh->ntriangles * 3;
	indices = new uint[num_indices];
	memcpy(indices, mesh->triangles, sizeof(uint) * num_indices);
	LOG(LOG_INFORMATION, "New mesh with %d indices", num_indices);
}

void Mesh::LoadNormals(par_shapes_mesh* mesh)
{
	if (mesh->normals != nullptr) 
	{
		num_normals = mesh->npoints;
		normals = new float[num_normals * 3];
		memcpy(normals, mesh->normals, sizeof(float) * num_normals * 3);
	}

	LOG(LOG_INFORMATION, "New mesh with %d normals", num_normals);
}

void Mesh::LoadUVs(par_shapes_mesh* mesh)
{
	if (mesh->tcoords != nullptr)
	{
		num_uvs = mesh->npoints;
		uvs = new float[num_uvs * 2];
		memcpy(uvs, mesh->tcoords, sizeof(float) * num_uvs * 2);
	}
	
	LOG(LOG_INFORMATION, "New mesh loaded with %d Texture Coords", num_uvs);
}

void Mesh::LoadFaces(aiMesh* mesh)
{
	if (mesh->HasFaces())
	{
		num_indices = mesh->mNumFaces * 3;
		indices = new uint[num_indices]; // assume each face is a triangle
		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
			{
				LOG(LOG_WARNING, "Geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}

		LOG(LOG_INFORMATION, "New mesh with %d indices", num_indices);
	}
}

void Mesh::LoadNormals(aiMesh* mesh)
{
	if (mesh->HasNormals())
	{
		num_normals = mesh->mNumVertices;
		normals = new float[num_normals * 3];
		memcpy(normals, mesh->mNormals, sizeof(float) * num_normals * 3);
		LOG(LOG_INFORMATION, "New mesh with %d normals", num_normals);

		center_face_point = new float[num_indices];
		center_face_normal_point = new float[num_indices];
		for (uint i = 0; i < num_indices; i += 3)
		{
			uint index1 = indices[i] * 3;
			uint index2 = indices[i + 1] * 3;
			uint index3 = indices[i + 2] * 3;

			vec3 x0(vertices[index1], vertices[index1 + 1], vertices[index1 + 2]);
			vec3 x1(vertices[index2], vertices[index2 + 1], vertices[index2 + 2]);
			vec3 x2(vertices[index3], vertices[index3 + 1], vertices[index3 + 2]);

			vec3 v0 = x0 - x2;
			vec3 v1 = x1 - x2;
			vec3 n = cross(v0, v1);

			vec3 normalized = normalize(n);

			center_face_point[i] = (x0.x + x1.x + x2.x) / 3;
			center_face_point[i + 1] = (x0.y + x1.y + x2.y) / 3;
			center_face_point[i + 2] = (x0.z + x1.z + x2.z) / 3;

			center_face_normal_point[i] = normalized.x;
			center_face_normal_point[i + 1] = normalized.y;
			center_face_normal_point[i + 2] = normalized.z;
		}
	}
}

void Mesh::LoadUVs(aiMesh* mesh)
{
	if (mesh->HasTextureCoords(0))
	{
		num_uvs = mesh->mNumVertices;
		uvs_dimension = mesh->mNumUVComponents[0];
		if (uvs_dimension == 2u)
		{
			uvs = new float[num_vertices * uvs_dimension];
			for (uint i = 0u; i < num_vertices; ++i)
			{
				memcpy(&uvs[i * uvs_dimension], &mesh->mTextureCoords[0][i], sizeof(float) * uvs_dimension);
			}
		}
	}

	LOG(LOG_INFORMATION, "New mesh loaded with %d Texture Coords", num_uvs);
}

void Mesh::CreateBuffers()
{
	/* VBO vertices */
	glGenBuffers(1, &id_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);

	/* IBO */
	glGenBuffers(1, &id_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * num_indices, indices, GL_STATIC_DRAW);

	/* Normals */
	glGenBuffers(1, &id_normals);
	glBindBuffer(GL_ARRAY_BUFFER, id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_normals * 3, normals, GL_STATIC_DRAW);

	/* UVs */
	glGenBuffers(1, &id_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, id_uvs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_uvs * 2, uvs, GL_STATIC_DRAW);

	LOG(LOG_INFORMATION, "New mesh buffers created");
}


#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	delete[] vertices;
	delete[] indices;
	delete[] normals;
	delete[] uvs;

	delete[] center_face_point;
	delete[] center_face_normal_point;

	vertices = nullptr;
	indices = nullptr;
	normals = nullptr;
	uvs = nullptr;

	center_face_point = nullptr;
	center_face_normal_point = nullptr;

	/*glDeleteBuffers(num_vertices, &id_vertices);
	glDeleteBuffers(num_indices, &id_indices);
	glDeleteBuffers(num_normals, &id_normals);
	glDeleteBuffers(num_uvs, &id_uvs);*/
}


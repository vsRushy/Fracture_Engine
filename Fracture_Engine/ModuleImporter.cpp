#include "GL/glew.h"

#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleSceneIntro.h"

ModuleImporter::ModuleImporter(bool start_enabled) : Module(start_enabled)
{

}

ModuleImporter::~ModuleImporter()
{}

// -----------------------------------------------------------------
bool ModuleImporter::Init()
{
	bool ret = true;

	/* Assimp log stream */
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	/* Initializate DevIL */
	ilInit();
	iluInit();
	ilEnable(IL_CONV_PAL);
	ilutEnable(ILUT_OPENGL_CONV);
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	return ret;
}

// -----------------------------------------------------------------
bool ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

// -----------------------------------------------------------------
update_status ModuleImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleImporter::LoadModel(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		LOG(LOG_INFORMATION, "New scene with %d mesh(es)", scene->mNumMeshes);
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			LOG(LOG_INFORMATION, "Operating with mesh number %d", i);

			Mesh* m = new Mesh();
			aiMesh* new_mesh = scene->mMeshes[i];

			/* Copy vertices */
			m->num_vertices = new_mesh->mNumVertices;
			m->vertices = new float[m->num_vertices * 3];
			memcpy(m->vertices, new_mesh->mVertices, sizeof(float) * m->num_vertices * 3);
			LOG(LOG_INFORMATION, "New mesh with %d vertices", m->num_vertices);

			/* Copy faces */
			if (new_mesh->HasFaces())
			{
				m->num_indices = new_mesh->mNumFaces * 3;
				m->indices = new uint[m->num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; i++)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG(LOG_WARNING, "Geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&m->indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}

				LOG(LOG_INFORMATION, "New mesh with %d indices", m->num_indices);
			}

			/* Copy normals */
			if (new_mesh->HasNormals())
			{
				m->num_normals = new_mesh->mNumVertices;
				m->normals = new float[m->num_normals * 3];
				memcpy(m->normals, new_mesh->mNormals, sizeof(float) * m->num_normals * 3);
				LOG(LOG_INFORMATION, "New mesh with %d normals", m->num_normals);

				m->center_face_point = new float[m->num_indices];
				m->center_face_normal_point = new float[m->num_indices];
				for (uint i = 0; i < m->num_indices; i+= 3)
				{
					uint index1 = m->indices[i] * 3;
					uint index2 = m->indices[i + 1] * 3;
					uint index3 = m->indices[i + 2] * 3;

					vec3 x0(m->vertices[index1], m->vertices[index1 + 1], m->vertices[index1 + 2]);
					vec3 x1(m->vertices[index2], m->vertices[index2 + 1], m->vertices[index2 + 2]);
					vec3 x2(m->vertices[index3], m->vertices[index3 + 1], m->vertices[index3 + 2]);

					vec3 v0 = x0 - x2;
					vec3 v1 = x1 - x2;
					vec3 n = cross(v0, v1);

					vec3 normalized = normalize(n);

					m->center_face_point[i] = (x0.x + x1.x + x2.x) / 3;
					m->center_face_point[i + 1] = (x0.y + x1.y + x2.y) / 3;
					m->center_face_point[i + 2] = (x0.z + x1.z + x2.z) / 3;

					m->center_face_normal_point[i] = normalized.x;
					m->center_face_normal_point[i + 1] = normalized.y;
					m->center_face_normal_point[i + 2] = normalized.z;
				}
			}

			/* Copy UVs */
			if (new_mesh->HasTextureCoords(0))
			{
				m->num_uvs = new_mesh->mNumVertices;
				m->uvs = new float[m->num_uvs * 3];
				memcpy(m->uvs, new_mesh->mTextureCoords[0], sizeof(float) * m->num_uvs * 3);
			}
			LOG(LOG_INFORMATION, "New mesh with %d UVs", m->num_uvs);
			
			/* VBO vertices */
			glGenBuffers(1, &(m->id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m->id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_vertices * 3, m->vertices, GL_STATIC_DRAW);
			
			/* IBO */
			glGenBuffers(1, &m->id_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->id_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m->num_indices, m->indices, GL_STATIC_DRAW);

			/* Normals */
			glGenBuffers(1, &m->id_normals);
			glBindBuffer(GL_ARRAY_BUFFER, m->id_normals);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_normals * 3, m->normals, GL_STATIC_DRAW);

			/* UVs */
			glGenBuffers(1, &m->id_uvs);
			glBindBuffer(GL_ARRAY_BUFFER, m->id_uvs);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_uvs * 3, m->uvs, GL_STATIC_DRAW);

			App->scene_intro->meshes.push_back(m);
		}

		aiReleaseImport(scene);
	}
	else
		LOG(LOG_ERROR, "Error loading scene %s", path);
}

uint ModuleImporter::LoadTexture(const char* path)
{
	if (ilLoadImage(path)) 
	{
		ILuint width, height;
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		ILubyte* data = ilGetData();

		uint tex_id;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		return tex_id;
	}
	else
		return -1;
}

void ModuleImporter::AssignTextureToModel(Mesh* mesh, uint texture_id)
{
	if (mesh != nullptr)
	{
		mesh->id_textures = texture_id;
	}
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

	glDeleteBuffers(num_vertices, &id_vertices);
	glDeleteBuffers(num_indices, &id_indices);
	glDeleteBuffers(num_normals, &id_normals);
	glDeleteBuffers(num_uvs, &id_uvs);
}

void Mesh::DrawMeshLines(const float& size) const
{
	glColor3f(mesh_lines_color.x, mesh_lines_color.y, mesh_lines_color.z);

	glEnableClientState(GL_VERTEX_ARRAY);

	glLineWidth(size);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, num_indices * 3, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glColor3f(255.0f, 255.0f, 255.0f);
}

/* Mesh ------------------------------------ */
void Mesh::DrawMeshVertices(const float& size) const
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(255.0f, 0.0f, 0.0f);

	for (int i = 0; i < num_vertices * 3; i += 3)
	{
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glPointSize(1.0f);
}

void Mesh::DrawMeshVertexNormals(const float& width) const
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(0.0f, 255.0f, 255.0f);

	for (int i = 0; i < num_normals * 3; i += 3)
	{
		vec3 normal_vector = normalize({ normals[i], normals[i + 1], normals[i + 2] });

		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
		glVertex3f(vertices[i] + normal_vector.x, vertices[i + 1] + normal_vector.y, vertices[i + 2] + normal_vector.z);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glLineWidth(1.0f);
}

void Mesh::DrawMeshFaceNormals(const float& width) const
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(255.0f, 0.0f, 255.0f);

	for (int i = 0; i < num_indices; i += 3)
	{
		glVertex3f(center_face_point[i], center_face_point[i + 1], center_face_point[i + 2]);
		glVertex3f(center_face_point[i] + center_face_normal_point[i], center_face_point[i + 1] + center_face_normal_point[i + 1], center_face_point[i + 2] + center_face_normal_point[i + 2]);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glLineWidth(1.0f);
}

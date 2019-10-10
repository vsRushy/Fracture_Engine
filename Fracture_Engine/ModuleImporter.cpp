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

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

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

void ModuleImporter::LoadModel(const char* full_path)
{
	const aiScene* scene = aiImportFile(full_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		LOG(LOG_INFORMATION, "New scene with %d mesh(es)", scene->mNumMeshes);
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			LOG(LOG_INFORMATION, "Operating with mesh number %d", i);

			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[i];

			/* Copy vertices */
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG(LOG_INFORMATION, "New mesh with %d vertices", m.num_vertices);

			/* Copy faces */
			if (new_mesh->HasFaces())
			{// TOQUESTION: Is different n verts?
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; i++)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG(LOG_WARNING, "Geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}

				LOG(LOG_INFORMATION, "New mesh with %d indices", m.num_indices);
			}

			/* Copy normals */
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3];
				memcpy(m.normals, new_mesh->mNormals, sizeof(float) * m.num_normals * 3);
				LOG(LOG_INFORMATION, "New mesh with %d normals", m.num_normals);
			}

			/* Copy UVs */
			for (uint j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; j++)
			{
				if (new_mesh->HasTextureCoords(j))
				{
					m.num_uvs = new_mesh->mNumVertices;
					m.uvs = new float[m.num_uvs * 2];
					for (uint k = 0; k < m.num_uvs; k++)
					{
						memcpy(&m.uvs[k], &new_mesh->mTextureCoords[j][k].x, sizeof(float));
						memcpy(&m.uvs[++k], &new_mesh->mTextureCoords[j][k].y, sizeof(float));
					}
				}
				else
					LOG(LOG_INFORMATION, "There are no UVs at the current UVs set (%d)", j);
			}
			LOG(LOG_INFORMATION, "New mesh with %d UVs", m.num_uvs);
			
			/* Copy colors */
			for (uint j = 0; j < AI_MAX_NUMBER_OF_COLOR_SETS; j++)
			{
				if (new_mesh->HasVertexColors(j))
				{
					m.num_colors = new_mesh->mNumVertices;
					m.colors = new float[m.num_colors * 4];

					for (uint k = 0; k < m.num_colors; k++)
					{
						memcpy(&m.colors[k], &new_mesh->mColors[j][k].r, sizeof(float));
						memcpy(&m.colors[++k], &new_mesh->mColors[j][k].g, sizeof(float));
						memcpy(&m.colors[++k], &new_mesh->mColors[j][k].b, sizeof(float));
						memcpy(&m.colors[++k], &new_mesh->mColors[j][k].a, sizeof(float));
					}
				}
				else
					LOG(LOG_INFORMATION, "There are no colors at the current color set (%d)", j);
			}
			LOG(LOG_INFORMATION, "New mesh with %d colors", m.num_colors);
			
			/* VBO vertices */
			glGenBuffers(1, &(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m.num_vertices * 3, m.vertices, GL_STATIC_DRAW);
			
			/* IBO */
			glGenBuffers(1, &m.id_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);

			/* Normals */
			glGenBuffers(1, &m.id_normals);
			glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m.num_normals * 3, m.normals, GL_STATIC_DRAW);

			/* UVs */
			glGenBuffers(1, &m.id_uvs);
			glBindBuffer(GL_ARRAY_BUFFER, m.id_uvs);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m.num_uvs * 2, m.uvs, GL_STATIC_DRAW);

			/* Colors */
			glGenBuffers(1, &m.id_colors);
			glBindBuffer(GL_ARRAY_BUFFER, m.id_colors);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* m.num_colors * 4, m.colors, GL_STATIC_DRAW);

			App->scene_intro->meshes.push_back(m);
		}

		aiReleaseImport(scene);
	}
	else
		LOG(LOG_ERROR, "Error loading scene %s", full_path);
}

Mesh::~Mesh()
{
	delete[] vertices;
	delete[] indices;
	delete[] normals;
	delete[] uvs;
	delete[] colors;

	vertices = nullptr;
	indices = nullptr;
	normals = nullptr;
	uvs = nullptr;
	colors = nullptr;

	glDeleteBuffers(num_vertices, &id_vertices);
	glDeleteBuffers(num_indices, &id_indices);
	glDeleteBuffers(num_normals, &id_normals);
	glDeleteBuffers(num_uvs, &id_uvs);
	glDeleteBuffers(num_colors, &id_colors);
}

/* Mesh ------------------------------------ */
void Mesh::DrawMeshVertices(const float& size) const
{
	glPointSize(7.5f);

	glBegin(GL_POINTS);

	glColor3f(255.0f, 0.0f, 0.0f);

	for (int i = 0; i < num_vertices * 3; i += 3)
	{
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	glEnd();
	glPointSize(1.0f);
}

void Mesh::DrawMeshNormals(const float& width) const
{
	glLineWidth(5.0f);
	glBegin(GL_LINES);

	glColor3f(0.0f, 255.0f, 255.0f);

	for (int i = 0; i < num_normals * 3; i += 3)
	{
		vec3 normal_vector = normalize({ normals[i], normals[i + 1], normals[i + 2] });

		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
		glVertex3f(vertices[i] + normal_vector.x, vertices[i + 1] + normal_vector.y, vertices[i + 2] + normal_vector.z);
	}

	glEnd();
	glLineWidth(1.0f);
}
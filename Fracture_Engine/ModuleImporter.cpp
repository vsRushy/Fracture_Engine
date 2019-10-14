#include "GL/glew.h"

#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleSceneIntro.h"

#include "Mesh.h"

ModuleImporter::ModuleImporter(bool start_enabled) : Module(start_enabled)
{

}

ModuleImporter::~ModuleImporter()
{}

// -----------------------------------------------------------------
bool ModuleImporter::Init()
{
	bool ret = true;

	texture_root_path = "Assets/Textures/";

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
			
			/* Copy materials */
			if (scene->HasMaterials())
			{
				for (uint i = 0; i < scene->mNumMaterials; i++)
				{
					uint diffuse_texture_count = scene->mMaterials[new_mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE);

					for (int j = 0; j < diffuse_texture_count; j++)
					{
						aiString texture_path;
						scene->mMaterials[new_mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, j, &texture_path);
						m->id_textures = LoadTexture(texture_path.data);
					}
				}
			}

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
	std::string local_path(path);
	std::string full_path(texture_root_path + local_path);
	if (ilLoad(IL_PNG, full_path.data()))
	{
		iluFlipImage();
		ILuint texture_id = ilutGLBindTexImage();

		if (texture_id > 0)
		{
			App->scene_intro->textures.insert({ path, texture_id });
			glBindTexture(GL_TEXTURE_2D, 0);
			ilDeleteImage(texture_id);
		}

		return texture_id;
	}
	else
		return -1;
}

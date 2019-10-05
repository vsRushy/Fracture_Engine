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
	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[i];

			/* Copy vertices */
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG(LOG_INFORMATION, "New mesh with %d vertices", m.num_vertices);
		
			/* Copy faces */
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG(LOG_WARNING, "WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}
			}

			/* VBO */
			glGenBuffers(1, &(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m.num_vertices * 3, m.vertices, GL_STATIC_DRAW);
			
			/* IBO */
			glGenBuffers(1, &m.id_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices * 3, m.indices, GL_STATIC_DRAW);

			App->scene_intro->meshes.push_back(m);
		}
		aiReleaseImport(scene);
	}
	else
		LOG(LOG_ERROR, "Error loading scene %s", full_path);
}
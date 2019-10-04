#include "Application.h"
#include "ModuleImporter.h"
#include "Mesh.h"
//#include "Log"

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
		// copy vertices
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[i];
			m.num_vertex = new_mesh->mNumVertices;
			m.vertex = new float[m.num_vertex * 3];
			memcpy(m.vertex, new_mesh->mVertices, sizeof(float) * m.num_vertex * 3);
			//LOG(LOG_INFORMATION, "New mesh with %d vertices", m.num_vertices);
		}
		aiReleaseImport(scene);
	}
	else
		LOG(LOG_ERROR, "Error loading scene %s", full_path);
}
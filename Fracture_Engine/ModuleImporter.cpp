#include "GL/glew.h"

#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleSceneIntro.h"

#include "GameObject.h"

#include "Component_Transform.h"
#include "Component_Mesh.h"
#include "Component_Material.h"

#include "Mesh.h"
#include "Texture.h"

#include "MathGeoLib.h"

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
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	return ret;
}

// -----------------------------------------------------------------
bool ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

void ModuleImporter::LoadDroppedFile(const char* path)
{
	std::string ext = App->file_system->GetFileExtensionFromPath(path);

	if (ext == ".fbx" || ext == ".FBX")
	{
		LoadModel(path);
	}
	else if (ext == ".png" || ext == ".PNG"
		|| ext == ".dds" || ext == ".DDS")
	{
		Texture* tmp_tex = LoadTexture(path);
		if (tmp_tex != nullptr)
		{
			if (App->scene_intro->selected_game_object != nullptr &&
				App->scene_intro->selected_game_object->GetComponentMaterial() != nullptr)
			{
				App->scene_intro->selected_game_object->GetComponentMaterial()->texture = tmp_tex;
			}
		}
	}
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
		GameObject* g_o = App->scene_intro->CreateEmptyGameObject(
			App->file_system->GetFileNameFromPath(path).data(),
			App->scene_intro->root_game_object
		);
		
		LOG(LOG_INFORMATION, "New scene with %d mesh(es)", scene->mNumMeshes);
		
		LoadSceneNode(scene, scene->mRootNode, g_o);
		
		aiVector3D position;
		aiQuaternion rotation;
		aiVector3D scale;

		scene->mRootNode->mTransformation.Decompose(scale, rotation, position);
		
		g_o->component_transform->Set(float3(position.x, position.y, position.z), 
			Quat(rotation.x, rotation.y, rotation.z, rotation.w), 
			float3(scale.x, scale.y, scale.z));

		g_o->component_transform->CalculateLocalMatrix();
		g_o->component_transform->CalculateGlobalMatrix();
		
		aiReleaseImport(scene);
	}
	else
		LOG(LOG_ERROR, "Error loading scene %s", path);
}


void ModuleImporter::LoadSceneNode(const aiScene* scene, aiNode* node, GameObject* parent)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		GameObject* go = App->scene_intro->CreateEmptyGameObject(node->mName.C_Str(), parent);
	
		aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
		go->CreateComponentMesh(Mesh::LoadMesh(ai_mesh));
		
		Mesh* tmp_m = go->GetComponentMesh()->mesh;
		std::string m_out;
		SaveMesh(tmp_m, node->mName.C_Str(), m_out);
		std::string own_mesh_file_n_e(node->mName.C_Str());
		own_mesh_file_n_e.append(".").append(FE_MESH);
		App->scene_intro->own_meshes.push_back(own_mesh_file_n_e);

		aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
		aiString file_path_tex;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &file_path_tex);

		go->CreateComponentMaterial();
		ComponentMaterial* tmp_cm = go->GetComponentMaterial();
		std::string full_tex_path = TEXTURE_ROOT_PATH;
		full_tex_path.append(file_path_tex.C_Str());
		tmp_cm->SetTexture(LoadTexture(full_tex_path.c_str()));
		tmp_cm->SetInitialTexture(LoadTexture(full_tex_path.c_str()));

		aiVector3D position;
		aiQuaternion rotation;
		aiVector3D scale;

		node->mTransformation.Decompose(scale, rotation, position);

		go->component_transform->Set(float3(position.x, position.y, position.z),
			Quat(rotation.x, rotation.y, rotation.z, rotation.w),
			float3(scale.x, scale.y, scale.z));

		/*go->component_transform->CalculateLocalMatrix();
		go->component_transform->CalculateGlobalMatrix();*/
	}

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		LoadSceneNode(scene, node->mChildren[i], parent);
	}
}

Texture* ModuleImporter::LoadTexture(const char* path)
{
	Texture* texture = nullptr;

	if (App->scene_intro->TextureAlreadyExists(path))
	{
		texture = App->scene_intro->GetTextureByName(path);
		LOG(LOG_INFORMATION, "Texture with path %s already exists!", path);
	}
	else
	{
		/* We cannot use ilSave(..) to save an already .DDS texture. Therefore, we copy it to our Library folder */
		std::string tex_ext = App->file_system->GetFileExtensionFromPath(path);
		if (tex_ext.compare(".dds") == 0 || tex_ext.compare(".DDS") == 0)
		{
			App->file_system->Copy(path, std::string(LIBRARY_TEXTURE_PATH + App->file_system->GetFileNameFromPath(path) + tex_ext).c_str());
		}

		ILuint devil_id = 0;
		ilGenImages(1, &devil_id);
		ilBindImage(devil_id);

		LOG(LOG_INFORMATION, "Loading texture with path %s", path);
		if ((bool)ilLoadImage(path))
		{
			ILinfo img_info;
			iluGetImageInfo(&img_info);


			/* Save own texture (as .DDS) */
			ILuint size;
			ILubyte* data;
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
			size = ilSaveL(IL_DDS, NULL, 0);
			if (size > 0)
			{
				data = new ILubyte[size];
				if (ilSaveL(IL_DDS, data, size) > 0)
				{
					std::string tex_o;
					std::string text_name = App->file_system->GetFileNameFromPath(path);
					App->file_system->SaveUnique(tex_o, data, size, LIBRARY_TEXTURE_PATH, text_name.c_str(), "dds");
				}

				if (data != nullptr)
				{
					delete[] data;
					data = nullptr;
				}
			}


			iluFlipImage();

			texture = new Texture();

			if (ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE))
			{
				texture->data = (unsigned char*)ilGetData();
				texture->width = ilGetInteger(IL_IMAGE_WIDTH);
				texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
				texture->name = App->file_system->GetFileNameFromPath(path);
				texture->extension = App->file_system->GetFileExtensionFromPath(path);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glGenTextures(1, &texture->id);
				glBindTexture(GL_TEXTURE_2D, texture->id);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), texture->width, texture->height,
					0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, texture->data);
			}
			else
				LOG(LOG_ERROR, "Image could not be converted. Error code: %s", iluErrorString(ilGetError()));

			App->scene_intro->textures.insert({ texture->name + texture->extension, texture });
				
		}
		else
		{
			LOG(LOG_ERROR, "Error loading the texture %s. Error code: %s", path, iluErrorString(ilGetError()));
		}

		ilDeleteImages(1, &devil_id);
		

		App->scene_intro->own_textures.push_back(std::string(App->file_system->GetFileNameFromPath(path) + ".dds"));
	}

	return texture;
}

bool ModuleImporter::SaveMesh(Mesh* mesh, const char* file_name, std::string& file_output)
{
	/* amount of indices / vertices / colors / normals / texture_coords / AABB */
	uint ranges[4] = { mesh->num_indices, mesh->num_vertices, mesh->num_normals, mesh->num_uvs };
	uint size = sizeof(ranges) + sizeof(uint) * mesh->num_indices + sizeof(float) * mesh->num_vertices * 3
		+ sizeof(float) * mesh->num_normals * 3 + sizeof(float) * mesh->num_uvs * 2;
	
	/* Allocate */
	char* data = new char[size];
	char* cursor = data;
	
	/* Store ranges */
	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);
	
	/* Store indices */
	cursor += bytes;
	bytes = sizeof(uint) * mesh->num_indices;
	memcpy(cursor, mesh->indices, bytes);

	/* Store vertices */
	cursor += bytes;
	bytes = sizeof(float) * mesh->num_vertices * 3;
	memcpy(cursor, mesh->vertices, bytes);

	/* Store normals */
	cursor += bytes;
	bytes = sizeof(float) * mesh->num_normals * 3;
	memcpy(cursor, mesh->normals, bytes);

	/* Store uvs */
	cursor += bytes;
	bytes = sizeof(float) * mesh->num_uvs * 2;
	memcpy(cursor, mesh->uvs, bytes);

	App->file_system->SaveUnique(file_output, data, size, LIBRARY_MESH_PATH, file_name, FE_MESH);

	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}

	return true;
}

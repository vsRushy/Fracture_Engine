#include "GL/glew.h"

#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleImporter.h"
#include "P_Cube.h"
#include "P_Sphere.h"
#include "P_Plane.h"

#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "Component.h"
#include "Component_Mesh.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{

}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG(LOG_INFORMATION, "Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	root_game_object = CreateEmptyGameObject("Root", nullptr);

	selected_game_object = root_game_object;

	GameObject* child_test_1 = CreateEmptyGameObject("Child 1", root_game_object);
	GameObject* child_test_2 = CreateEmptyGameObject("Child 2", root_game_object);
	GameObject* child_test_3 = CreateEmptyGameObject("Child 3", child_test_2);

	checkered_texture = App->importer->LoadTextureCheckered();

	//App->importer->LoadModel("Assets/Models/BakerHouse.FBX");
	App->importer->LoadTexture("Assets/Textures/Checkers.dds");
	App->importer->LoadTexture("Assets/Textures/Lenna.png");

	GameObject* cube = CreatePrimitiveGameObject("Cube", PRIMITIVE_TYPE::CUBE, root_game_object);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG(LOG_INFORMATION, "Unloading Intro scene");

	/* Delete all game objects */
	for (std::list<GameObject*>::reverse_iterator item = game_objects.rbegin(); item != game_objects.rend(); item++)
	{
		delete* item;
		*item = nullptr;
	}
	game_objects.clear();

	/* Delete all primitives */
	for (std::list<Primitive*>::reverse_iterator item = primitives.rbegin(); item != primitives.rend(); item++)
	{
		delete *item;
		*item = nullptr;
	}
	primitives.clear();

	/* Delete all textures */
	for (std::map<std::string, Texture*>::reverse_iterator item = textures.rbegin(); item != textures.rend(); item++)
	{
		if ((*item).second != nullptr)
		{
			delete (*item).second;
			(*item).second = nullptr;
		}
	}
	textures.clear();

	return true;
}
 
void ModuleSceneIntro::DrawGrid(int subdivisions)
{
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(255.0f, 255.0f, 255.0f);
	for (int i = -subdivisions / 2; i < subdivisions / 2; i++)
	{
		glVertex3f(i, 0, -subdivisions / 2);
		glVertex3f(i, 0, subdivisions / 2);
		glVertex3f(-subdivisions / 2, 0, i);
		glVertex3f(subdivisions / 2, 0, i);
	}
	glEnd();
}

GameObject* ModuleSceneIntro::CreatePrimitiveGameObject(std::string name, PRIMITIVE_TYPE type, GameObject* parent)
{
	ChangeNameIfGameObjectNameAlreadyExists(name);

	GameObject* primitive = new GameObject(name, parent);
	primitive->CreateComponentMesh(nullptr);
	primitive->CreateComponentMaterial();

	primitive->GetComponentMesh()->mesh = CreatePrimitiveMesh(PRIMITIVE_TYPE::CUBE);

	game_objects.push_back(primitive);

	LOG(LOG_INFORMATION, "Created primitive game object with name %s", name.c_str());

	return primitive;
}

Mesh* ModuleSceneIntro::CreatePrimitiveMesh(PRIMITIVE_TYPE type)
{
	Mesh* mesh = new Mesh();
	par_shapes_mesh* primitive_mesh = nullptr;

	switch (type)
	{
	case PRIMITIVE_TYPE::CUBE:
		primitive_mesh = par_shapes_create_cube();
		break;
	case PRIMITIVE_TYPE::SPHERE:
		primitive_mesh = par_shapes_create_subdivided_sphere(10);
		break;
	case PRIMITIVE_TYPE::PLANE:
		primitive_mesh = par_shapes_create_plane(10, 10);
		break;
	default:
		break;
	}

	mesh->num_vertices = primitive_mesh->npoints;
	mesh->vertices = new float[mesh->num_vertices * 3];
	memcpy(mesh->vertices, primitive_mesh->points, sizeof(float) * mesh->num_vertices * 3);

	mesh->num_indices = primitive_mesh->ntriangles * 3;
	mesh->indices = new uint[primitive_mesh->ntriangles * 3];
	memcpy(mesh->indices, primitive_mesh->triangles, sizeof(uint) * mesh->num_indices);

	if (primitive_mesh->normals != nullptr)
	{
		mesh->num_normals = primitive_mesh->npoints;
		mesh->normals = new float[mesh->num_normals * 3];
		memcpy(mesh->normals, primitive_mesh->normals, sizeof(float) * mesh->num_normals * 3);
	}

	if (primitive_mesh->tcoords != nullptr)
	{
		mesh->num_uvs = primitive_mesh->npoints;
		mesh->uvs = new float[mesh->num_uvs * 2];
		memcpy(mesh->uvs, primitive_mesh->tcoords, sizeof(float) * mesh->num_uvs * 2);
	}
	
	mesh->CreateBuffers();

	par_shapes_free_mesh(primitive_mesh);

	return mesh;
}

GameObject* ModuleSceneIntro::CreateEmptyGameObject(std::string name, GameObject* parent)
{
	ChangeNameIfGameObjectNameAlreadyExists(name);

	GameObject* go = new GameObject(name, parent);
	game_objects.push_back(go);

	LOG(LOG_INFORMATION, "Created empty game object with name %s", name.c_str());

	return go;
}

Texture* ModuleSceneIntro::GetTextureByName(const std::string& name)
{
	Texture* texture = nullptr;
	for (std::map<std::string, Texture*>::const_iterator item = textures.begin(); item != textures.end(); item++)
	{
		if ((*item).first == name)
		{
			texture = (*item).second;
		}
	}

	return texture;
}

bool ModuleSceneIntro::TextureAlreadyExists(const std::string& name)
{
	bool ret = false;
	for (std::map<std::string, Texture*>::const_iterator item = textures.begin(); item != textures.end(); item++)
	{
		if ((*item).first == name)
		{
			ret = true;
		}
	}

	return ret;
}

void ModuleSceneIntro::ChangeNameIfGameObjectNameAlreadyExists(const std::string& name)
{
	for (std::list<GameObject*>::const_iterator item = game_objects.begin(); item != game_objects.end(); item++)
	{
		static uint counter = 0;
		if ((*item)->name == name)
		{
			counter++;
			(*item)->name = name + " (" + std::to_string(counter) + ")";
		}
	}
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
	/* Pre Update game objects ----------------------- */
	for (std::list<GameObject*>::iterator item = game_objects.begin(); item != game_objects.end(); item++)
	{
		(*item)->PreUpdate(dt);
	}

	return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/* Draw grid ----------------------------- */
	DrawGrid(100);

	/* Draw primitives ----------------------- */
	for (std::list<Primitive*>::iterator item = primitives.begin(); item != primitives.end(); item++)
	{
		App->renderer3D->DrawPrimitive(*item);
	}

	/* Update game objects ----------------------- */
	for (std::list<GameObject*>::iterator item = game_objects.begin(); item != game_objects.end(); item++)
	{
		(*item)->Update(dt);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	/* Post Update game objects ----------------------- */
	for (std::list<GameObject*>::iterator item = game_objects.begin(); item != game_objects.end(); item++)
	{
		(*item)->PostUpdate(dt);
	}

	return UPDATE_CONTINUE;
}

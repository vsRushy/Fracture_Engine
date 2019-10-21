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

	//CreatePrimitive({0, 0, 0}, PRIMITIVE_TYPE::CUBE);

	//App->importer->LoadModel("Assets/Models/BakerHouse.FBX");

	//GameObject* g1 = CreateEmptyGameObject("test", nullptr);
	//GameObject* g2 = CreateModelGameObject("test2", "Assets/Models/BakerHouse.FBX", nullptr);

	root_game_object = CreateEmptyGameObject("Root", nullptr);

	selected_game_object = root_game_object;

	GameObject* child_test_1 = CreateEmptyGameObject("Child 1", root_game_object);
	GameObject* child_test_2 = CreateEmptyGameObject("Child 2", root_game_object);
	GameObject* child_test_3 = CreateEmptyGameObject("Child 3", child_test_2);

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

	/* Delete all meshes */
	for (std::map<const char*, std::list<Mesh*>>::reverse_iterator item = meshes.rbegin(); item != meshes.rend(); item++)
	{
		for (std::list<Mesh*>::reverse_iterator item_list = (*item).second.rbegin(); item_list != (*item).second.rend(); item_list++)
		{
			delete *item_list;
			*item_list = nullptr;
		}
	}
	meshes.clear();

	/* Delete all textures */
	for (std::map<const char*, Texture*>::reverse_iterator item = textures.rbegin(); item != textures.rend(); item++)
	{
		delete (*item).second;
		(*item).second = nullptr;
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

void ModuleSceneIntro::CreatePrimitive(const vec3& pos, PRIMITIVE_TYPE type)
{
	Primitive* primitive;
	switch (type)
	{
	case PRIMITIVE_TYPE::CUBE:
		primitive = new P_Cube(pos);
		primitives.push_back(primitive);
		break;
	case PRIMITIVE_TYPE::SPHERE:
		primitive = new P_Sphere(pos);
		primitives.push_back(primitive);
		break;
	case PRIMITIVE_TYPE::PLANE:
		primitive = new P_Plane(pos);
		primitives.push_back(primitive);
		break;
	default:
		break;
	}
}

GameObject* ModuleSceneIntro::CreateEmptyGameObject(std::string name, GameObject* parent)
{
	GameObject* go = new GameObject(name, parent);
	game_objects.push_back(go);

	return go;
}

GameObject* ModuleSceneIntro::CreateModelGameObject(std::string name, const char* meshes_name, GameObject* parent)
{
	GameObject* go = new GameObject(name, parent);

	go->CreateComponentMesh(meshes_name);

	game_objects.push_back(go);

	return go;
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

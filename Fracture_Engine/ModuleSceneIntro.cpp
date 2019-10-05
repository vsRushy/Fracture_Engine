#include "GL/glew.h"

#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "P_Cube.h"
#include "P_Sphere.h"
#include "P_Plane.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG(LOG_INFORMATION, "Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//CreatePrimitive({0.0f, 0.0f, 0.0f}, PRIMITIVE_TYPE::CUBE);
	//CreatePrimitive({0.0f, 0.0f, 0.0f}, PRIMITIVE_TYPE::SPHERE);
	//CreatePrimitive({0.0f, 0.0f, 0.0f}, PRIMITIVE_TYPE::PLANE);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG(LOG_INFORMATION, "Unloading Intro scene");

	/* Delete all primitives */
	for (std::list<Primitive*>::reverse_iterator item = primitives.rbegin(); item != primitives.rend(); item++)
	{
		delete *item;
		*item = nullptr;
	}
	primitives.clear();

	return true;
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

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/* Draw primitives ----------------------- */
	for (std::list<Primitive*>::iterator item = primitives.begin(); item != primitives.end(); item++)
	{
		App->renderer3D->DrawPrimitive(*item);
	}

	return UPDATE_CONTINUE;
}

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "MathGeoLib.h"
#include "MathBuildConfig.h"
#include "MathGeoLibFwd.h"
#include "MathGeoLib/include/Geometry/Sphere.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Sphere s({ 0.0f, 0.0f, 0.0f }, 4.0f);
	Sphere f({ 0.0f, 0.0f, 0.0f }, 7.0f);

	if (f.Intersects(s))
	{
		LOG("INTERSECTION");
	}

	return UPDATE_CONTINUE;
}

#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	user_interface = new ModuleUserInterface(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	
	// Scenes
	AddModule(scene_intro);

	// User Interface
	AddModule(user_interface);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (std::list<Module*>::const_reverse_iterator item = list_modules.rbegin(); item != list_modules.rend(); item++)
	{
		delete *item;
	}
}

bool Application::Init()
{
	bool ret = true;

	/* Settings */
	SetAppName("Fracture Engine");
	SetAppOrganization("CITM-UPC");

	// Call Init() in all modules
	for (std::list<Module*>::const_iterator item = list_modules.begin(); item != list_modules.end() && ret; item++)
	{
		ret = (*item)->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	
	for (std::list<Module*>::const_iterator item = list_modules.begin(); item != list_modules.end() && ret; item++)
	{
		ret = (*item)->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{

}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	PrepareUpdate();
	
	std::list<Module*>::const_iterator item;
	
	for (item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->PreUpdate(dt);
	}

	for (item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->Update(dt);
	}

	for (item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->PostUpdate(dt);
	}
	
	FinishUpdate();

	// -----------------------------------------------

	if (close_app)
		return UPDATE_STOP;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (std::list<Module*>::const_reverse_iterator item = list_modules.rbegin(); item != list_modules.rend() && ret; item++)
	{
		ret = (*item)->CleanUp();
	}

	return ret;
}

void Application::CloseApplication()
{
	close_app = true;
}

void Application::SetAppName(const char* name)
{
	app_name = name;
}

void Application::SetAppOrganization(const char* organization)
{
	app_organization = organization;
}

void Application::SetMaxFPS(const int& m_fps)
{
	max_fps = m_fps;
}

void Application::SetVSync(const bool& value)
{
	vsync = value;
}

const char* Application::GetAppName() const
{
	return app_name;
}

const char* Application::GetAppOrganization() const
{
	return app_organization;
}

int Application::GetMaxFPS() const
{
	return max_fps;
}

bool Application::GetVSync() const
{
	return vsync;
}

void Application::RequestBrowser(const char* link) const
{
	ShellExecute(0, "open", link, 0, 0, SW_SHOWNORMAL);
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}
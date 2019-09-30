#include "Application.h"

Application::Application()
{
	window = new ModuleWindow();
	input = new ModuleInput();
	scene_intro = new ModuleSceneIntro();
	user_interface = new ModuleUserInterface();
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();

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

	startup_time.Start();

	/* Set fps and ms vectors capacity */
	fps_vec.resize(120);
	ms_vec.resize(120);

	/* Settings */
	SetAppName("Fracture Engine");
	SetAppOrganization("CITM-UPC");

	SetMaxFPS(60);

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
	frame_count++;
	last_sec_frame_count++;

	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	avg_fps = (float)frame_count / startup_time.ReadSec();
	seconds_since_startup = startup_time.ReadSec();
	last_frame_ms = ms_timer.Read();
	frames_on_last_update = prev_last_sec_frame_count;
	fps = frames_on_last_update;
	milliseconds = 1.0f / fps * 1000.0f;

	if (capped_ms > 0 && last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}

	AddFPSToVec(fps);
	AddMSToVec(milliseconds);
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

void Application::Log(const char* text_log)
{
	user_interface->LogToConsole(text_log);
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
	CapMS();
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

float Application::GetFPS() const
{
	return fps;
}

float Application::GetMS() const
{
	return milliseconds;
}

void Application::AddFPSToVec(float fps)
{
	static int counter = 0;

	if (counter == fps_vec.capacity())
	{
		for (uint i = 0; i < fps_vec.capacity() - 1; i++)
		{
			fps_vec[i] = fps_vec[i + 1];
		}
	}
	else
		counter++;

	fps_vec[counter - 1] = fps;
}

void Application::AddMSToVec(float ms)
{
	static int counter = 0;

	if (counter == ms_vec.capacity())
	{
		for (uint i = 0; i < ms_vec.capacity() - 1; i++)
		{
			ms_vec[i] = ms_vec[i + 1];
		}
	}
	else
		counter++;

	ms_vec[counter - 1] = ms;
}

void Application::RequestBrowser(const char* link) const
{
	ShellExecute(0, "open", link, 0, 0, SW_SHOWNORMAL);
}

void Application::CapMS()
{
	if (GetMaxFPS() > 0)
	{
		capped_ms = 1000 / GetMaxFPS();
	}
	else
		capped_ms = 0;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}
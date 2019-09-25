#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <list>

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleUserInterface.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleUserInterface* user_interface;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:
	std::list<Module*> list_modules;
	
	const char* app_name;
	const char* app_organization;

	float	dt;
	Timer	ms_timer;
	int max_fps = 0;

	bool close_app = false;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	void CloseApplication();
	void RequestBrowser(const char* link) const;

	void SetAppName(const char* name);
	void SetAppOrganization(const char* organization);
	void SetMaxFPS(const int& m_fps);

	const char* GetAppName() const;
	const char* GetAppOrganization() const;
	int GetMaxFPS() const;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

#endif /* __APPLICATION_H__ */
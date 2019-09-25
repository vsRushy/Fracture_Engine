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

	Timer	ms_timer;
	float	dt;

	bool close_app = false;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	void CloseApplication();
	void SetAppName(const char* name);
	void SetAppOrganization(const char* organization);
	const char* GetAppName() const;
	const char* GetAppOrganization() const;
	void RequestBrowser(const char* link) const;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

#endif /* __APPLICATION_H__ */
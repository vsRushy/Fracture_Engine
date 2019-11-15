#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <list>
#include <vector>

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleUserInterface.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleImporter.h"
#include "ModuleFileSystem.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleUserInterface* user_interface;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImporter* importer;
	ModuleFileSystem* file_system;

private:
	std::list<Module*> list_modules;
	
	const char*			app_name;
	const char*			app_organization;

	float				dt;
	unsigned __int64	frame_count = 0;
	float				fps = 0.0f;
	float				milliseconds = 0.0f;
	float				avg_fps;
	float				seconds_since_startup = 0.0f;
	Timer				ms_timer;
	uint				last_frame_ms;
	Timer				startup_time;
	Timer				last_sec_frame_time;
	uint				last_sec_frame_count = 0;
	uint				prev_last_sec_frame_count = 0;
	uint				frames_on_last_update = 0;
	int					max_fps = 0;
	int					capped_ms = -1;

	bool				close_app = false;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	void Log(LOG_TYPE type, const char* text_log);
	void CloseApplication();
	void RequestBrowser(const char* link) const;
	void CapMS();

	// -----------------------------------

	void SetAppName(const char* name);
	void SetAppOrganization(const char* organization);
	void SetMaxFPS(const int& m_fps);

	const char* GetAppName() const;
	const char* GetAppOrganization() const;
	int GetMaxFPS() const;
	float GetFPS() const;
	float GetMS() const;

	void AddFPSToVec(float fps);
	void AddMSToVec(float ms);

public:
	std::vector<float> fps_vec;
	std::vector<float> ms_vec;
	
private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	JSON_Object* LoadJSONFile(const char* path) const;
	/* This function loads Application settings and also iterates every module in order to load more settings
	   specifically from each module */
	void LoadAllConfiguration();
};

extern Application* App;

#endif /* __APPLICATION_H__ */
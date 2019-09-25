#ifndef __MODULE_USER_INTERFACE_H__
#define __MODULE_USER_INTERFACE_H__

#include "Module.h"
#include "Globals.h"

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface(Application* app, bool start_enabled = true);
	~ModuleUserInterface();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:
	void ShowMainMenuBarWindow();
	void ShowAboutWindow();
	void ShowLicenseWindow();

private:
	static bool show_demo_window;
	static bool show_main_menu_bar_window;
	static bool show_about_window;
	static bool show_license_window;
};

#endif /* __MODULE_USER_INTERFACE_H__ */
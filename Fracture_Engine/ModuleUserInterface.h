#ifndef __MODULE_USER_INTERFACE_H__
#define __MODULE_USER_INTERFACE_H__

#include <list>

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"

class Panel;
class PanelScene;

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface(bool start_enabled = true);
	~ModuleUserInterface();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	void LogToConsole(LOG_TYPE type, const char* text_log);
	bool scroll_down_console = false;

	void AddPanel(Panel* panel);

private:
	void ShowMainMenuBarWindow();
	void ShowAboutWindow();
	void ShowConfigurationWindow();
	void ShowConsoleWindow();

private:
	static bool show_demo_window;
	static bool show_main_menu_bar_window;
	static bool show_about_window;
	static bool show_configuration_window;
	static bool show_console_window;

private:
	std::list<std::pair<LOG_TYPE, const char*>> console_logs;

public:
	std::vector<Panel*> panels;

	Panel* panel_scene = nullptr;
};

#endif /* __MODULE_USER_INTERFACE_H__ */
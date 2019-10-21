#ifndef __MODULE_USER_INTERFACE_H__
#define __MODULE_USER_INTERFACE_H__

#include <list>

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"

class Panel;

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
	void AddPanel(Panel* panel);

	void LogToConsole(LOG_TYPE type, const char* text_log);

public:
	std::vector<Panel*> panels;

	Panel* panel_scene = nullptr;
	Panel* panel_main_menu_bar = nullptr;
	Panel* panel_console = nullptr;
	Panel* panel_about = nullptr;
	Panel* panel_configuration = nullptr;
	Panel* panel_hierarchy = nullptr;
	Panel* panel_inspector = nullptr;
};

#endif /* __MODULE_USER_INTERFACE_H__ */
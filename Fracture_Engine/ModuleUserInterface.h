#ifndef __MODULE_USER_INTERFACE_H__
#define __MODULE_USER_INTERFACE_H__

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"

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

public:
	void LogToConsole(const char* text_log);

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
	ImGuiTextBuffer text_buffer;
};

#endif /* __MODULE_USER_INTERFACE_H__ */
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "GL/glew.h"
#include "SDL/include/SDL_cpuinfo.h"

#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleInput.h"

#include "Panel.h"
#include "PanelScene.h"
#include "PanelMainMenuBar.h"
#include "PanelConsole.h"
#include "PanelAbout.h"
#include "PanelConfiguration.h"

ModuleUserInterface::ModuleUserInterface(bool start_enabled) :  Module(start_enabled)
{
	panel_scene = new PanelScene("Scene");
	panel_main_menu_bar = new PanelMainMenuBar("MainMenuBar");
	panel_console = new PanelConsole("Console", false);
	panel_about = new PanelAbout("About", false);
	panel_configuration = new PanelConfiguration("Configuration");

	AddPanel(panel_scene);
	AddPanel(panel_main_menu_bar);
	AddPanel(panel_console);
	AddPanel(panel_about);
	AddPanel(panel_configuration);
}

ModuleUserInterface::~ModuleUserInterface()
{

}

bool ModuleUserInterface::Start()
{
	bool ret = true;

	/* Load ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/Montserrat-Regular.ttf", 17.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	style.FrameRounding = 4.0f;
	style.GrabRounding = 4.0f;
	style.GrabMinSize = 16.0f;
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	/* Start panels */
	for (std::vector<Panel*>::const_iterator item = panels.begin(); item != panels.end(); item++)
	{
		if ((*item)->IsActive())
			(*item)->Start();
	}

	return ret;
}

update_status ModuleUserInterface::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleUserInterface::Update(float dt)
{
	ImGui::ShowDemoWindow();

	/* Update panels */
	for (std::vector<Panel*>::const_iterator item = panels.begin(); item != panels.end(); item++)
	{
		if((*item)->IsActive())
			(*item)->Update();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleUserInterface::PostUpdate(float dt)
{
	/* Render ImGui */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

bool ModuleUserInterface::CleanUp()
{
	/* CleanUp panels */
	for (std::vector<Panel*>::reverse_iterator item = panels.rbegin(); item != panels.rend(); item++)
	{
		(*item)->CleanUp();
		
		*item = nullptr;
	}
	panels.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleUserInterface::LogToConsole(LOG_TYPE type, const char* text_log)
{
	if(panel_console != nullptr)
		panel_console->Log(type, text_log);
}

void ModuleUserInterface::AddPanel(Panel* panel)
{
	panels.push_back(panel);
}


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
#include "PanelHierarchy.h"
#include "PanelInspector.h"
#include "PanelAssets.h"
#include "PanelLibrary.h"

ModuleUserInterface::ModuleUserInterface(bool start_enabled) :  Module(start_enabled)
{
	panel_scene = new PanelScene("Scene");
	panel_main_menu_bar = new PanelMainMenuBar("MainMenuBar");
	panel_console = new PanelConsole("Console");
	panel_configuration = new PanelConfiguration("Configuration");
	panel_hierarchy = new PanelHierarchy("Hierarchy");
	panel_inspector = new PanelInspector("Inspector");
	panel_assets = new PanelAssets("Assets");
	panel_library = new PanelLibrary("Library");
	panel_about = new PanelAbout("About", false);

	AddPanel(panel_scene);
	AddPanel(panel_main_menu_bar);
	AddPanel(panel_console);
	AddPanel(panel_about);
	AddPanel(panel_configuration);
	AddPanel(panel_hierarchy);
	AddPanel(panel_inspector);
	AddPanel(panel_assets);
	AddPanel(panel_library);
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
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
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

	/* Dockspace created before drawing the panels */
	ImGuiIO& io = ImGui::GetIO();
	CreateDockSpace(io);

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
	ImGuiIO& io = ImGui::GetIO();

	/* Render ImGui */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

void ModuleUserInterface::CreateDockSpace(const ImGuiIO& io)
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	
	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &dockspace_active, window_flags);
	ImGui::PopStyleVar();

	ImGui::PopStyleVar(2);

	// DockSpace
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		LOG(LOG_INFORMATION, "Docking space is disabled");
	}

	ImGui::End();
}

void ModuleUserInterface::AddPanel(Panel* panel)
{
	panels.push_back(panel);
}


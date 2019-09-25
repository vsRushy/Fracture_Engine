#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleInput.h"
#include "SDL\include\SDL_cpuinfo.h"

bool ModuleUserInterface::show_demo_window = true;
bool ModuleUserInterface::show_main_menu_bar_window = true;
bool ModuleUserInterface::show_about_window = false;
bool ModuleUserInterface::show_license_window = false;

ModuleUserInterface::ModuleUserInterface(Application* app, bool start_enabled) :  Module(app, start_enabled)
{
	
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
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/Montserrat-Regular.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	style.FrameRounding = 5.0f;
	style.GrabRounding = 5.0f;
	style.GrabMinSize = 17.0f;
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();
	SDL_version compiled;

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
	/* Show Windows --------------------------- */
	ImGui::Begin("Configuration");
	ImGui::Text("Something");
	if (ImGui::CollapsingHeader("Application"))
	{
		static char app_name[CUSTOM_BUFFER_SIZE_MEDIUM];
		strcpy_s(app_name, CUSTOM_BUFFER_SIZE_MEDIUM, App->GetAppName());
		if (ImGui::InputText("Application name", app_name, CUSTOM_BUFFER_SIZE_MEDIUM,
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
		{
			App->SetAppName((const char*)app_name);
		}

		static char app_organization[CUSTOM_BUFFER_SIZE_MEDIUM];
		strcpy_s(app_organization, CUSTOM_BUFFER_SIZE_MEDIUM, App->GetAppOrganization());
		if (ImGui::InputText("Application organization", app_organization, CUSTOM_BUFFER_SIZE_MEDIUM,
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
		{
			App->SetAppOrganization((const char*)app_organization);
		}

		static int max_fps = App->GetMaxFPS();
		if (ImGui::SliderInt("Max FPS", &max_fps, 0, 144))
		{
			App->SetMaxFPS(max_fps);
		}
	}
	if (ImGui::CollapsingHeader("Window"))
	{
		ImGui::Text("Parameters");
	}
	if (ImGui::CollapsingHeader("Hardware"))
	{
		SDL_version compiled;
		SDL_VERSION(&compiled);
		ImGui::Text("SDL version: %d. %d. %d", compiled.major, compiled.minor, compiled.patch);
		ImGui::Text("CPUs: %i (Cache: %ikb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
		ImGui::Text("System RAM: %i Mb", SDL_GetSystemRAM());
	}
	ImGui::End();

	/* Demo Window */
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	/* Main Menu Bar */
	if (show_main_menu_bar_window)
		ShowMainMenuBarWindow();

	/* About Window */
	if (show_about_window)
		ShowAboutWindow();

	/* License Window */
	if (show_license_window)
		ShowLicenseWindow();

	return UPDATE_CONTINUE;
}

update_status ModuleUserInterface::PostUpdate(float dt)
{
	/* Render ImGui */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleUserInterface::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleUserInterface::ShowMainMenuBarWindow()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close"))
			{
				App->CloseApplication();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				show_about_window = true;
			}
			if (ImGui::MenuItem("License"))
			{
				show_license_window = true;
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Webpage"))
			{
				App->RequestBrowser("https://vsrushy.github.io/Fracture_Engine/");
			}
			if (ImGui::MenuItem("GitHub"))
			{
				App->RequestBrowser("https://github.com/vsRushy/Fracture_Engine/");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ModuleUserInterface::ShowAboutWindow()
{
	ImGui::SetNextWindowPosCenter();
	ImGui::Begin("About", &show_about_window, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Fracture Engine is a video game engine used for educational purposes.\n"
		"This project is part of the Video Game Engines subject. CITM - UPC.\n"
		"Credits: Gerard Marcos Freixas and Marti Torras Isanta.");
	ImGui::End();
}

void ModuleUserInterface::ShowLicenseWindow()
{
	ImGui::SetNextWindowPosCenter();
	ImGui::Begin("License", &show_license_window, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("MIT License\n\n"

		"Copyright(c) 2019 Fracture Engine Team\n\n"

		"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
		"of this softwareand associated documentation files(the \"Software\"), to deal\n"
		"in the Software without restriction, including without limitation the rights\n"
		"to use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n"
		"copies of the Software, and to permit persons to whom the Software is\n"
		"furnished to do so, subject to the following conditions :\n\n"

		"The above copyright noticeand this permission notice shall be included in all\n"
		"copies or substantial portions of the Software.\n\n"

		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\n"
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
		"SOFTWARE.");
	ImGui::End();
}

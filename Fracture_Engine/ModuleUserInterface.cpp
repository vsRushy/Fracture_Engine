#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "GL/glew.h"
#include "SDL/include/SDL_cpuinfo.h"

#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleInput.h"

bool ModuleUserInterface::show_demo_window = false;
bool ModuleUserInterface::show_main_menu_bar_window = true;
bool ModuleUserInterface::show_about_window = false;
bool ModuleUserInterface::show_configuration_window = false;
bool ModuleUserInterface::show_console_window = false;

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

	fullscreen = false;
	resizable = false;
	borderless = false;
	fulldesktop = false;
	
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

	/* Configuration */
	if (show_configuration_window)
		ShowConfigurationWindow();

	/* Console */
	if (show_console_window)
		ShowConsoleWindow();

	/* Demo Window */
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	/* Main Menu Bar */
	if (show_main_menu_bar_window)
		ShowMainMenuBarWindow();

	/* About Window */
	if (show_about_window)
		ShowAboutWindow();

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

void ModuleUserInterface::LogToConsole(const char* text_log)
{
	text_buffer.appendf(text_log);
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

		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Configuration", NULL, & show_configuration_window);
			ImGui::MenuItem("Console", NULL, & show_console_window);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				show_about_window = true;
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
	ImGui::Text("Fracture Engine");
	ImGui::Separator();
	ImGui::Text("An educational purposes game engine");
	ImGui::Separator();
	ImGui::Text("Credits: Gerard Marcos Freixas and Marti Torras Isanta");
	ImGui::Separator();
	ImGui::Text("3rd party libraries used:");
	SDL_version sdl_version;
	SDL_VERSION(&sdl_version);
	ImGui::BulletText("SDL %d. %d. %d", sdl_version.major, sdl_version.minor, sdl_version.patch);
	ImGui::BulletText("OpenGL %s", glGetString(GL_VERSION));
	ImGui::BulletText("Glew %s", glewGetString(GLEW_VERSION));
	ImGui::BulletText("ImGui %s", ImGui::GetVersion());
	ImGui::BulletText("MathGeoLib"); ImGui::SameLine();  ImGui::Text("2.0");
	ImGui::Separator();
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

void ModuleUserInterface::ShowConfigurationWindow()
{
	ImGui::Begin("Configuration");
	ImGui::Text("Options");
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

		ImGui::Text("Limit framerate: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", App->GetMaxFPS());

		char title[CUSTOM_BUFFER_SIZE_MEDIUM];
		sprintf_s(title, CUSTOM_BUFFER_SIZE_MEDIUM, "Framerate: %.2f", App->fps_vec[App->fps_vec.size() - 1]);
		ImGui::PlotHistogram("##Framerate", &App->fps_vec[0], App->fps_vec.size(), 0, title, 0.0f, 144.0f, ImVec2(310, 100));
		sprintf_s(title, CUSTOM_BUFFER_SIZE_MEDIUM, "Milliseconds: %.2f", App->ms_vec[App->ms_vec.size() - 1]);
		ImGui::PlotHistogram("##Milliseconds", &App->ms_vec[0], App->ms_vec.size(), 0, title, 0.0f, 30.0f, ImVec2(310, 100));
	}
	if (ImGui::CollapsingHeader("Window"))
	{
		static int brightness = 50;
		static int width = 600;
		static int height = 600;
		ImGui::SliderInt("Brightness", &brightness, 0, 100);
		ImGui::SliderInt("Width", &width, 100, SCREEN_WIDTH);
		ImGui::SliderInt("Height", &height, 100, SCREEN_HEIGHT);
		ImGui::Separator();

		if (ImGui::Checkbox("Fullscreen", &fullscreen));
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Restart to apply");
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &resizable));
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Restart to apply");
		if (ImGui::Checkbox("Borderless", &borderless));
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Restart to apply");
		ImGui::SameLine();
		if (ImGui::Checkbox("Full Desktop", &fulldesktop));
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Restart to apply");
	}
	if (ImGui::CollapsingHeader("Hardware"))
	{
		SDL_version compiled;
		SDL_VERSION(&compiled);
		ImGui::Text("SDL version: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d. %d. %d", compiled.major, compiled.minor, compiled.patch);
		ImGui::Separator();
		ImGui::Text("CPUs: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), " %i (Cache: %ikb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
		ImGui::Text("System RAM: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i Mb", SDL_GetSystemRAM());
		static char caps[CUSTOM_BUFFER_SIZE_MEDIUM];
		strcpy_s(caps, CUSTOM_BUFFER_SIZE_MEDIUM, "");
		if (SDL_Has3DNow()) strcat(caps, "3DNow, ");
		if (SDL_HasAVX()) strcat(caps, "AVX, ");
		if (SDL_HasAVX2()) strcat(caps, "AVX2, ");
		if (SDL_HasAltiVec()) strcat(caps, "AltiVec, ");
		if (SDL_HasMMX()) strcat(caps, "MMX, ");
		if (SDL_HasRDTSC()) strcat(caps, "RDTSC, ");
		if (SDL_HasSSE()) strcat(caps, "SSE, ");
		if (SDL_HasSSE2()) strcat(caps, "SSE2, ");
		if (SDL_HasSSE3()) strcat(caps, "SSE3, ");
		if (SDL_HasSSE41()) strcat(caps, "SSE41, ");
		if (SDL_HasSSE42()) strcat(caps, "SSE42, ");
		ImGui::Text("Caps:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", caps);
		ImGui::Separator();
		ImGui::Text("GPU:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_RENDERER));
	}
	ImGui::End();
}

void ModuleUserInterface::ShowConsoleWindow()
{
	ImGui::Begin("Console");
	ImGui::TextUnformatted(text_buffer.begin());
	ImGui::SetScrollHere(1.0f);
	ImGui::End();
}

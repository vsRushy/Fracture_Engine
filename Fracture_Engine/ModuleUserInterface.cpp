#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "GL/glew.h"
#include "SDL/include/SDL_cpuinfo.h"

#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleInput.h"
#include "PanelConfiguration.h"

bool ModuleUserInterface::show_demo_window = false;
bool ModuleUserInterface::show_main_menu_bar_window = true;
bool ModuleUserInterface::show_about_window = false;
bool ModuleUserInterface::show_configuration_window = false;
bool ModuleUserInterface::show_console_window = false;

ModuleUserInterface::ModuleUserInterface(bool start_enabled) :  Module(start_enabled)
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

	/* Demo Window */
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	/* Configuration */
	if (show_configuration_window)
	{
		panel = new PanelConfiguration();
		show_configuration_window = false;
		is_config_open = true;
	}
	if (is_config_open)
		panel->Update(dt);

	/* Console */
	if (show_console_window)
		ShowConsoleWindow();

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
	for (std::list<std::pair<LOG_TYPE, const char*>>::iterator item = console_logs.begin(); item != console_logs.end(); item++)
	{
		free((void*)item->second); // TOCHECK
	}
	console_logs.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete panel;

	return true;
}

void ModuleUserInterface::LogToConsole(LOG_TYPE type, const char* text_log)
{
	console_logs.push_back(std::make_pair(type, strdup(text_log)));
	scroll_down_console = true;
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
			ImGui::MenuItem("Configuration", NULL, &show_configuration_window);
			ImGui::MenuItem("Console", NULL, &show_console_window);
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
			if (ImGui::MenuItem("Report a bug"))
			{
				App->RequestBrowser("https://github.com/vsRushy/Fracture_Engine/issues/");
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

void ModuleUserInterface::ShowConsoleWindow()
{
	ImGui::Begin("Console");

	for (std::list<std::pair<LOG_TYPE, const char*>>::iterator item = console_logs.begin(); item != console_logs.end(); item++)
	{ 
		char tmp_str[250];

		switch (item->first)
		{
		case LOG_INFORMATION:
			strcpy(tmp_str, "[Information]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));
			break;
		case LOG_WARNING:
			strcpy(tmp_str, "[Warning]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
			break;
		case LOG_ERROR:
			strcpy(tmp_str, "[Error]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}

		strcat(tmp_str, item->second);
		ImGui::TextUnformatted(tmp_str);
		ImGui::PopStyleColor();
	}

	if(scroll_down_console)
		ImGui::SetScrollHereY(1.0f);

	scroll_down_console = false;
	ImGui::End();
}

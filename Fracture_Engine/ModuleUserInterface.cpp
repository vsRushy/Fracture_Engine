#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "Application.h"
#include "ModuleUserInterface.h"

bool ModuleUserInterface::show_demo_window = false;
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
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/NotoSans-Regular.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	style.FrameRounding = 7.0f;
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
	/* Main Menu bar */
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close"))
			{
				return UPDATE_STOP;
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
				ShellExecute(0, 0, "https://vsrushy.github.io/Fracture_Engine/", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("GitHub"))
			{
				ShellExecute(0, 0, "https://github.com/vsRushy/Fracture_Engine/", 0, 0, SW_SHOW);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	/* Show Windows --------------------------- */

	/* Demo Window */
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	/* About Window */
	if (show_about_window)
	{
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin("About", &show_about_window, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Fracture Engine is a video game engine used for educational purposes.\n"
		"This project is part of the Video Game Engines subject. CITM - UPC.\n"
		"Credits: Gerard Marcos Freixas and Marti Torras Isanta.");
		ImGui::End();
	}

	/* License Window */
	if (show_license_window)
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

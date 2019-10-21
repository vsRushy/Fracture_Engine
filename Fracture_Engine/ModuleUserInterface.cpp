#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "GL/glew.h"
#include "SDL/include/SDL_cpuinfo.h"

#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleInput.h"

#include "Panel.h"

bool ModuleUserInterface::show_demo_window = true;
bool ModuleUserInterface::show_main_menu_bar_window = true;
bool ModuleUserInterface::show_about_window = false;
bool ModuleUserInterface::show_configuration_window = true;
bool ModuleUserInterface::show_console_window = true;

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
		ShowConfigurationWindow();

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
	for (std::list<std::pair<LOG_TYPE, const char*>>::iterator item = console_logs.begin(); item != console_logs.end(); item++)
	{
		free((void*)item->second); // TOCHECK
	}
	console_logs.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleUserInterface::LogToConsole(LOG_TYPE type, const char* text_log)
{
	console_logs.push_back(std::make_pair(type, strdup(text_log)));
	scroll_down_console = true;
}

void ModuleUserInterface::AddPanel(Panel* panel)
{
	panels.push_back(panel);
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
	ImGui::SetNextWindowPosCenter(ImGuiCond_::ImGuiCond_Always);
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
		float brightness = App->window->GetWindowBrightness();
		if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
		{
			App->window->SetWindowBrightness(brightness);
		}
		int width = App->window->GetWindowWidth();
		if (ImGui::SliderInt("Width", &width, App->window->GetScreenMinWidth(), App->window->GetScreenMaxWidth()))
		{
			App->window->SetWindowWidth(width);
		}
		int height = App->window->GetWindowHeight();
		if (ImGui::SliderInt("Height", &height, App->window->GetScreenMinHeight(), App->window->GetScreenMaxHeight()))
		{
			App->window->SetWindowHeight(height);
		}
		bool fullscreen = App->window->GetWindowFullscreen();
		if (ImGui::Checkbox("Fullscreen", &fullscreen))
		{
			App->window->SetWindowFullscreen(fullscreen);
		}
		bool resizable = App->window->GetWindowResizable();
		if (ImGui::Checkbox("Resizable", &resizable))
		{
			App->window->SetWindowResizable(resizable);
		}
		bool borderless = App->window->GetWindowBorderless();
		if (ImGui::Checkbox("Borderless", &borderless))
		{
			App->window->SetWindowBorderless(borderless);
		}
		bool fullscreen_desktop = App->window->GetWindowFullScreenDesktop();
		if (ImGui::Checkbox("Full Desktop", &fullscreen_desktop))
		{
			App->window->SetWindowFullScreenDesktop(fullscreen_desktop);
		}
	}
	if (ImGui::CollapsingHeader("Renderer"))
	{
		bool vsync = App->renderer3D->GetVSync();
		if (ImGui::Checkbox("VSync", &vsync))
		{
			App->renderer3D->SetVSync(vsync);
		}
		bool wireframe_mode = App->renderer3D->GetWireframeMode();
		if (ImGui::Checkbox("Wireframe mode", &wireframe_mode))
		{
			App->renderer3D->SetWireframeMode(wireframe_mode);
		}
		bool gl_depth_test = App->renderer3D->GetDepthTest();
		if (ImGui::Checkbox("GL_DEPTH_TEST", &gl_depth_test))
		{
			App->renderer3D->SetDepthTest(gl_depth_test);
		}
		bool gl_cull_face = App->renderer3D->GetCullFace();
		if (ImGui::Checkbox("GL_CULL_FACE", &gl_cull_face))
		{
			App->renderer3D->SetCullFace(gl_cull_face);
		}
		bool gl_lighting = App->renderer3D->GetLighting();
		if (ImGui::Checkbox("GL_LIGHTING", &gl_lighting))
		{
			App->renderer3D->SetLighting(gl_lighting);
		}
		bool gl_color_material = App->renderer3D->GetColorMaterial();
		if (ImGui::Checkbox("GL_COLOR_MATERIAL", &gl_color_material))
		{
			App->renderer3D->SetColorMaterial(gl_color_material);
		}
		bool gl_texture_2d = App->renderer3D->GetTexture2D();
		if (ImGui::Checkbox("GL_TEXTURE_2D", &gl_texture_2d))
		{
			App->renderer3D->SetTexture2D(gl_texture_2d);
		}
		bool gl_blend = App->renderer3D->GetBlend();
		if (ImGui::Checkbox("GL_BLEND", &gl_blend))
		{
			App->renderer3D->SetBlend(gl_blend);
		}
		bool gl_fog = App->renderer3D->GetFog();
		if (ImGui::Checkbox("GL_FOG", &gl_fog))
		{
			App->renderer3D->SetFog(gl_fog);
		}
		bool gl_alpha_test = App->renderer3D->GetAlphaTest();
		if (ImGui::Checkbox("GL_ALPHA_TEST", &gl_alpha_test))
		{
			App->renderer3D->SetAlphaTest(gl_alpha_test);
		}
		if (ImGui::CollapsingHeader("Advanced options"))
		{
			bool draw_mesh_lines = App->renderer3D->GetDrawMeshLines();
			if (ImGui::Checkbox("Draw mesh lines", &draw_mesh_lines))
			{
				App->renderer3D->SetDrawMeshLines(draw_mesh_lines);
			}
			ImGui::SameLine();
			ImGui::ColorEdit3("Mesh lines color", &App->renderer3D->mesh_lines_color);
			ImGui::Spacing();
			bool draw_mesh_vertices = App->renderer3D->GetDrawMeshVertices();
			if (ImGui::Checkbox("Draw mesh vertices", &draw_mesh_vertices))
			{
				App->renderer3D->SetDrawMeshVertices(draw_mesh_vertices);
			}
			ImGui::SameLine();
			ImGui::ColorEdit3("Mesh vertices color", &App->renderer3D->mesh_vertices_color);
			ImGui::Spacing();
			bool draw_mesh_vertex_normals = App->renderer3D->GetDrawMeshVertexNormals();
			if (ImGui::Checkbox("Draw mesh vertex normals", &draw_mesh_vertex_normals))
			{
				App->renderer3D->SetDrawMeshVertexNormals(draw_mesh_vertex_normals);
			}
			ImGui::SameLine();
			ImGui::ColorEdit3("Mesh vertex normals color", &App->renderer3D->mesh_vertex_normals_color);
			ImGui::Spacing();
			bool draw_mesh_face_normals = App->renderer3D->GetDrawMeshFaceNormals();
			if (ImGui::Checkbox("Draw mesh face normals", &draw_mesh_face_normals))
			{
				App->renderer3D->SetDrawMeshFaceNormals(draw_mesh_face_normals);
			}
			ImGui::SameLine();
			ImGui::ColorEdit3("Mesh face normals color", &App->renderer3D->mesh_face_normals_color);
			ImGui::Spacing();
		}
	}
	if (ImGui::CollapsingHeader("Input"))
	{
		ImGui::Text("Mouse position: ");
		ImGui::SameLine();
		ImGui::Text("X ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", App->input->GetMouseX());
		ImGui::SameLine();
		ImGui::Text("Y ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", App->input->GetMouseY());

		ImGui::Text("Mouse motion: ");
		ImGui::SameLine();
		ImGui::Text("X ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", App->input->GetMouseXMotion());
		ImGui::SameLine();
		ImGui::Text("Y ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", App->input->GetMouseYMotion());
	}
	if (ImGui::CollapsingHeader("Camera"))
	{
		float speed = App->camera->GetCameraSpeed();
		ImGui::Text("Speed: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.2f", speed);
		if (ImGui::SliderFloat("Speed", &speed, App->camera->GetMinCameraSpeed(), App->camera->GetMaxCameraSpeed()))
		{
			App->camera->SetCameraSpeed(speed);
		}
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

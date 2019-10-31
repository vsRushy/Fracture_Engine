#include "SDL/include/SDL.h"
#include "GL/glew.h"

#include "PanelConfiguration.h"
#include "Globals.h"

#include "Application.h"


PanelConfiguration::PanelConfiguration(std::string name, bool active) : Panel(name, active)
{

}

PanelConfiguration::~PanelConfiguration()
{
	
}

bool PanelConfiguration::Update()
{
	ImGui::Begin(name.c_str());
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

		float fov = App->camera->GetCameraFOV();
		ImGui::Text("FOV: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.2f", fov);
		if (ImGui::SliderFloat("FOV", &fov, App->camera->GetMinCameraFOV(), App->camera->GetMaxCameraFOV()))
		{
			App->camera->SetCameraFOV(fov);
		}

		float near_plane = App->camera->GetCameraNearPlane();
		ImGui::Text("Near plane: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.2f", near_plane);
		if (ImGui::SliderFloat("Near_plane", &near_plane, App->camera->GetMinCameraNearPlane(), App->camera->GetMaxCameraNearPlane()))
		{
			App->camera->SetCameraNearPlane(near_plane);
		}

		float far_plane = App->camera->GetCameraFarPlane();
		ImGui::Text("Far plane: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.2f", far_plane);
		if (ImGui::SliderFloat("Far_plane", &far_plane, App->camera->GetMinCameraFarPlane(), App->camera->GetMaxCameraFarPlane()))
		{
			App->camera->SetCameraFarPlane(far_plane);
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

	return true;
}


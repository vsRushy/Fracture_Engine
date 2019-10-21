#include "SDL/include/SDL.h"
#include "GL/glew.h"

#include "PanelAbout.h"
#include "Application.h"

PanelAbout::PanelAbout(std::string name, bool active) : Panel(name, active)
{

}

PanelAbout::~PanelAbout()
{
}

bool PanelAbout::Update()
{
	ImGui::SetNextWindowPosCenter(ImGuiCond_::ImGuiCond_Always);
	ImGui::Begin(name.c_str(), &(App->user_interface->panel_about->active), ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
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

	return true;
}


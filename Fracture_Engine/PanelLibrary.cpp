#include "PanelLibrary.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

PanelLibrary::PanelLibrary(std::string name, bool active) : Panel(name, active)
{

}

PanelLibrary::~PanelLibrary()
{

}

bool PanelLibrary::Update()
{
	ImGui::Begin(name.c_str());
	
	if (ImGui::CollapsingHeader("Meshes"))
	{
		for (auto item = App->scene_intro->own_meshes.begin(); item != App->scene_intro->own_meshes.end(); item++)
		{
			ImGui::Text((*item).c_str());
		}
	}

	if (ImGui::CollapsingHeader("Textures"))
	{

	}

	ImGui::End();

	return true;
}

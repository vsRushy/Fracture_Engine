#include "Texture.h"
#include "PanelAssets.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

PanelAssets::PanelAssets(std::string name, bool active) : Panel(name, active)
{

}

PanelAssets::~PanelAssets()
{

}

bool PanelAssets::Update()
{
	ImGui::Begin(name.c_str());
	/* Meshes */
	if (ImGui::CollapsingHeader("Meshes"))
	{
		
	}
	if (ImGui::CollapsingHeader("Textures"))
	{
		for (auto item = App->scene_intro->textures.begin(); item != App->scene_intro->textures.end(); item++)
		{
			ImGui::Image((ImTextureID)(*item).second->id, ImVec2(50.0f, 50.0f));
			ImGui::SameLine();
		}
	}

	ImGui::End();

	return true;
}

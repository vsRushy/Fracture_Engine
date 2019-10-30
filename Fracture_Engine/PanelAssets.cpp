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
	if (ImGui::CollapsingHeader("GameObjects"))
	{
		
	}
	if (ImGui::CollapsingHeader("Textures"))
	{
		ImGui::Columns(7);
		for (auto item = App->scene_intro->textures.begin(); item != App->scene_intro->textures.end(); item++)
		{
			ImGui::Image((ImTextureID)(*item).second->id, ImVec2(50.0f, 50.0f));
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted((*item).second->name.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
	}

	ImGui::End();

	return true;
}

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
	
	/* GameObjects */
	if (ImGui::CollapsingHeader("Game Objects"))
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
				std::string name_and_extension;
				name_and_extension.append((*item).second->name);
				name_and_extension.append((*item).second->extension);
				ImGui::TextUnformatted(name_and_extension.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("Texture", &(*item).second, sizeof(Texture*));
				ImGui::TextUnformatted((*item).second->name.c_str());
				ImGui::EndDragDropSource();
			}

			ImGui::NextColumn();
		}

		ImGui::Columns(1);
	}

	ImGui::End();

	return true;
}
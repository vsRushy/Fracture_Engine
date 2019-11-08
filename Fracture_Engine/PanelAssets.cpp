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

	if (ImGui::CollapsingHeader("Game Objects"))
	{
		// TODO
	}

	if (ImGui::CollapsingHeader("Meshes"))
	{
		// TODO
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
				ImGui::SetDragDropPayload("Texture", &(*item).first, sizeof(std::string));
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
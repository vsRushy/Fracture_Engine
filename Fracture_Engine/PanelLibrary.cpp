#include "Texture.h"

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

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("Own_mesh", &(*item), sizeof(std::string));
				ImGui::TextUnformatted((*item).c_str());
				ImGui::EndDragDropSource();
			}
		}
	}

	if (ImGui::CollapsingHeader("Textures"))
	{
		ImGui::Columns(7);

		for (auto item = App->scene_intro->own_textures.begin(); item != App->scene_intro->own_textures.end(); item++)
		{
			ImGui::Image((ImTextureID)(*item).second->id, ImVec2(50.0f, 50.0f));

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				std::string name_and_extension;
				name_and_extension.append((*item).first);
				ImGui::TextUnformatted(name_and_extension.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("Own_texture", &(*item), sizeof(std::string));
				ImGui::TextUnformatted((*item).first.c_str());
				ImGui::Image((ImTextureID)(*item).second->id, ImVec2(50.0f, 50.0f));
				ImGui::EndDragDropSource();
			}

			ImGui::NextColumn();
		}

		ImGui::Columns(1);
	}

	ImGui::End();

	return true;
}

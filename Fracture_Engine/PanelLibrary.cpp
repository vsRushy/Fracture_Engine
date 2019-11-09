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
		for (auto item = App->scene_intro->own_textures.begin(); item != App->scene_intro->own_textures.end(); item++)
		{
			ImGui::Text((*item).c_str());

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("Own_texture", &(*item), sizeof(std::string));
				ImGui::TextUnformatted((*item).c_str());
				ImGui::EndDragDropSource();
			}
		}
	}

	ImGui::End();

	return true;
}

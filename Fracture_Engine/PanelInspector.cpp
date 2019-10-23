#include "PanelInspector.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Globals.h"
#include "Component.h"
#include "Component_Transform.h"
#include "Component_Mesh.h"
#include "Component_Material.h"

PanelInspector::PanelInspector(std::string name, bool active) : Panel(name, active)
{

}

PanelInspector::~PanelInspector()
{

}

bool PanelInspector::Update()
{
	ImGui::Begin(name.c_str());

	if (App->scene_intro->selected_game_object != nullptr)
	{
		GameObject* game_object = App->scene_intro->selected_game_object;

		ImGui::Checkbox("##Active", &(game_object->active));
		ImGui::SameLine();
		char* go_name = &game_object->name[0];
		ImGui::InputText("##Name", go_name, CUSTOM_BUFFER_SIZE_MEDIUM,
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
	
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
		for (std::vector<Component*>::iterator item = game_object->components.begin();
			item != game_object->components.end(); item++)
		{
			if ((*item)->type == COMPONENT_TYPE::TRANSFORM)
			{
				ComponentTransform* tr = (ComponentTransform*)(*item);
				if (ImGui::CollapsingHeader("Transform"))
				{
					ImGui::Text("Position");
					ImGui::DragFloat3("##Position", (float*)&(tr->position));
					ImGui::Text("Rotation");
					ImGui::DragFloat3("##Rotation", (float*)&(tr->rotation));
					ImGui::Text("Scale");
					ImGui::DragFloat3("##Scale", (float*) &(tr->scale));
				}
			}

			if ((*item)->type == COMPONENT_TYPE::MESH)
			{
				ComponentMesh* tr = (ComponentMesh*)(*item);
				if (ImGui::CollapsingHeader("Mesh"))
				{

				}
			}

			if ((*item)->type == COMPONENT_TYPE::MATERIAL)
			{
				ComponentMaterial* tr = (ComponentMaterial*)(*item);
				if (ImGui::CollapsingHeader("Material"))
				{

				}
			}
		}
	}

	ImGui::End();

	return true;
}

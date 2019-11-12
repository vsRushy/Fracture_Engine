#include "PanelInspector.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Globals.h"
#include "Component.h"
#include "Component_Transform.h"
#include "Component_Mesh.h"
#include "Component_Material.h"

#include "QuadTree.h"

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

		bool go_active = game_object->IsActive();
		if (ImGui::Checkbox("##Active", &go_active))
		{
			game_object->SetActive(go_active);
		}

		ImGui::SameLine();
		char* go_name = &game_object->name[0];
		ImGui::PushItemWidth(150.0f);
		ImGui::InputText("##Name", go_name, CUSTOM_BUFFER_SIZE_MEDIUM,
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
		ImGui::PopItemWidth();

		ImGui::SameLine();

		bool go_static = game_object->IsStatic();
		if (ImGui::Checkbox("##Static", &go_static))
		{
			game_object->SetStatic(go_static);
			if(go_static)
				App->scene_intro->quad_tree->Insert(game_object);
			else
				App->scene_intro->quad_tree->Remove(game_object);
		}
		ImGui::SameLine();
		ImGui::Text("Static");
	
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
		for (std::vector<Component*>::iterator item = game_object->components.begin();
			item != game_object->components.end(); item++)
		{
			(*item)->OnEditor();
		}
	}

	ImGui::End();

	return true;
}

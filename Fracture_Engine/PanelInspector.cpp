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

		bool go_active = game_object->IsActive();
		ImGui::Checkbox("##Active", &go_active);

		game_object->SetActive(go_active);

		ImGui::SameLine();
		char* go_name = &game_object->name[0];
		ImGui::InputText("##Name", go_name, CUSTOM_BUFFER_SIZE_MEDIUM,
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
	
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

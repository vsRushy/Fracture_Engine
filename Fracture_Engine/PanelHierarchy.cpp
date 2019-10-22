#include "PanelHierarchy.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"

PanelHierarchy::PanelHierarchy(std::string name, bool active) : Panel(name, active)
{

}

PanelHierarchy::~PanelHierarchy()
{

}

bool PanelHierarchy::Update()
{
	ImGui::Begin(name.c_str());

	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
	GameObject* root = App->scene_intro->root_game_object;
	if (root != nullptr)
	{
		if (ImGui::TreeNodeEx(root->name.c_str(), node_flags))
		{
			for (std::vector<GameObject*>::iterator item = root->children.begin(); item != root->children.end(); item++)
				DrawTextGameObject(*item);

			ImGui::TreePop();
		}
	}

	ImGui::End();

	return true;
}

void PanelHierarchy::DrawTextGameObject(GameObject* game_object)
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;

	bool is_open = ImGui::TreeNodeEx(game_object->name.c_str(), node_flags);
	
	if (is_open)
	{
		for (std::vector<GameObject*>::iterator item = game_object->children.begin();
			item != game_object->children.end(); item++)
			DrawTextGameObject(*item);

		ImGui::TreePop();
	}
}

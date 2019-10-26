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

	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Selected;
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
	if (game_object != nullptr)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;

		if (game_object->children.size() == 0)
			node_flags |= ImGuiTreeNodeFlags_Leaf;

		bool is_open = ImGui::TreeNodeEx(game_object->name.c_str(), node_flags);

		bool has_been_clicked = ImGui::IsItemClicked(0);
		if (has_been_clicked)
		{
			App->scene_intro->selected_game_object = game_object;
			LOG(LOG_INFORMATION, "Clicked and selected the following Game Object: %s", game_object->name.c_str());
		}

		bool has_been_right_clicked = ImGui::IsItemClicked(1);
		if (has_been_right_clicked)
		{
			ImGui::Begin("test");
			ImGui::Text("hello");
			ImGui::End();
			LOG(LOG_INFORMATION, "Right clicked game object %s", game_object->name.c_str());
		}

		if (is_open)
		{
			for (std::vector<GameObject*>::iterator item = game_object->children.begin();
				item != game_object->children.end(); item++)
				DrawTextGameObject(*item);

			ImGui::TreePop();
		}
	}
}

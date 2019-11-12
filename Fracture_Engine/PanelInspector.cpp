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

	GameObject* go = App->scene_intro->selected_game_object;
	if (go != nullptr)
	{
		go->OnEditor();
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
		for (std::vector<Component*>::iterator item = go->components.begin();
			item != go->components.end(); item++)
		{
			(*item)->OnEditor();
		}
	}

	ImGui::End();

	return true;
}

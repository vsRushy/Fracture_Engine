#include "PanelScene.h"

PanelScene::PanelScene(std::string name, bool active) : Panel(name, active)
{

}

PanelScene::~PanelScene()
{

}

bool PanelScene::Update()
{
	if (IsActive())
	{
		ImGui::Begin(name.c_str());

		ImGui::End();
	}

	return true;
}

ImVec2 PanelScene::GetSize() const
{
	return size;
}

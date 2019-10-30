#include "PanelAssets.h"

PanelAssets::PanelAssets(std::string name, bool active) : Panel(name, active)
{

}

PanelAssets::~PanelAssets()
{

}

bool PanelAssets::Update()
{
	ImGui::Begin(name.c_str());


	ImGui::End();

	return true;
}
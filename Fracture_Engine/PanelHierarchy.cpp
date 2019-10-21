#include "PanelHierarchy.h"

PanelHierarchy::PanelHierarchy(std::string name, bool active) : Panel(name, active)
{

}

PanelHierarchy::~PanelHierarchy()
{

}

bool PanelHierarchy::Update()
{
	ImGui::Begin(name.c_str());

	ImGui::End();

	return true;
}

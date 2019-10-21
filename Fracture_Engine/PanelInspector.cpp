#include "PanelInspector.h"

PanelInspector::PanelInspector(std::string name, bool active) : Panel(name, active)
{

}

PanelInspector::~PanelInspector()
{

}

bool PanelInspector::Update()
{
	ImGui::Begin(name.c_str());

	ImGui::End();

	return true;
}

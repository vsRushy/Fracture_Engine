#include "PanelLibrary.h"

PanelLibrary::PanelLibrary(std::string name, bool active) : Panel(name, active)
{

}

PanelLibrary::~PanelLibrary()
{

}

bool PanelLibrary::Update()
{
	ImGui::Begin(name.c_str());

	ImGui::End();

	return true;
}

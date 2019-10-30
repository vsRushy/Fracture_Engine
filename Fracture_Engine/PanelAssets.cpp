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
	/* Meshes */
	if (ImGui::CollapsingHeader("Meshes"))
	{
		for (uint i = 0; i < 10; i++)
		{

		}
	}
	if (ImGui::CollapsingHeader("Textures"))
	{

	}

	ImGui::End();

	return true;
}

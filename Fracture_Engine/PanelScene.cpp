#include "PanelScene.h"

#include "Application.h"
#include "ModuleRenderer3D.h"

PanelScene::PanelScene(std::string name, bool active) : Panel(name, active)
{

}

PanelScene::~PanelScene()
{

}

bool PanelScene::Update()
{
	ImGui::Begin(name.c_str());

	SetViewportSize(ImGui::GetContentRegionAvail());
	ImGui::Image((ImTextureID)App->renderer3D->frame_buffer_object.texture_id, ImVec2(viewport_size.x, viewport_size.y), ImVec2(0, 1), ImVec2(1, 0));

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture");
		ImGui::EndDragDropTarget();
	}

	ImGui::End();

	return true;
}

ImVec2 PanelScene::GetViewportSize() const
{
	return viewport_size;
}

void PanelScene::SetViewportSize(const ImVec2& size)
{
	viewport_size = size;
}

#include "Texture.h"
#include "PanelScene.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleImporter.h"



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
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture"))
		{
			IM_ASSERT(payload->DataSize == sizeof(std::string));
			std::string tex_drop = *(std::string*)payload->Data;

			Texture* t = App->scene_intro->textures[tex_drop];

			std::string file_tex_path = TEXTURE_ROOT_PATH;
			file_tex_path.append(t->name);
			file_tex_path.append(t->extension);
			App->importer->LoadDroppedFile(file_tex_path.c_str());

			LOG(LOG_INFORMATION, "Dropped texture into the scene");
		}

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

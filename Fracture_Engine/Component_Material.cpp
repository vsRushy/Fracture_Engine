#include <string>

#include "Component_Material.h"
#include "Texture.h"
#include "ImGui/imgui.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleImporter.h"

ComponentMaterial::ComponentMaterial(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::MATERIAL;
}

ComponentMaterial::~ComponentMaterial()
{

}
 
void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Checkbox("Active", &active);
		
		std::string m_name = texture->name;
		m_name.append(texture->extension);
		ImGui::Text("Material name: "); ImGui::SameLine(); ImGui::Text(m_name.c_str());
		
		std::string m_path = TEXTURE_ROOT_PATH;
		m_path.append(texture->name);
		ImGui::Text("Material path: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), m_path.c_str());

		std::string t_width = std::to_string(texture->width);
		ImGui::Text("Texture width: "); ImGui::SameLine(); 
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), t_width.c_str());

		std::string t_height = std::to_string(texture->height);
		ImGui::Text("Texture height: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), t_height.c_str());

		ImGui::Text("Preview: "); ImGui::SameLine(); ImGui::Image((ImTextureID)texture->id, ImVec2(100.0f, 100.0f));
	
		if (ImGui::Checkbox("Use checkered texture", &use_checkered_texture))
		{
			if(use_checkered_texture)
				SetTexture(App->scene_intro->textures["Checkers.dds"]);
			else
				SetTexture(initial_texture);
		}
	}
}

void ComponentMaterial::SetTexture(Texture* texture)
{
	this->texture = texture;
}

void ComponentMaterial::SetInitialTexture(Texture* texture)
{
	this->initial_texture = texture;
}

void ComponentMaterial::SetTextureByPath(const std::string& path)
{
	/* Note that for the checkered texture we only use the name */

	for (std::map<std::string, Texture*>::const_iterator item = App->scene_intro->textures.begin();
		item != App->scene_intro->textures.end(); item++)
	{
		if ((*item).first == path)
		{
			SetTexture((*item).second);
		}
	}
}

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

void ComponentMaterial::Load(JSON_Object* json_object)
{
	id_material = json_object_get_number(json_object, "ID Material");
	texture->texture_path = std::string(json_object_get_string(json_object, "Path"));
	/* TODO: Load and assign */
}

void ComponentMaterial::Save(JSON_Array* json_array) const
{
	JSON_Value* value = json_value_init_object();
	JSON_Object* object = json_value_get_object(value);

	json_object_set_number(object, "Component Type", (double)type);
	json_object_set_number(object, "ID Material", id_material);

	std::string tmp_path;
	if (texture != nullptr)
		tmp_path = texture->texture_path;
	
	json_object_set_string(object, "Path", tmp_path.c_str());

	json_array_append_value(json_array, value);
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

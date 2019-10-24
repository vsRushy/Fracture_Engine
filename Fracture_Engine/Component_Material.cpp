#include <string>

#include "Component_Material.h"
#include "Texture.h"
#include "ImGui/imgui.h"

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
		ImGui::Text("Material path: "); ImGui::SameLine(); ImGui::Text(m_name.c_str());
		
		std::string t_width = std::to_string(texture->width);
		ImGui::Text("Texture width: "); ImGui::SameLine(); 
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), t_width.c_str());

		std::string t_height = std::to_string(texture->height);
		ImGui::Text("Texture height: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), t_height.c_str());

		ImGui::Text("Preview: "); ImGui::SameLine(); ImGui::Image((ImTextureID)texture->id, ImVec2(100.0f, 100.0f));
	}
}

void ComponentMaterial::SetTexture(Texture* texture)
{
	this->texture = texture;
}

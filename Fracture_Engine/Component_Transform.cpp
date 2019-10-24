#include "Component_Transform.h"
#include "ImGui/imgui.h"

ComponentTransform::ComponentTransform(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::TRANSFORM;
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Checkbox("Active", &active);
		ImGui::Text("Position");
		ImGui::DragFloat3("##Position", (float*) &position);
		ImGui::Text("Rotation");
		ImGui::DragFloat3("##Rotation", (float*) &rotation);
		ImGui::Text("Scale");
		ImGui::DragFloat3("##Scale", (float*) &scale);
	}
}

void ComponentTransform::Set(const math::float3& position, const math::Quat& rotation, const math::float3& scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

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

void ComponentTransform::SetPosition(const float& x, const float& y, const float& z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void ComponentTransform::SetRotation(const float& w, const float& x, const float& y, const float& z)
{
	this->rotation.w = w;
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
}

void ComponentTransform::SetScale(const float& x, const float& y, const float& z)
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;
}

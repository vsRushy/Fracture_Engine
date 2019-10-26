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
	position.Set(x, y, z);
}

void ComponentTransform::SetRotationQuaternion(const float& w, const float& x, const float& y, const float& z)
{
	rotation.Set(x, y, z, w);
}

void ComponentTransform::SetRotationEuler(const float& x, const float& y, const float& z)
{
	euler_rotation.Set(x, y, z);
}

void ComponentTransform::SetScale(const float& x, const float& y, const float& z)
{
	scale.Set(x, y, z);
}

float3 ComponentTransform::GetPosition() const
{
	return position;
}

Quat ComponentTransform::GetRotationQuaternion() const
{
	return rotation;
}

float3 ComponentTransform::GetRotationEuler() const
{
	return euler_rotation;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

float4x4 ComponentTransform::GetLocalMatrix() const
{
	return local_matrix;
}

float4x4 ComponentTransform::GetGlobalMatrix() const
{
	return global_matrix;
}

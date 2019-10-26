#include "ImGui/imgui.h"
#include "GL/glew.h"

#include "Component_Transform.h"

#include "GameObject.h"

ComponentTransform::ComponentTransform(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::TRANSFORM;

	CalculateLocalMatrix();
}

ComponentTransform::~ComponentTransform()
{

}

bool ComponentTransform::PreUpdate(float dt)
{
	glPushMatrix();

	return true;
}

bool ComponentTransform::Update(float dt)
{
	glMultMatrixf(GetGlobalMatrix().Transposed().ptr());

	return true;
}

bool ComponentTransform::PostUpdate(float dt)
{
	glPopMatrix();

	return true;
}

void ComponentTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Checkbox("Active", &active);
		ImGui::Text("Position");
		if (ImGui::DragFloat3("##Position", (float*)& position, 0.05f))
		{
			CalculateLocalMatrix();
		}
		ImGui::Text("Rotation");

		if(ImGui::DragFloat3("##Rotation", (float*)&euler_rotation,
			0.05f, -360.0f, 360.0f))
		{
			float3 euler_in_radians = DegToRad(euler_rotation);
			rotation = Quat::FromEulerXYZ(euler_in_radians.x, euler_in_radians.y, euler_in_radians.z);
			CalculateLocalMatrix();
		}

		ImGui::Text("Scale");
		if(ImGui::DragFloat3("##Scale", (float*)& scale, 0.05f, 0.0f, 100.0f))
		{
			CalculateLocalMatrix();
		}
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

void ComponentTransform::CalculateLocalMatrix()
{
	local_matrix = float4x4::FromTRS(position, rotation, scale);
	
	CalculateGlobalMatrix();
	
	for (std::vector<GameObject*>::const_iterator item = target->children.begin(); item != target->children.end(); item++)
	{
		(*item)->component_transform->CalculateGlobalMatrix();
	}
}

void ComponentTransform::CalculateGlobalMatrix()
{
	global_matrix = local_matrix;
	
	if (target->parent != nullptr)
	{
		global_matrix = target->parent->component_transform->global_matrix * local_matrix;
	}
}

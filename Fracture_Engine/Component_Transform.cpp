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

void ComponentTransform::SetPosition(const float& x, const float& y, const float& z)
{
	position.Set(x, y, z);
}

void ComponentTransform::SetRotation(const float& w, const float& x, const float& y, const float& z)
{
	rotation.Set(x, y, z, w);
}

void ComponentTransform::SetScale(const float& x, const float& y, const float& z)
{
	scale.Set(x, y, z);
}

void ComponentTransform::CalculateLocalMatrix()
{
	local_matrix = float4x4::FromTRS(position, rotation, scale);
}

void ComponentTransform::CalculateGlobalMatrix()
{
	global_matrix = local_matrix;
	if (target->parent != nullptr) 
	{
		global_matrix = target->parent->component_transform->global_matrix * local_matrix;
	}
}

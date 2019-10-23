#include "Component_Transform.h"

ComponentTransform::ComponentTransform(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::TRANSFORM;
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::Set(const math::float3& position, const math::Quat& rotation, const math::float3& scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

#include "ComponentCamera.h"

ComponentCamera::ComponentCamera(GameObject* target) : Component(target)
{
	
}

ComponentCamera::~ComponentCamera()
{

}

bool ComponentCamera::PreUpdate(float dt)
{
	return true;
}

bool ComponentCamera::Update(float dt)
{
	return true;
}

bool ComponentCamera::PostUpdate(float dt)
{
	return true;
}

void ComponentCamera::OnEditor()
{

}

void ComponentCamera::Load(JSON_Object* json_object)
{

}

void ComponentCamera::Save(JSON_Array* json_array) const
{

}

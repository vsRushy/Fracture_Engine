#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* target) : target(target)
{

}

Component::~Component()
{

}

bool Component::PreUpdate(float dt)
{
	return true;
}

bool Component::Update(float dt)
{
	return true;
}

bool Component::PostUpdate(float dt)
{
	return true;
}

void Component::SetActive(const bool& value)
{
	active = value;
}

bool Component::IsActive() const
{
	return active;
}

void Component::OnEditor()
{

}

void Component::Load(JSON_Object* json_object)
{

}

void Component::Save(JSON_Array* json_array) const
{

}

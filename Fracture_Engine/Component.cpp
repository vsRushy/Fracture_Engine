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
	return active ?  true : false;
}

bool Component::Update(float dt)
{
	return active ? true : false;
}

bool Component::PostUpdate(float dt)
{
	return active ? true : false;
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

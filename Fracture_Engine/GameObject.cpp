#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string name, GameObject* parent)
	: name(name), parent(parent)
{
	CreateComponent(COMPONENT_TYPE::TRANSFORM);
}

GameObject::~GameObject()
{

}

bool GameObject::PreUpdate(float dt)
{
	bool ret = false;
	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		ret = (*item)->PreUpdate(dt);
	}

	return ret;
}

bool GameObject::Update(float dt)
{
	bool ret = false;
	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		ret = (*item)->Update(dt);
	}

	return ret;
}

bool GameObject::PostUpdate(float dt)
{
	bool ret = false;
	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		ret = (*item)->PostUpdate(dt);
	}

	return ret;
}

bool GameObject::CleanUp()
{
	return true;
}

void GameObject::SetActive(bool value)
{
	active = value;

	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		(*item)->SetActive(value);
	}
}

bool GameObject::IsActive() const
{
	return active;
}

Component* GameObject::CreateComponent(COMPONENT_TYPE type)
{
	return nullptr;
}

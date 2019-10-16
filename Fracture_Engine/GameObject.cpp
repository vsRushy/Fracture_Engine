#include "GameObject.h"
#include "Component.h"
#include "Component_Transform.h"

GameObject::GameObject(std::string name, GameObject* parent)
	: name(name), parent(parent)
{
	CreateComponent(COMPONENT_TYPE::TRANSFORM);
}

GameObject::~GameObject()
{
	for (std::vector<Component*>::reverse_iterator item = components.rbegin(); item != components.rend(); item++)
	{
		delete* item;
		*item = nullptr;
	}
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
	Component* component = nullptr;
	
	switch (type)
	{
	case COMPONENT_TYPE::TRANSFORM:
		component = new ComponentTransform(this);
		components.push_back(component);
		break;

	case COMPONENT_TYPE::MESH:
		component = new Component(this);
		components.push_back(component);
		break;

	case COMPONENT_TYPE::MATERIAL:
		component = new Component(this);
		components.push_back(component);
		break;

	case COMPONENT_TYPE::UNKNOWN:
		break;

	default:
		break;
	}

	return component;
}

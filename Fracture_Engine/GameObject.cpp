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
	return true;
}

bool GameObject::Update(float dt)
{
	return true;
}

bool GameObject::PostUpdate(float dt)
{
	return true;
}

bool GameObject::CleanUp()
{
	return true;
}

void GameObject::SetActive(bool value)
{
	active = value;
}

bool GameObject::IsActive() const
{
	return active;
}

Component* GameObject::CreateComponent(COMPONENT_TYPE type)
{
	return nullptr;
}

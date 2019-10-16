#include "GameObject.h"

#include "Component.h"
#include "Component_Transform.h"
#include "Component_Mesh.h"

#include "Mesh.h"

GameObject::GameObject(std::string name, GameObject* parent)
	: name(name), parent(parent)
{
	CreateComponentTransform();
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

Component* GameObject::CreateComponentTransform()
{
	Component* component_transform = new ComponentTransform(this);
	components.push_back(component_transform);

	return component_transform;
}

Component* GameObject::CreateComponentMesh(Mesh* mesh)
{
	Component* component_mesh = new ComponentMesh(this, mesh);
	components.push_back(component_mesh);

	return component_mesh;
}

Component* GameObject::CreateComponentMaterial()
{
	Component* component_material = nullptr;

	// TODO

	/*component_material = new Component(this);
	components.push_back(component_material);

	return component_material;*/

	return component_material;
}

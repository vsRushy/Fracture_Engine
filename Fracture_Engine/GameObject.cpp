#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "GameObject.h"
#include "Component.h"
#include "Component_Transform.h"
#include "Component_Mesh.h"

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
	Component* component_transform = nullptr;
	
	component_transform = new ComponentTransform(this);
	components.push_back(component_transform);

	return component_transform;
}

Component* GameObject::CreateComponentMesh(const char* meshes_name)
{
	Component* component_mesh = nullptr;

	component_mesh = new ComponentMesh(this, meshes_name);
	components.push_back(component_mesh);

	return component_mesh;
}

Component* GameObject::CreateComponentMaterial()
{
	return nullptr;
}

/*void GameObject::AssignMeshesToComponentMesh(const char* name)
{
	std::map<const char*, std::list<Mesh*>>::iterator item1;
	item1 = App->scene_intro->meshes.find(name);

	std::list<Mesh*> to_copy = (*item1).second;

	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == COMPONENT_TYPE::MESH)
		{
			ComponentMesh* c_m = (ComponentMesh*)*item;
			for (std::list<Mesh*>::iterator item_copy = to_copy.begin(); item_copy != to_copy.end(); item++)
			{
				c_m->meshes.push_back(*item_copy);
			}
		}
	}
}*/

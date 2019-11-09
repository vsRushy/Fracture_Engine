#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "GameObject.h"

#include "Component.h"
#include "Component_Transform.h"
#include "Component_Mesh.h"
#include "Component_Material.h"

GameObject::GameObject(std::string name, GameObject* parent)
	: name(name), parent(parent)
{
	this->component_transform = (ComponentTransform*)CreateComponentTransform();

	if (parent != nullptr)
		parent->children.push_back(this);
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
		if ((*item)->IsActive())
			ret = (*item)->PreUpdate(dt);
		else
			ret = true;
	}

	return ret;
}

bool GameObject::Update(float dt)
{
	bool ret = false;
	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->IsActive())
			ret = (*item)->Update(dt);
		else 
			ret = true;
	}

	if(this->IsActive())
		App->renderer3D->DrawGameObject(this);

	return ret;
}

bool GameObject::PostUpdate(float dt)
{
	bool ret = false;
	for (std::vector<Component*>::iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->IsActive())
			ret = (*item)->PostUpdate(dt);
		else
			ret = true;
	}

	return ret;
}

void GameObject::SetActive(bool value)
{
	active = value;

	for (auto item = children.begin(); item != children.end(); item++)
	{
		(*item)->SetActive(value);
	}

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
	Component* component_material = new ComponentMaterial(this);
	components.push_back(component_material);

	return component_material;
}

ComponentMesh* GameObject::GetComponentMesh() const
{
	for (std::vector<Component*>::const_iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == COMPONENT_TYPE::MESH)
		{
			return (ComponentMesh*)*item;
		}
	}
}

ComponentMaterial* GameObject::GetComponentMaterial() const
{
	for (std::vector<Component*>::const_iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == COMPONENT_TYPE::MATERIAL)
		{
			return (ComponentMaterial*)*item;
		}
	}
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

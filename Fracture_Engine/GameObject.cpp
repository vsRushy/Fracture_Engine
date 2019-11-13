#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "QuadTree.h"

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
		RELEASE(*item);
	}
	components.clear();
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

	UpdateBoundingBox();

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

	/* Draw bounding box at post-update */
	DrawBoundingBox();
	
	return ret;
}

void GameObject::SetActive(const bool& value)
{
	active = value;

	for (auto item = children.begin(); item != children.end(); item++)
	{
		(*item)->SetActive(value);
	}

	for (auto item = components.begin(); item != components.end(); item++)
	{
		(*item)->SetActive(value);
	}
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetStatic(const bool& value)
{
	is_static = value;
}

bool GameObject::IsStatic() const
{
	return is_static;
}

void GameObject::UpdateBoundingBox()
{
	bounding_box.SetNegativeInfinity();

	ComponentMesh* tmp_mesh = GetComponentMesh();
	if (tmp_mesh != nullptr) {

		bounding_box.Enclose((const float3*)GetComponentMesh()->mesh->vertices, tmp_mesh->mesh->num_vertices);
	}

	if (component_transform) {

		obb_box.SetFrom(bounding_box);
		obb_box.Transform(component_transform->GetGlobalMatrix());
		
		if (obb_box.IsFinite())
		{
			bounding_box = obb_box.MinimalEnclosingAABB();
		}
	}

	for (uint i = 0; i < children.size(); ++i)
	{
		children[i]->UpdateBoundingBox();
	}
}

void GameObject::DrawBoundingBox()
{
	glBegin(GL_LINES);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	for (uint i = 0; i < bounding_box.NumEdges(); i++)
	{
		glVertex3f(bounding_box.Edge(i).a.x, bounding_box.Edge(i).a.y, bounding_box.Edge(i).a.z);
		glVertex3f(bounding_box.Edge(i).b.x, bounding_box.Edge(i).b.y, bounding_box.Edge(i).b.z);
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();

	for (uint i = 0; i < children.size(); i++)
	{
		children[i]->DrawBoundingBox();
	}
}

void GameObject::OnEditor()
{
	if (ImGui::Checkbox("##Active", &active))
	{
		SetActive(this);
	}

	ImGui::SameLine();
	ImGui::PushItemWidth(150.0f);
	ImGui::InputText("##Name", (char*)name.c_str(), CUSTOM_BUFFER_SIZE_MEDIUM,
		ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	if (ImGui::Checkbox("##Static", &is_static))
	{
		SetStatic(is_static);
		if (is_static)
			App->scene_intro->quad_tree->Insert(this);
		else
			App->scene_intro->quad_tree->Remove(this);
	}
	ImGui::SameLine();
	ImGui::Text("Static");
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
	ComponentMesh* tmp_m = nullptr;
	for (std::vector<Component*>::const_iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == COMPONENT_TYPE::MESH)
		{
			tmp_m = (ComponentMesh*)*item;
			break;
		}
	}

	return tmp_m;
}

ComponentMaterial* GameObject::GetComponentMaterial() const
{
	ComponentMaterial* tmp_mat = nullptr;
	for (std::vector<Component*>::const_iterator item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == COMPONENT_TYPE::MATERIAL)
		{
			tmp_mat = (ComponentMaterial*)*item;
			break;
		}
	}
	
	return tmp_mat;
}

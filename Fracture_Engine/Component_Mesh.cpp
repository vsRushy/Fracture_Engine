#include <list>
#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target, const char* name_meshes) : Component(target)
{
	type = COMPONENT_TYPE::MESH;
	CopyMeshes(name_meshes);
}

ComponentMesh::~ComponentMesh()
{

}

bool ComponentMesh::Update(float dt)
{
	for (std::list<Mesh*>::iterator item = meshes.begin(); item != meshes.end(); item++)
	{
		App->renderer3D->DrawMesh(*item);
	}

	return true;
}

void ComponentMesh::CopyMeshes(const char* name)
{
	std::map<const char*, std::list<Mesh*>>::iterator item_mesh;
	item_mesh = App->scene_intro->meshes.find(name);

	std::list<Mesh*> to_copy = (*item_mesh).second;

	meshes = to_copy;
}

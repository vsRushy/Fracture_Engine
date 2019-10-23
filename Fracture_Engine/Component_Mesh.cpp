#include <list>
#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target, Mesh* mesh) : Component(target), mesh(mesh)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{

}

bool ComponentMesh::Update(float dt)
{
	return true;
}

#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target, std::list<Mesh*> meshes) : Component(target), meshes(meshes)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{

}

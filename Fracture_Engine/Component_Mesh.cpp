#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{

}

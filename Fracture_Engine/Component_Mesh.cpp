#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target, const char* name_meshes) : Component(target)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{

}

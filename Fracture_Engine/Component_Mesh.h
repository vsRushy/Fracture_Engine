#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"
#include "Mesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* target, Mesh* mesh);
	~ComponentMesh();

private:
	Mesh* mesh = nullptr;
};

#endif /* __COMPONENT_MESH_H__ */
#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* target, Mesh* mesh);
	~ComponentMesh();

public:
	Mesh* mesh = nullptr;
};

#endif /* __COMPONENT_MESH_H__ */
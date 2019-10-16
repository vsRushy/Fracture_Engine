#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"

class Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* target);
	~ComponentMesh();

private:
	Mesh* mesh = nullptr;
};

#endif /* __COMPONENT_MESH_H__ */
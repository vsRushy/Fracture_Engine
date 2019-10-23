#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include <list>

#include "Component.h"
#include "Mesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* target, Mesh* mesh);
	~ComponentMesh();

	bool Update(float dt);

public:
	Mesh* mesh;
};

#endif /* __COMPONENT_MESH_H__ */
#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include <list>

#include "Component.h"
#include "Mesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* target, const char* name_meshes);
	~ComponentMesh();

public:
	std::list<Mesh*> meshes;
};

#endif /* __COMPONENT_MESH_H__ */
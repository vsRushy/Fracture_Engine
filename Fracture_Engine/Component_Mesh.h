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

	void OnEditor() override;

	void Load(JSON_Object* json_object) override;
	void Save(JSON_Array* json_array) const override;

	bool Update(float dt);

public:
	Mesh* mesh;
};

#endif /* __COMPONENT_MESH_H__ */
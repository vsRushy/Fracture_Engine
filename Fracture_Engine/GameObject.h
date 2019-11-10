#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "Component.h"
#include "Mesh.h"
#include "MathGeoLib/include/Geometry/AABB.h"
#include "MathGeoLib/include/Geometry/OBB.h"

class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class Mesh;
class GameObject
{
public:
	GameObject(std::string name, GameObject* parent);
	~GameObject();

	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);

	void SetActive(bool value);
	bool IsActive() const;

	// ------------------------------------------

	Component* CreateComponentTransform();
	Component* CreateComponentMesh(Mesh* mesh);
	Component* CreateComponentMaterial();

	ComponentMesh* GetComponentMesh() const;
	ComponentMaterial* GetComponentMaterial() const;

	void UpdateBoundingBox();
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name = nullptr;
	bool active = true;

	ComponentTransform* component_transform = nullptr;
	Mesh* mesh = nullptr;

	std::vector<Component*> components;
	AABB boundingBox;
	OBB obbBox;

private:

};

#endif /* __GAME_OBJECT_H__ */
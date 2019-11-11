#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "MathGeoLib.h"

#include "Component.h"
#include "Mesh.h"

class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;

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

	void UpdateBoundingBox();
	void DrawBoundingBox();

	// ------------------------------------------

	Component* CreateComponentTransform();
	Component* CreateComponentMesh(Mesh* mesh);
	Component* CreateComponentMaterial();

	ComponentMesh* GetComponentMesh() const;
	ComponentMaterial* GetComponentMaterial() const;
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name = nullptr;
	bool active = true;

	ComponentTransform* component_transform;

	std::vector<Component*> components;

	AABB bounding_box;
	OBB obb_box;

private:

};

#endif /* __GAME_OBJECT_H__ */
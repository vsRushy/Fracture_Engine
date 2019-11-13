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
class ComponentCamera;

class GameObject
{
public:
	GameObject(std::string name, GameObject* parent);
	~GameObject();

	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);

	void SetActive(const bool& value);
	bool IsActive() const;

	void SetStatic(const bool& value);
	bool IsStatic() const;

	void UpdateBoundingBox();
	void DrawBoundingBox();

	void OnEditor();

	// ------------------------------------------

	Component* CreateComponentTransform();
	Component* CreateComponentMesh(Mesh* mesh);
	Component* CreateComponentMaterial();
	Component* CreateComponentCamera();

	ComponentMesh* GetComponentMesh() const;
	ComponentMaterial* GetComponentMaterial() const;
	ComponentCamera* GetComponentCamera() const;
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name = nullptr;
	bool active = true;

	bool is_static = false;

	ComponentTransform* component_transform;

	std::vector<Component*> components;

	AABB bounding_box;
	OBB obb_box;

private:

};

#endif /* __GAME_OBJECT_H__ */
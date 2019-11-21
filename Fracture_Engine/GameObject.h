#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "JSON/parson.h"

#include "MathGeoLib.h"

#include "Globals.h"
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

	void SetActive(const bool& value);
	bool IsActive() const;

	void SetStatic(const bool& value);
	bool IsStatic() const;

	void UpdateBoundingBox();
	void DrawBoundingBox();

	void OnEditor();

	void Load(JSON_Object* json_object);
	void Save(JSON_Array* json_array) const;

	// ------------------------------------------

	Component* CreateComponentTransform();
	Component* CreateComponentMesh(Mesh* mesh);
	Component* CreateComponentMaterial();

	ComponentMesh* GetComponentMesh() const;
	ComponentMaterial* GetComponentMaterial() const;
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name;
	bool active = true;

	bool is_static = false;

	ComponentTransform* component_transform;

	std::vector<Component*> components;

	AABB bounding_box;
	OBB obb_box;

private:
	uint64 id;
};

#endif /* __GAME_OBJECT_H__ */
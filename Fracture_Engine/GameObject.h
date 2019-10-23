#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "Component.h"
#include "Mesh.h"

enum class GAME_OBJECT_TYPE
{
	UNKNOWN = -1,

	MODEL,
	PRIMITIVE,
	EMPTY
};

class ComponentTransform;

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

	// ------------------------------------------

	//void AssignMeshesToComponentMesh(const char* name);
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name = nullptr;
	bool active = true;

	GAME_OBJECT_TYPE type = GAME_OBJECT_TYPE::UNKNOWN;

	ComponentTransform* component_transform;

	std::vector<Component*> components;

private:

};

#endif /* __GAME_OBJECT_H__ */
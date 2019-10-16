#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "Component.h"
#include "Mesh.h"

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
	Component* CreateComponentMesh();
	Component* CreateComponentMaterial();

	// ------------------------------------------

	void AssignMeshesToComponentMesh(const char* name);
	
public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	std::string name = nullptr;
	bool active = true;

	std::vector<Component*> components;

private:

};

#endif /* __GAME_OBJECT_H__ */
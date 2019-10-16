#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <vector>
#include <string>

#include "Component.h"

class GameObject
{
public:
	GameObject(std::string name, GameObject* parent);
	~GameObject();

	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	void SetActive(bool value);
	bool IsActive() const;

	Component* CreateComponent(COMPONENT_TYPE type);

public:
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

private:
	std::string name = nullptr;
	bool active = true;

	std::vector<Component*> components;
};

#endif /* __GAME_OBJECT_H__ */
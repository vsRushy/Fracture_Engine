#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "JSON/parson.h"

class GameObject;

enum class COMPONENT_TYPE
{
	UNKNOWN = -1,

	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA,
};

class Component
{
public:
	Component(GameObject* target);
	virtual ~Component();

	virtual bool PreUpdate(float dt);
	virtual bool Update(float dt);
	virtual bool PostUpdate(float dt);

	virtual void SetActive(const bool& value);
	virtual bool IsActive() const;

	virtual void OnEditor();

	virtual void Load(JSON_Object* json_object);
	virtual void Save(JSON_Array* json_array) const;

public:
	bool active = true;
	GameObject* target = nullptr;
	COMPONENT_TYPE type = COMPONENT_TYPE::UNKNOWN;

private:
};

#endif /* __COMPONENT_H__ */
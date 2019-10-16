#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class GameObject;

enum class COMPONENT_TYPE
{
	UNKNOWN = -1,

	TRANSFORM,
	MESH,
	MATERIAL,
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

private:
	bool active = true;
	GameObject* target = nullptr;
};

#endif /* __COMPONENT_H__ */
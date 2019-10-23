#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"

class Texture;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* target);
	~ComponentMaterial();

	void SetTexture(Texture* texture);

public:
	Texture* texture = nullptr;
};

#endif /* __COMPONENT_MATERIAL_H__ */
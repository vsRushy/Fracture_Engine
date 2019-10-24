#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include <string>

#include "Component.h"

class Texture;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* target);
	~ComponentMaterial();

	void OnEditor() override;

	void SetTexture(Texture* texture);

	/* This will find the texture by the name at the std::map in the scenee */
	void SetTextureByPath(const std::string& path);

public:
	Texture* texture = nullptr;
};

#endif /* __COMPONENT_MATERIAL_H__ */
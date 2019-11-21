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

	void Load(JSON_Object* json_object) override;
	void Save(JSON_Array* json_array) const override;

	void SetTexture(Texture* texture);
	void SetInitialTexture(Texture* texture);

	/* This will find the texture by the name at the std::map in the scenee */
	void SetTextureByPath(const std::string& path);

public:
	Texture* texture = nullptr;

	/* Store the first texture ever loaded to the component */
	Texture* initial_texture = nullptr;

	bool use_checkered_texture = false;
};

#endif /* __COMPONENT_MATERIAL_H__ */
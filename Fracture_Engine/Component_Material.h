#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* target);
	~ComponentMaterial();
};

#endif /* __COMPONENT_MATERIAL_H__ */
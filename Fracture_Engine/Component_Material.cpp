#include "Component_Material.h"
#include "Texture.h"

ComponentMaterial::ComponentMaterial(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::MATERIAL;
}

ComponentMaterial::~ComponentMaterial()
{

}

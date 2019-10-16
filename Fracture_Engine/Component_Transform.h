#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "MathGeoLib.h"

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* target);
	~ComponentTransform();

private:
	float3 position = float3::zero;
	float3 rotation = float3::zero;
	float3 scale = float3::zero;
	
	float4x4 local_matrix = float4x4::identity;
	float4x4 global_matrix = float4x4::identity;
};

#endif /* __COMPONENT_TRANSFORM_H__ */
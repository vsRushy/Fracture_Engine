#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "MathGeoLib.h"

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* target);
	~ComponentTransform();

	void OnEditor() override;

	void Set(const math::float3& position, const math::Quat& rotation, const math::float3& scale);
	void SetPosition(const float& x, const float& y, const float& z);
	void SetRotation(const float& w, const float& x, const float& y, const float& z);
	void SetScale(const float& x, const float& y, const float& z);

public:
	float3 position = float3::zero;
	Quat rotation = Quat::identity;
	float3 scale = float3::one;
	
	float4x4 local_matrix = float4x4::identity;
	float4x4 global_matrix = float4x4::identity;
};

#endif /* __COMPONENT_TRANSFORM_H__ */
#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "MathGeoLib.h"

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* target);
	~ComponentTransform();

	bool PreUpdate(float dt) override;
	bool Update(float dt) override;
	bool PostUpdate(float dt) override;

	void OnEditor() override;

	void Set(const math::float3& position, const math::Quat& rotation, const math::float3& scale);
	void SetPosition(const float& x, const float& y, const float& z);
	void SetRotationQuaternion(const float& w, const float& x, const float& y, const float& z);
	void SetRotationEuler(const float& x, const float& y, const float& z);
	void SetScale(const float& x, const float& y, const float& z);

	float3 GetPosition() const;
	Quat GetRotationQuaternion() const;
	float3 GetRotationEuler() const;
	float3 GetScale() const;

	float4x4 GetLocalMatrix() const;
	float4x4 GetGlobalMatrix() const;
	const AABB GetBoundingBox() const;

	void CalculateLocalMatrix();
	void CalculateGlobalMatrix();

private:
	float3 position = float3::zero;
	Quat rotation = Quat::identity;
	float3 euler_rotation = float3::zero;
	float3 scale = float3::one;
	
	float4x4 local_matrix = float4x4::identity;
	float4x4 global_matrix = float4x4::identity;

	AABB bounding_box;
};

#endif /* __COMPONENT_TRANSFORM_H__ */
#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "MathGeoLib.h"

#include "Component.h"

#include "Globals.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* target);
	~ComponentCamera();

	bool PreUpdate(float dt) override;
	bool Update(float dt) override;
	bool PostUpdate(float dt) override;

	void OnEditor() override;

	void Load(JSON_Object* json_object) override;
	void Save(JSON_Array* json_array) const override;

	void DrawFrustum();

public:
	/* Getters */
	Frustum  GetFrustrum() const;

	float4x4 GetViewMatrix() const;
	float4x4 GetProjectionMatrix() const;

	/* Setters */
	void SetPosition(const float3& position);

	void SetFrustumVertices();
	void SetFrustumQuad(const float3& position, const float& width, const float& height, const float& depth);

private:
	Frustum frustum;

	float aspect_ratio = 1.0f;

	float horizontal_fov = NULL;
	float vertical_fov = NULL;
	
	float far_plane = NULL;
	float near_plane = NULL;

private:
	uint id_f_vertices = -1;
	uint id_f_indices = -1;
};

#endif /* __COMPONENT_CAMERA_H__ */
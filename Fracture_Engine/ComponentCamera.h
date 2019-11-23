#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "MathGeoLib/include/Geometry/Frustum.h"

#include "Component.h"

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

private:
	Frustum frustum;
	
	float3 cam_points;

	float horizontal_fov = NULL;
	float vertical_fov = NULL;

	float far_plane = NULL;
	float near_plane = NULL;
};

#endif /* __COMPONENT_CAMERA_H__ */
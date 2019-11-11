#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include <string>
#include <list>

#include "Component.h"
#include "MathGeoLib/include/Geometry/Frustum.h"


class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* target);
	~ComponentCamera();

	void SetCameraFOV(const float& fov);
	void SetCameraNearPlane(const float& near_plane);
	void SetCameraFarPlane(const float& far_plane);

	float GetCameraFOV() const;
	float GetCameraNearPlane() const;
	float GetCameraFarPlane() const;

	float fov = 0.0f;
	float min_fov = 0.0f;
	float max_fov = 0.0f;

	float near_plane = 0.0f;
	float min_near_plane = 0.0f;
	float max_near_plane = 0.0f;

	float far_plane = 0.0f;
	float min_far_plane = 0.0f;
	float max_far_plane = 0.0f;

private:
	Frustum frustum;
	float aspect_ratio = 1.7778f;
};

#endif /* __COMPONENT_CAMERA_H__ */
#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "Component.h"
#include "MathGeoLib\include\Geometry\Frustum.h"
#include "MathGeoLib\include\Geometry\AABB.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* target);
	~ComponentCamera();

	bool Update(float dt);

	void SetCameraFOV(const float& fov);
	void SetCameraNearPlane(const float& near_plane);
	void SetCameraFarPlane(const float& far_plane);
	void SetAspectRatio(const float& a_r);
	void SetCameraSpeed(const float& sp);

	float GetCameraVerticalFOV() const;
	float GetCameraHorizontalFOV() const;
	float GetCameraNearPlane() const;
	float GetCameraFarPlane() const;
	float GetAspectRatio() const;
	float GetCameraSpeed() const;

private:
	//void CalculateViewMatrix();

private:
	Frustum frustum;
	float aspect_ratio = 0.0f;
	mat4x4 ViewMatrix, ViewMatrixInverse;
	float speed = 0.0f;
};

#endif /* __COMPONENT_CAMERA_H__ */
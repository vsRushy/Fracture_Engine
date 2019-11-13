#include "Application.h"
#include "ModuleSceneIntro.h"

#include "Component_Camera.h"

ComponentCamera::ComponentCamera(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::CAMERA;
	frustum.type = PerspectiveFrustum;
	frustum.front = float3(0, 0, 1);
	frustum.up = float3(0, 1, 0);
	frustum.pos = float3(0, 0, 0);
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 500.0f;
	frustum.verticalFov = DEGTORAD * 120.0f;
	frustum.horizontalFov = 0;
	aspect_ratio = 1.5f;
}

ComponentCamera::~ComponentCamera()
{

}

bool ComponentCamera::Update(float dt)
{
	return true;
}

void ComponentCamera::SetCameraFOV(const float& fov)
{
	frustum.verticalFov = DEGTORAD * fov;
	frustum.horizontalFov = 2.0f * atanf(aspect_ratio * tanf(frustum.verticalFov * 0.5f));
}

void ComponentCamera::SetCameraNearPlane(const float& near_plane)
{
	frustum.nearPlaneDistance = near_plane;
}

void ComponentCamera::SetCameraFarPlane(const float& far_plane)
{
	frustum.farPlaneDistance = far_plane;
}

void ComponentCamera::SetAspectRatio(const float& a_r)
{
	aspect_ratio = a_r;
}

void ComponentCamera::SetCameraSpeed(const float& sp)
{
	speed = sp;
}

float ComponentCamera::GetCameraVerticalFOV() const
{
	return RADTODEG * frustum.verticalFov;
}

float ComponentCamera::GetCameraHorizontalFOV() const
{
	return RADTODEG * frustum.horizontalFov;
}

float ComponentCamera::GetCameraNearPlane() const
{
	return frustum.nearPlaneDistance;
}

float ComponentCamera::GetCameraFarPlane() const
{
	return frustum.farPlaneDistance;
}

float ComponentCamera::GetAspectRatio() const
{
	return aspect_ratio;
}

float ComponentCamera::GetCameraSpeed() const
{
	return speed;
}
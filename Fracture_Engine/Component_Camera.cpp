#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Component_Camera.h"

ComponentCamera::ComponentCamera(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::CAMERA;
	frustum.type = math::PerspectiveFrustum;
	frustum.front = math::float3::unitZ;
	frustum.up = math::float3::unitY;
	frustum.pos = math::float3::zero;
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = DEGTORAD * 60;
	frustum.horizontalFov = 2.0f * atanf(aspect_ratio * tanf(frustum.verticalFov * 0.5f));
}

ComponentCamera::~ComponentCamera()
{
	
}

float ComponentCamera::GetCameraFOV() const {

	return RADTODEG * frustum.verticalFov;
}
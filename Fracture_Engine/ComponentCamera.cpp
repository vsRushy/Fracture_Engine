#include "ComponentCamera.h"

#include "GL/glew.h"

ComponentCamera::ComponentCamera(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::CAMERA;

	frustum.pos = float3::zero;
	frustum.up = float3::unitY;
	frustum.front = float3::unitZ;

	aspect_ratio = 1.7f; /* 16/9ar */

	vertical_fov = frustum.verticalFov = 60.0f * DEGTORAD;
	horizontal_fov = frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * aspect_ratio);

	near_plane = frustum.nearPlaneDistance = 0.1f;
	far_plane = frustum.farPlaneDistance = 1000.0f;
}

ComponentCamera::~ComponentCamera()
{

}

bool ComponentCamera::PreUpdate(float dt)
{
	return true;
}

bool ComponentCamera::Update(float dt)
{
	return true;
}

bool ComponentCamera::PostUpdate(float dt)
{
	return true;
}

void ComponentCamera::OnEditor()
{

}

void ComponentCamera::Load(JSON_Object* json_object)
{

}

void ComponentCamera::Save(JSON_Array* json_array) const
{

}

Frustum ComponentCamera::GetFrustrum() const
{
	return frustum;
}

float4x4 ComponentCamera::GetViewMatrix() const
{
	float4x4 fvm = frustum.ViewMatrix();
	return fvm.Transposed();
}

float4x4 ComponentCamera::GetProjectionMatrix() const
{
	return frustum.ProjectionMatrix();
}

void ComponentCamera::SetPosition(const float3& position)
{
	frustum.pos = position;
}

void ComponentCamera::SetFrustumVertices()
{
	float3 vertices[8] = { float3::zero };
	frustum.GetCornerPoints(vertices);

	glBindBuffer(GL_ARRAY_BUFFER, id_f_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertices, GL_DYNAMIC_DRAW);
}

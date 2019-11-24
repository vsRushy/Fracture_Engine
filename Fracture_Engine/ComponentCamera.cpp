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

	/* Set Buffers */

	glGenBuffers(1, (GLuint*) &id_f_vertices);
	glGenBuffers(1, (GLuint*) &id_f_indices);

	uint indices[8 * 4] = {
	0,1, 0,1,  4,5,	0,4,
	3,2, 2,0,  5,1,  1,3,
	7,6, 6,2,  2,3, 3,7,
	6,4, 2,0,  7,5, 3,1
	};
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_f_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 8 * 4, indices, GL_STATIC_DRAW);

	SetFrustumQuad(float3(0, 0, 0), 1, 1, 1);
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

void ComponentCamera::DrawFrustum()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_f_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_f_indices);
	glDrawElements(GL_LINES, 8 * 4, GL_UNSIGNED_INT, NULL);
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

void ComponentCamera::SetFrustumQuad(const float3& position, const float& width, const float& height, const float& depth)
{
	float mid_w = 0.5f * width;
	float mid_h = 0.5f * height;
	float mid_d = 0.5f * depth;

	float vertices[8 * 3] = { -mid_w + position.x, -mid_h + position.y, -mid_d + position.z,
							  -mid_w + position.x, -mid_h + position.y,  mid_d + position.z,
							   mid_w + position.x, -mid_h + position.y,  mid_d + position.z,
							   mid_w + position.x, -mid_h + position.y, -mid_d + position.z,
							  -mid_w + position.x,  mid_h + position.y, -mid_d + position.z,
							  -mid_w + position.x,  mid_h + position.y,  mid_d + position.z,
							   mid_w + position.x,  mid_h + position.y,  mid_d + position.z,
							   mid_w + position.x,  mid_h + position.y, -mid_d + position.z
	};

	glBindBuffer(GL_ARRAY_BUFFER, id_f_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertices, GL_DYNAMIC_DRAW);
}

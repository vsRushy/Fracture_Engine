#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ImGui\imgui.h"

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

void ComponentCamera::Draw()
{

	if (ImGui::CollapsingHeader("Component camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		float h_fov = GetCameraHorizontalFOV();
		ImGui::Text("Horizontal camera FOV:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.7f, 0.8f, 0.0f, 1.0f), "%f", h_fov);
		ImGui::Text("Camera FOV");
		ImGui::SameLine();
		if (ImGui::DragFloat("fov", &h_fov, 1.0f))
			SetCameraFOV(h_fov);

		float v_fov = GetCameraVerticalFOV();
		ImGui::Text("Vertical camera FOV:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.7f, 0.8f, 0.0f, 1.0f), "%f", v_fov);
		ImGui::Text("Camera FOV");
		ImGui::SameLine();
		if (ImGui::DragFloat("fov", &v_fov, 1.0f))
			SetCameraFOV(v_fov);


		float near_plane = GetCameraNearPlane();
		ImGui::Text("Camera Near Plane:");
		ImGui::SameLine();
		if (ImGui::DragFloat("near", &near_plane, 1.0F))
		{
			SetCameraNearPlane(near_plane);
		}


		float far_plane = GetCameraFarPlane();
		ImGui::Text("Camera Far Plane:");
		ImGui::SameLine();
		if (ImGui::DragFloat("far", &far_plane, 1.0F))
		{
			SetCameraFarPlane(far_plane);
		}

	}
}
#ifndef __MODULE_CAMERA_3D_H__
#define __MODULE_CAMERA_3D_H__

#include "JSON/parson.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ConfigurationTool;
class GameObject;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadConfiguration(ConfigurationTool* configuration) override;
	void SaveConfiguration(ConfigurationTool* configuration) override;

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

	// ----------------

	void SetCameraSpeed(const float& speed);
	void SetMaxCameraSpeed(const float& max_speed);
	void SetMinCameraSpeed(const float& min_speed);

	void SetCameraFOV(const float& fov);
	void SetMinCameraFOV(const float& min_fov);
	void SetMaxCameraFOV(const float& max_fov);

	void SetCameraNearPlane(const float& near_plane);
	void SetMinCameraNearPlane(const float& min_near_plane);
	void SetMaxCameraNearPlane(const float& max_near_plane);

	void SetCameraFarPlane(const float& far_plane);
	void SetMinCameraFarPlane(const float& min_far_plane);
	void SetMaxCameraFarPlane(const float& max_far_plane);

	float GetCameraSpeed() const;
	float GetMinCameraSpeed() const;
	float GetMaxCameraSpeed() const;

	float GetCameraFOV() const;
	float GetMinCameraFOV() const;
	float GetMaxCameraFOV() const;

	float GetCameraNearPlane() const;
	float GetMinCameraNearPlane() const;
	float GetMaxCameraNearPlane() const;

	float GetCameraFarPlane() const;
	float GetMinCameraFarPlane() const;
	float GetMaxCameraFarPlane() const;

private:
	void CalculateViewMatrix();


public:
	vec3 X, Y, Z, Position, Reference;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;

	float speed = 0.0f;
	float min_speed = 0.0f;
	float max_speed = 0.0f;

	int zoom = 0;

public:
	float fov = 0.0f;
	float min_fov = 0.0f;
	float max_fov = 0.0f;

	float near_plane = 0.0f;
	float min_near_plane = 0.0f;
	float max_near_plane = 0.0f;

	float far_plane = 0.0f;
	float min_far_plane = 0.0f;
	float max_far_plane = 0.0f;
};

#endif /* __MODULE_CAMERA_3D_H__ */
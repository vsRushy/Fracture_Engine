#ifndef __MODULE_CAMERA_3D_H__
#define __MODULE_CAMERA_3D_H__

#include "JSON/parson.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class GameObject;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadConfiguration(JSON_Object* configuration) override;

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

	// ----------------
	void SetCameraSpeed(const float& speed);
	void SetMaxCameraSpeed(const float& max_speed);
	void SetMinCameraSpeed(const float& min_speed);

	float GetCameraSpeed() const;
	float GetMaxCameraSpeed() const;
	float GetMinCameraSpeed() const;

private:
	void CalculateViewMatrix();


public:
	vec3 X, Y, Z, Position, Reference;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;

	float speed = 0.0f;
	float max_speed = 0.0f;
	float min_speed = 0.0f;
	int zoom = 0;

	GameObject* object_selected = nullptr;
};

#endif /* __MODULE_CAMERA_3D_H__ */
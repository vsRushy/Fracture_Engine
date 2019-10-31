#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Component_Transform.h"
ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG(LOG_INFORMATION, "Setting up the camera");
	bool ret = true;

	/* Settings */
	SetCameraSpeed(speed);
	SetMaxCameraSpeed(max_speed);
	SetMinCameraSpeed(min_speed);
	SetCameraFOV(fov);
	SetCameraNearPlane(near_plane);
	SetCameraFarPlane(far_plane);

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG(LOG_INFORMATION, "Cleaning camera");

	return true;
}

void ModuleCamera3D::LoadConfiguration(JSON_Object* configuration)
{
	speed = (float)json_object_dotget_number(configuration, "Engine.Camera.Speed");
	max_speed = (float)json_object_dotget_number(configuration, "Engine.Camera.Max_speed");
	min_speed = (float)json_object_dotget_number(configuration, "Engine.Camera.Min_speed");
	fov = (float)json_object_dotget_number(configuration, "Engine.Camera.FOV");
	near_plane = (float)json_object_dotget_number(configuration, "Engine.Camera.Near_plane");
	far_plane = (float)json_object_dotget_number(configuration, "Engine.Camera.Far_plane");
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!


	vec3 newPos(0, 0, 0);
	vec3 pointPos(0, 0, 0);
	vec3 reset(0, 0, 0);
	float cam_speed = speed * dt;
	float Sensitivity = 0.25f;
	float zoom_Sensitivity = 5.0f;
	bool scrollUp = false, scrollDown = false;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		cam_speed *= 2.0f;

	if (App->input->GetMouseZ() > 0)
	{
		newPos -= Z * cam_speed * zoom_Sensitivity;
		if (zoom > 0) --zoom;
		else pointPos -= Z * cam_speed * zoom_Sensitivity;		
	}

	if (App->input->GetMouseZ() < 0)
	{
		newPos += Z * cam_speed * zoom_Sensitivity;
		//pointPos += Z * cam_speed * zoom_Sensitivity;
		++zoom;
	}

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN)
	{

		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}

			Position = Reference + Z * length(Position);
		}
	}
	else
	{
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				newPos -= Z * cam_speed;
				pointPos -= Z * cam_speed;
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				newPos += Z * cam_speed;
				pointPos += Z * cam_speed;
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				newPos -= X * cam_speed;
				pointPos -= X * cam_speed;
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				newPos += X * cam_speed;
				pointPos += X * cam_speed;
			}

			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			newPos -=  Y * (float)dy * Sensitivity * cam_speed;
			newPos +=  X * (float)dx * Sensitivity * cam_speed;
			pointPos -= Y * (float)dy * Sensitivity * cam_speed;
			pointPos += X * (float)dx * Sensitivity * cam_speed;
		}
	}

	Position += newPos;
	Reference += pointPos;
	
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		GameObject* object_selected = App->scene_intro->selected_game_object;
		if (object_selected != nullptr)
		{
			if (zoom != 0)
			{
				while(zoom != 0)
				{
					newPos -= Z * cam_speed * zoom_Sensitivity;
					--zoom;
				}
				Position += newPos;
				CalculateViewMatrix();
			}
			float3 pos = object_selected->component_transform->GetPosition();
			LookAt(vec3(pos.x, pos.y, pos.z));
		}
	}


	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

void ModuleCamera3D::SetCameraSpeed(const float& speed)
{
	this->speed = speed;
}

void ModuleCamera3D::SetMaxCameraSpeed(const float& max_speed)
{
	this->max_speed = max_speed;
}

void ModuleCamera3D::SetMinCameraSpeed(const float& min_speed)
{
	this->min_speed = min_speed;
}

void ModuleCamera3D::SetCameraFOV(const float& fov)
{
	this->fov = fov;
}

void ModuleCamera3D::SetCameraNearPlane(const float& near_plane)
{
	this->near_plane = near_plane;
}

void ModuleCamera3D::SetCameraFarPlane(const float& far_plane)
{
	this->far_plane = far_plane;
}

float ModuleCamera3D::GetCameraSpeed() const
{
	return speed;
}

float ModuleCamera3D::GetMaxCameraSpeed() const
{
	return max_speed;
}

float ModuleCamera3D::GetMinCameraSpeed() const
{
	return min_speed;
}

float ModuleCamera3D::GetCameraFOV() const
{
	return fov;
}

float ModuleCamera3D::GetCameraNearPlane() const
{
	return near_plane;
}

float ModuleCamera3D::GetCameraFarPlane() const
{
	return far_plane;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}
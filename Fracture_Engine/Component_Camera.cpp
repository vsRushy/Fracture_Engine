#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Component_Camera.h"

ComponentCamera::ComponentCamera(GameObject* target) : Component(target)
{
	type = COMPONENT_TYPE::CAMERA;
}

ComponentCamera::~ComponentCamera()
{
	
}


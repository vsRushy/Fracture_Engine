#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include <string>
#include <list>

#include "Component.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* target);
	~ComponentCamera();

};

#endif /* __COMPONENT_CAMERA_H__ */
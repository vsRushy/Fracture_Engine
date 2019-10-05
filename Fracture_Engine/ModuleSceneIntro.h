#ifndef __MODULE_SCENE_INTRO_H__
#define __MODULE_SCENE_INTRO_H__

#include <list>

#include "glmath.h"

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreatePrimitive(const vec3& pos, PRIMITIVE_TYPE type);

public:
	std::list<Primitive*> primitives;
};

#endif /* __MODULE_SCENE_INTRO_H__ */
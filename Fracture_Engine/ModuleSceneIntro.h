#ifndef __MODULE_SCENE_INTRO_H__
#define __MODULE_SCENE_INTRO_H__

#include <list>
#include <map>

#include "glmath.h"

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class Mesh;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void DrawGrid(int subdivisions);

	void CreatePrimitive(const vec3& pos, PRIMITIVE_TYPE type);

public:
	std::list<Primitive*> primitives;
	std::list<Mesh*> meshes;
	std::map<const char*, uint> textures;

private:
	uint texture_01_id = -1;
};

#endif /* __MODULE_SCENE_INTRO_H__ */
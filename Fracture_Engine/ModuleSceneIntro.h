#ifndef __MODULE_SCENE_INTRO_H__
#define __MODULE_SCENE_INTRO_H__

#include <list>
#include <map>
#include <string>

#include "glmath.h"

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class GameObject;
class Mesh;
class Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void DrawGrid(int subdivisions);

	// ---------------------------------------------------------------------------

	void CreatePrimitive(const vec3& pos, PRIMITIVE_TYPE type);

	GameObject* CreateEmptyGameObject(std::string name, GameObject* parent = nullptr);
	GameObject* CreateModelGameObject(std::string name, const std::list<Mesh*>& meshes, GameObject* parent = nullptr);

public:
	std::list<GameObject*> game_objects;

	std::list<Primitive*> primitives;
	std::list<Mesh*> meshes;
	std::map<const char*, Texture*> textures;
};

#endif /* __MODULE_SCENE_INTRO_H__ */
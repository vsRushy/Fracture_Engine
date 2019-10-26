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
	GameObject* CreatePrimitive(std::string name, PRIMITIVE_TYPE type, GameObject* parent = nullptr);

	// ------------------------------------------------------------------------

	void ChangeNameIfGameObjectNameAlreadyExists(const std::string& name);

	Texture* GetTextureByName(const std::string& name);
	bool TextureAlreadyExists(const std::string& name);

public:
	std::list<GameObject*> game_objects;

	GameObject* root_game_object = nullptr;

	GameObject* selected_game_object = nullptr;

	std::list<Primitive*> primitives;

	std::map<std::string, Texture*> textures;
	Texture* checkered_texture = nullptr;
};

#endif /* __MODULE_SCENE_INTRO_H__ */
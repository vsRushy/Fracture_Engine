#include "Texture.h"

#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Component_Material.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::ApplyTextureToSelectedGameObject(Texture* texture)
{
	if (texture != nullptr)
	{
		if (App->scene_intro->selected_game_object != nullptr &&
			App->scene_intro->selected_game_object->GetComponentMaterial() != nullptr)
		{
			App->scene_intro->selected_game_object->GetComponentMaterial()->texture = texture;
		}
	}
}

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

Texture* Texture::LoadTexture(const char* path)
{
	Texture* texture = nullptr;

	if (App->scene_intro->TextureAlreadyExists(path))
	{
		texture = App->scene_intro->GetTextureByName(path);
		LOG(LOG_INFORMATION, "Texture with path %s already exists!", path);
	}
	else
	{
		/* We cannot use ilSave(..) to save an already .DDS texture. Therefore, we copy it to our Library folder */
		std::string tex_ext = App->file_system->GetFileExtensionFromPath(path);
		if (tex_ext.compare(".dds") == 0 || tex_ext.compare(".DDS") == 0)
		{
			App->file_system->Copy(path, std::string(LIBRARY_TEXTURE_PATH + App->file_system->GetFileNameFromPath(path) + tex_ext).c_str());
		}

		ILuint devil_id = 0;
		ilGenImages(1, &devil_id);
		ilBindImage(devil_id);

		LOG(LOG_INFORMATION, "Loading texture with path %s", path);
		if ((bool)ilLoadImage(path))
		{
			ILinfo img_info;
			iluGetImageInfo(&img_info);


			/* Save own texture (as .DDS) */
			ILuint size;
			ILubyte* data;
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
			size = ilSaveL(IL_DDS, NULL, 0);
			if (size > 0)
			{
				data = new ILubyte[size];
				if (ilSaveL(IL_DDS, data, size) > 0)
				{
					std::string tex_o;
					std::string text_name = App->file_system->GetFileNameFromPath(path);
					App->file_system->SaveUnique(tex_o, data, size, LIBRARY_TEXTURE_PATH, text_name.c_str(), "dds");
				}

				RELEASE_ARRAY(data);
			}


			iluFlipImage();

			texture = new Texture();

			if (ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE))
			{
				texture->data = (GLubyte*)ilGetData();
				texture->width = ilGetInteger(IL_IMAGE_WIDTH);
				texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
				texture->name = App->file_system->GetFileNameFromPath(path);
				texture->extension = App->file_system->GetFileExtensionFromPath(path);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glGenTextures(1, &texture->id);
				glBindTexture(GL_TEXTURE_2D, texture->id);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), texture->width, texture->height,
					0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, texture->data);
			}
			else
				LOG(LOG_ERROR, "Image could not be converted. Error code: %s", iluErrorString(ilGetError()));

			App->scene_intro->textures.insert({ texture->name + texture->extension, texture });
		}
		else
		{
			LOG(LOG_ERROR, "Error loading the texture %s. Error code: %s", path, iluErrorString(ilGetError()));
		}

		ilDeleteImages(1, &devil_id);


		std::string t_name_ext = std::string(App->file_system->GetFileNameFromPath(path) + ".dds");
		texture->texture_path.assign(std::string(LIBRARY_TEXTURE_PATH).append(t_name_ext));
		App->scene_intro->own_textures.insert(std::make_pair(t_name_ext, texture));
	}

	return texture;
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

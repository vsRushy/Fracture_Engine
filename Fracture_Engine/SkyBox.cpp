#include "SkyBox.h"

#include "GL/glew.h"

#include "Texture.h"

#include "Application.h"
#include "ModuleImporter.h"

SkyBox::SkyBox()
{

}

SkyBox::~SkyBox()
{

}

bool SkyBox::GenerateCubeMap(std::vector<std::string> textures)
{
	this->textures = textures;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (uint i = 0; i < this->textures.size(); i++)
	{
		Texture* tex = App->scene_intro->own_textures[this->textures[i]];
		
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data
		);
	}

	return true;
}

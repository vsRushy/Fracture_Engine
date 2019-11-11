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

bool SkyBox::GenerateCubeMap(std::vector<Texture*> textures)
{
	this->textures = textures;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	unsigned char* data;
	for (uint i = 0; i < this->textures.size(); i++)
	{
		Texture* tex = Texture::LoadTexture(this->textures[i]->name.c_str());
		
		/*data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);*/
	}

	return true;
}

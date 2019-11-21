#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include "GL/glew.h"

#include "Globals.h"

class Texture
{
public:
	Texture();
	~Texture();

	static Texture* LoadTexture(const char* path);
	static void ApplyTextureToSelectedGameObject(Texture* texture);

public:
	std::string name;
	std::string extension;
	std::string texture_path;
	uint id = -1;
	uint width = -1;
	uint height = -1;
	GLubyte* data = nullptr;
};

#endif /* __TEXTURE_H__ */
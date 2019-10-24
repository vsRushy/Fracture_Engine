#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include "GL/glew.h"

#include "Globals.h"

class Texture
{
public:
	Texture() {}
	Texture(const std::string& name, const uint& id, const uint& width, const uint& height);
	~Texture();

public:
	std::string name;
	uint id = -1;
	uint width = -1;
	uint height = -1;
	GLubyte* data = nullptr;
};

#endif /* __TEXTURE_H__ */
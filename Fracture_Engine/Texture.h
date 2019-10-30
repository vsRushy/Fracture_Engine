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

public:
	std::string name;
	std::string extension;
	uint id = -1;
	uint width = -1;
	uint height = -1;
	GLubyte* data = nullptr;
};

#endif /* __TEXTURE_H__ */
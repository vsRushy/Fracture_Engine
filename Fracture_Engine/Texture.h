#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Globals.h"

class Texture
{
public:
	Texture() {}
	Texture(const char* name, const uint& id, const uint& width, const uint& height);
	~Texture();

public:
	const char* name = nullptr;
	uint id = -1;
	uint width = -1;
	uint height = -1;
};

#endif /* __TEXTURE_H__ */
#ifndef __SKY_BOX_H__
#define __SKY_BOX_H__

#include <vector>

#include "Globals.h"

class Texture;

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	bool GenerateCubeMap(std::vector<Texture*> textures);

public:
	uint texture_id = -1;
	std::vector<Texture*> textures;
};

#endif /* __SKY_BOX_H__ */
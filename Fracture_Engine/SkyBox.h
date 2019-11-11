#ifndef __SKY_BOX_H__
#define __SKY_BOX_H__

#include <vector>
#include <string>

#include "Globals.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	bool GenerateCubeMap(std::vector<std::string> textures);

public:
	uint texture_id = -1;
	std::vector<std::string> textures;
};

#endif /* __SKY_BOX_H__ */
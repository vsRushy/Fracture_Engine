#ifndef __SCENE_SERIALIZER_H__
#define __SCENE_SERIALIZER_H__

#include "JSON/parson.h"

class SceneSerializer
{
public:
	SceneSerializer();
	~SceneSerializer();

public:
	void LoadScene(const char* scene_name);
	void SaveScene(const char* scene_name) const;
};

#define /* __SCENE_SERIALIZER_H__ */
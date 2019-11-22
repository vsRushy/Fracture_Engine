#include "SceneSerializer.h"

#include "Globals.h"

SceneSerializer::SceneSerializer()
{

}

SceneSerializer::~SceneSerializer()
{

}

void SceneSerializer::LoadScene(const char* scene_name)
{

}

void SceneSerializer::SaveScene(const char* scene_name) const
{
	LOG(LOG_INFORMATION, "Saving scene at %s.", scene_name)
}

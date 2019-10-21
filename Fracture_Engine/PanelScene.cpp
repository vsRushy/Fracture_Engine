#include "PanelScene.h"

PanelScene::PanelScene(std::string name) : Panel(name)
{
	size.xy = 0.0f;
}

PanelScene::~PanelScene()
{

}

bool PanelScene::Update()
{
	return true;
}

ImVec2 PanelScene::GetSize() const
{
	return size;
}

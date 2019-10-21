#include "PanelScene.h"

PanelScene::PanelScene(std::string name) : Panel(name)
{

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

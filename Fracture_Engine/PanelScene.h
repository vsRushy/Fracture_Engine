#ifndef __PANEL_SCENE_H__
#define __PANEL_SCENE_H__

#include "Panel.h"

class PanelScene : public Panel
{
public:
	PanelScene(std::string name, bool active = true);
	~PanelScene();

	bool Update() override;

	ImVec2 GetSize() const;

private:
	ImVec2 size { 0.0f, 0.0f };
};

#endif /* __PANEL_SCENE_H__ */
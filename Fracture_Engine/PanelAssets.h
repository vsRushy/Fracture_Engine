#ifndef __PANEL_ASSETS_H__
#define __PANEL_ASSETS_H__

#include "Panel.h"

class PanelAssets : public Panel
{
public:
	PanelAssets(std::string name, bool active = true);
	~PanelAssets();

	bool Update() override;
};

#endif /* __PANEL_ASSETS_H__ */ 
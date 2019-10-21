#ifndef __PANEL_MAIN_MENU_BAR_H__
#define __PANEL_MAIN_MENU_BAR_H__

#include "Panel.h"

class PanelMainMenuBar : public Panel
{
public:
	PanelMainMenuBar(std::string name);
	~PanelMainMenuBar();

	bool Update() override;
};

#endif /* __PANEL_MAIN_MENU_BAR_H__ */
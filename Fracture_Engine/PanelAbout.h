#ifndef __PANEL_ABOUT_H__
#define __PANEL_ABOUT_H__

#include "Panel.h"

class PanelAbout : public Panel
{
public:
	PanelAbout(std::string name, bool active = true);
	~PanelAbout();

	bool Update() override;
};

#endif /* __PANEL_ABOUT_H__ */
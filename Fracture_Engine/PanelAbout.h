#ifndef __PANEL_ABOUT_H__
#define __PANEL_ABOUT_H__

#include "Panel.h"
#include "PhysFS/include/physfs.h"

class PanelAbout : public Panel
{
public:
	PanelAbout(std::string name, bool active = true);
	~PanelAbout();

	bool Update() override;
	PHYSFS_Version compiled;
	PHYSFS_Version linked;
};

#endif /* __PANEL_ABOUT_H__ */
#ifndef __PANEL_HIERARCHY_H__
#define __PANEL_HIERARCHY_H__

#include "Panel.h"

class PanelHierarchy : public Panel
{
public:
	PanelHierarchy(std::string name, bool active = true);
	~PanelHierarchy();

	bool Update() override;
};

#endif /* __PANEL_HIERARCHY_H__ */
#ifndef __PANEL_INSPECTOR_H__
#define __PANEL_INSPECTOR_H__

#include "Panel.h"

class PanelInspector : public Panel
{
public:
	PanelInspector(std::string name, bool active = true);
	~PanelInspector();

	bool Update() override;
};

#endif /* __PANEL_INSPECTOR_H__ */
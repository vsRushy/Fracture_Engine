#ifndef __PANEL_CONFIGURATION_H__
#define __PANEL_CONFIGURATION_H__

#include "Panel.h"

class PanelConfiguration : public Panel
{
public:
	PanelConfiguration(std::string name, bool active = true);
	~PanelConfiguration();

	bool Update() override;
};

#endif /* __PANEL_CONFIGURATION_H__ */
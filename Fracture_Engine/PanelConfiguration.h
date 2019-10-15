#ifndef __MODULE_PANEL_CONFIGURATION_H__
#define __MODULE_PANEL_CONFIGURATION_H__

#include <list>

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"

class PanelConfiguration : public Module
{
public:
	PanelConfiguration(bool start_enabled = true);
	~PanelConfiguration();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
};

#endif /* __MODULE_PANEL_CONFIGURATION_H__ */
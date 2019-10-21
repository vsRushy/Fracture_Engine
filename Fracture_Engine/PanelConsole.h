#ifndef __PANEL_CONSOLE_H__
#define __PANEL_CONSOLE_H__

#include <list>

#include "Panel.h"

#include "Globals.h"

class PanelConsole : public Panel
{
public:
	PanelConsole(std::string name, bool active = true);
	~PanelConsole();

	bool Update() override;
	bool CleanUp() override;

	void Log(LOG_TYPE type, const char* text_log) override;

public:
	std::list<std::pair<LOG_TYPE, const char*>> console_logs;
	bool scroll_down_console = false;
};

#endif /* __PANEL_CONSOLE_H__ */
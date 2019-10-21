#ifndef __PANEL_H__
#define __PANEL_H__

#include <string>

#include "ImGui/imgui.h"

#include "Globals.h"

class Panel
{
public:
	Panel(std::string name, bool active = true);
	~Panel();

	virtual bool Start();
	virtual bool Update();
	virtual bool CleanUp();

	bool IsActive() const;
	void SetActive(const bool& value);
	void ChangeActive();

	std::string GetName() const;

public:
	int position_x = 0;
	int position_y = 0;
	int width = 0;
	int height = 0;
	
protected:
	std::string name;

public:
	bool active = true;

	/* To access from base class pointers */
public:
	virtual void Log(LOG_TYPE type, const char* text_log) {}; // Override in PanelConsole
};

#endif /* __PANEL_H__ */
#ifndef __PANEL_LIBRARY_H__
#define __PANEL_LIBRARY_H__

#include "Panel.h"

class PanelLibrary : public Panel
{
public:
	PanelLibrary(std::string name, bool active = true);
	~PanelLibrary();

	bool Update() override;
};

#endif /* __PANEL_LIBRARY_H__ */
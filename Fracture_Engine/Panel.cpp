#include "Panel.h"

#include "Application.h"
#include "ModuleUserInterface.h"

Panel::Panel(std::string name, bool active) : name(name), active(active)
{

}

Panel::~Panel()
{
	delete this; // edgy
}

bool Panel::Start()
{
	return true;
}

bool Panel::Update()
{
	return true;
}

bool Panel::CleanUp()
{
	return true;
}

bool Panel::IsActive() const
{
	return active;
}

void Panel::SetActive(const bool& value)
{
	active = value;
}

void Panel::ChangeActive()
{
	active = !active;
}

std::string Panel::GetName() const
{
	return name;
}

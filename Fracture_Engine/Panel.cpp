#include "Panel.h"

#include "Application.h"
#include "ModuleUserInterface.h"

Panel::Panel(std::string name) : name(name)
{

}

Panel::~Panel()
{

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

std::string Panel::GetName() const
{
	return name;
}

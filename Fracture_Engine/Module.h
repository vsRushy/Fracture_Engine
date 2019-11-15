#ifndef __MODULE_H__
#define __MODULE_H__

#include "JSON/parson.h"

class Application;
class ConfigurationTool;

class Module
{
private :
	bool enabled;
	const char* name;

public:
	Module(bool start_enabled = true) : enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void LoadConfiguration(ConfigurationTool* configuration)
	{

	}

	virtual void SaveConfiguration(ConfigurationTool* configuration)
	{

	}

	bool IsEnabled() const { return enabled; }

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	const char* GetName() const
	{
		return name;
	}

	void SetName(const char* name)
	{
		this->name = name;
	}
};

#endif /* __MODULE_H__ */
#ifndef __PANEL_H__
#define __PANEL_H__

#include <string>

class Panel
{
public:
	Panel(std::string name);
	~Panel();

	virtual bool Update();

	bool IsActive() const;
	void SetActive(const bool& value);

	std::string GetName() const;

public:
	int position_x = 0;
	int position_y = 0;
	int width = 0;
	int height = 0;
	
protected:
	std::string name;

private:
	bool active = true;
};

#endif /* __PANEL_H__ */
#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:
	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

public:
	void SetTitle(const char* title);
	void SetWindowBrightness(const float& brightness) const;
	void SetWindowSize(const int& size);
	void SetWindowWidth(const int& width);
	void SetWindowHeight(const int& height);
	void SetWindowFullscreen(const bool& value);
	void SetWindowResizable(const bool& value);
	void SetWindowBorderless(const bool& value);
	void SetWindowFullScreenDesktop(const bool& value);
	void SetScreenMaxWidth(const int& max_width);
	void SetScreenMaxHeight(const int& max_height);
	void SetScreenMinWidth(const int& min_width);
	void SetScreenMinHeight(const int& min_height);

	const char* GetTitle() const;
	float GetWindowBrightness() const;
	int GetWindowSize() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	bool GetWindowFullscreen() const;
	bool GetWindowResizable() const;
	bool GetWindowBorderless() const;
	bool GetWindowFullScreenDesktop() const;
	int GetScreenMaxWidth() const;
	int GetScreenMaxHeight() const;
	int GetScreenMinWidth() const;
	int GetScreenMinHeight() const;

	void UpdateWindowSize() const;

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

private:
	const char* window_title;
	int window_size;
	int window_width;
	int window_height;
	bool window_fullscreen;
	bool window_resizable;
	bool window_borderless;
	bool window_fullscreen_desktop;
	int screen_max_width;
	int screen_max_height;
	int screen_min_width;
	int screen_min_height;
};

#endif /* __MODULE_WINDOW_H__ */
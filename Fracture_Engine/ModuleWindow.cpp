#include "JSON/parson.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ConfigurationTool.h"

ModuleWindow::ModuleWindow(bool start_enabled) : Module(start_enabled)
{
	SetName("Window");

	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG(LOG_INFORMATION, "Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG(LOG_ERROR, "SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window and window configuration
		SetTitle(App->GetAppName());
		SetWindowSize(window_size);
		SetWindowWidth(window_width);
		SetWindowHeight(window_height);
		SetWindowFullscreen(window_fullscreen);
		SetWindowResizable(window_resizable);
		SetWindowBorderless(window_borderless);
		SetWindowFullScreenDesktop(window_fullscreen_desktop);
		SetScreenMaxWidth(screen_max_width);
		SetScreenMaxHeight(screen_max_height);
		SetScreenMinWidth(screen_min_width);
		SetScreenMinHeight(screen_min_height);

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 3.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(GetWindowFullscreen())
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(GetWindowResizable() == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(GetWindowBorderless() == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(GetWindowFullScreenDesktop() == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(GetTitle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			GetWindowWidth(), GetWindowHeight(), flags);

		if(window == NULL)
		{
			LOG(LOG_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG(LOG_INFORMATION, "Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();

	return true;
}

void ModuleWindow::LoadConfiguration(ConfigurationTool* configuration)
{
	window_size = configuration->GetInt("Size");
	window_width = configuration->GetInt("Width");
	window_height = configuration->GetInt("Height");
	window_fullscreen = configuration->GetBool("Fullscreen");
	window_resizable = configuration->GetBool("Resizable");
	window_borderless = configuration->GetBool("Borderless");
	window_fullscreen_desktop = configuration->GetBool("Fullscreen_desktop");
	screen_max_width = configuration->GetInt("Max_width");
	screen_max_height = configuration->GetInt("Max_height");
	screen_min_width = configuration->GetInt("Min_width");
	screen_min_height = configuration->GetInt("Min_height");
}

void ModuleWindow::SaveConfiguration(ConfigurationTool* configuration)
{

}

void ModuleWindow::SetTitle(const char* title)
{
	window_title = title;
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetWindowBrightness(const float& brightness) const
{
	SDL_SetWindowBrightness(window, brightness);
}

void ModuleWindow::SetWindowSize(const int& size)
{
	window_size = size;
}

void ModuleWindow::SetWindowWidth(const int& width)
{
	window_width = width * GetWindowSize();
	UpdateWindowSize();
}

void ModuleWindow::SetWindowHeight(const int& height)
{
	window_height = height * GetWindowSize();
	UpdateWindowSize();
}

void ModuleWindow::SetWindowFullscreen(const bool& value)
{
	window_fullscreen = value;
	if (value)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetWindowResizable(const bool& value)
{
	window_resizable = value;
	if (value)
		SDL_SetWindowResizable(window, SDL_TRUE);
	else
		SDL_SetWindowResizable(window, SDL_FALSE);
}

void ModuleWindow::SetWindowBorderless(const bool& value)
{
	window_borderless = value;
	if (value)
		SDL_SetWindowBordered(window, SDL_FALSE);
	else
		SDL_SetWindowBordered(window, SDL_TRUE);
}

void ModuleWindow::SetWindowFullScreenDesktop(const bool& value)
{
	window_fullscreen_desktop = value;
	if (value)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetScreenMaxWidth(const int& max_width)
{
	screen_max_width = max_width;
}

void ModuleWindow::SetScreenMaxHeight(const int& max_height)
{
	screen_max_height = max_height;
}

void ModuleWindow::SetScreenMinWidth(const int& min_width)
{
	screen_min_width = min_width;
}

void ModuleWindow::SetScreenMinHeight(const int& min_height)
{
	screen_min_height = min_height;
}

const char* ModuleWindow::GetTitle() const
{
	return window_title;
}

float ModuleWindow::GetWindowBrightness() const
{
	return SDL_GetWindowBrightness(window);
}

int ModuleWindow::GetWindowSize() const
{
	return window_size;
}

int ModuleWindow::GetWindowWidth() const
{
	return window_width;
}

int ModuleWindow::GetWindowHeight() const
{
	return window_height;
}

bool ModuleWindow::GetWindowFullscreen() const
{
	return window_fullscreen;
}

bool ModuleWindow::GetWindowResizable() const
{
	return window_resizable;
}

bool ModuleWindow::GetWindowBorderless() const
{
	return window_borderless;
}

bool ModuleWindow::GetWindowFullScreenDesktop() const
{
	return window_fullscreen_desktop;
}

int ModuleWindow::GetScreenMaxWidth() const
{
	return screen_max_width;
}

int ModuleWindow::GetScreenMaxHeight() const
{
	return screen_max_height;
}

int ModuleWindow::GetScreenMinWidth() const
{
	return screen_min_width;
}

int ModuleWindow::GetScreenMinHeight() const
{
	return screen_min_height;
}

void ModuleWindow::UpdateWindowSize() const
{
	int w = GetWindowWidth();
	int h = GetWindowHeight();
	SDL_SetWindowSize(window, w, h);
	App->renderer3D->OnResize(w, h);
}

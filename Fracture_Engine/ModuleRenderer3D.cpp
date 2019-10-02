#include <GL/glew.h>

#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

#pragma comment (lib, "glu32.lib")    /* Link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* Link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* Link Glew OpenGL specification */

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) : Module(start_enabled)
{}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG(LOG_INFORMATION, "Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG(LOG_ERROR, "OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// Initialize Glew after OpenGL context is created
	GLenum g_init = glewInit();

	if (g_init != GLEW_OK)
	{
		LOG(LOG_ERROR, "Glew could not be initialized! %s", glewGetErrorString(g_init));
	}
	
	if(ret)
	{
		SetVSync(vsync);

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG(LOG_ERROR, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG(LOG_ERROR, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG(LOG_ERROR, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(App->window->GetWindowWidth(), App->window->GetWindowHeight());

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG(LOG_INFORMATION, "Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRenderer3D::LoadConfiguration(JSON_Object* configuration)
{
	vsync = json_object_dotget_boolean(configuration, "Engine.Renderer.V_sync");
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::SetVSync(const bool& value)
{
	vsync = value;

	if (GetVSync())
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
			LOG(LOG_ERROR, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		if (SDL_GL_SetSwapInterval(0) < 0)
			LOG(LOG_ERROR, "Warning: Unable to unset VSync! SDL Error: %s\n", SDL_GetError());
	}
}

bool ModuleRenderer3D::GetVSync() const
{
	return vsync;
}

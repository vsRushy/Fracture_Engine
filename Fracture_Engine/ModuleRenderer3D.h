#ifndef __MODULE_RENDERER_3D_H__
#define __MODULE_RENDERER_3D_H__

#include "JSON/parson.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "Primitive.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	/* Draw functions ------------------ */
	void DrawPrimitive(Primitive* primitive);

	void LoadConfiguration(JSON_Object* configuration) override;

	void OnResize(int width, int height);

	void SetVSync(const bool& value);
	bool GetVSync() const;

public:
	bool vsync;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};

#endif /* __MODULE_RENDERER_3D_H__ */
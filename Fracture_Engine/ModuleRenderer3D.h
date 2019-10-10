#ifndef __MODULE_RENDERER_3D_H__
#define __MODULE_RENDERER_3D_H__

#include "JSON/parson.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

class Primitive;
class Mesh;

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
	void DrawPrimitive(Primitive* primitive) const;
	void DrawMesh(Mesh* mesh) const;

	void LoadConfiguration(JSON_Object* configuration) override;

	void OnResize(int width, int height);

	void SetVSync(const bool& value);
	void SetWireframeMode(const bool& value);
	void SetDepthTest(const bool& value);
	void SetCullFace(const bool& value);
	void SetLighting(const bool& value);
	void SetColorMaterial(const bool& value);
	void SetTexture2D(const bool& value);
	void SetBlend(const bool& value);
	void SetFog(const bool& value);
	void SetAlphaTest(const bool& value);

	bool GetVSync() const;
	bool GetWireframeMode() const;
	bool GetDepthTest() const;
	bool GetCullFace() const;
	bool GetLighting() const;
	bool GetColorMaterial() const;
	bool GetTexture2D() const;
	bool GetBlend() const;
	bool GetFog() const;
	bool GetAlphaTest() const;

	// Mesh advanced functions
	void SetDrawMeshLines(const bool& value);
	bool GetDrawMeshLines() const;

public:
	bool vsync;

	bool wireframe_mode;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool gl_depth_test;
	bool gl_cull_face;
	bool gl_lighting;
	bool gl_color_material;
	bool gl_texture_2d;
	bool gl_blend;
	bool gl_fog;
	bool gl_alpha_test;
};

#endif /* __MODULE_RENDERER_3D_H__ */
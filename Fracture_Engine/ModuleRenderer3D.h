#ifndef __MODULE_RENDERER_3D_H__
#define __MODULE_RENDERER_3D_H__

#include "JSON/parson.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "FrameBufferObject.h"

#define MAX_LIGHTS 8

class GameObject;
class Primitive;

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
	void DrawGameObject(GameObject* game_object) const;

	void LoadConfiguration(JSON_Object* configuration) override;

	void OnResize(const int& width, const int& height);

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
	void SetDrawMeshVertices(const bool& value);
	void SetDrawMeshVertexNormals(const bool& value);
	void SetDrawMeshFaceNormals(const bool& value);

	bool GetDrawMeshLines() const;
	bool GetDrawMeshVertices() const;
	bool GetDrawMeshVertexNormals() const;
	bool GetDrawMeshFaceNormals() const;

	void DrawMeshLines(Mesh* mesh, const float& size) const;
	void DrawMeshVertices(Mesh* mesh, const float& size) const;
	void DrawMeshVertexNormals(Mesh* mesh, const float& width) const;
	void DrawMeshFaceNormals(Mesh* mesh, const float& width) const;

public:
	bool vsync;

	bool wireframe_mode;

	FrameBufferObject frame_buffer_object;

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

public:
	/* Mesh advanced options */
	bool draw_mesh_lines = false;
	float mesh_lines_width = 3.0f;

	bool draw_mesh_vertices = false;
	float mesh_vertices_size = 9.0f;

	bool draw_mesh_vertex_normals = false;
	float mesh_vertex_normals_width = 2.0f;

	bool draw_mesh_face_normals = false;
	float mesh_face_normals_width = 2.0f;

	// -----------------------------------------

	Color mesh_lines_color = { 255.0f, 255.0f, 0.0f };
	Color mesh_vertices_color = { 0.0f, 255.0f, 255.0f };
	Color mesh_vertex_normals_color = { 255.0f, 0.0f, 0.0f };
	Color mesh_face_normals_color = { 0.0f, 0.0f, 255.0f };
};

#endif /* __MODULE_RENDERER_3D_H__ */
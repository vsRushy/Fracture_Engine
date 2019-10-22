#include <GL/glew.h>

#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleImporter.h"
#include "Primitive.h"
#include "Mesh.h"

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
		/* Setting vsync */
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
		glClearColor(0.12f, 0.12f, 0.12f, 1.0f);

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
		
		lights[0].Active(true);

		/* Settings */
		SetWireframeMode(wireframe_mode);
		SetDepthTest(gl_depth_test);
		SetCullFace(gl_cull_face);
		SetLighting(gl_lighting);
		SetColorMaterial(gl_color_material);
		SetTexture2D(gl_texture_2d);
		SetBlend(gl_blend);
		SetFog(gl_fog);
		SetAlphaTest(gl_alpha_test);
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

void ModuleRenderer3D::DrawPrimitive(Primitive* primitive) const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, primitive->vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive->ibo_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawElements(GL_TRIANGLES, primitive->shape->ntriangles * 3, GL_UNSIGNED_SHORT, nullptr);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ModuleRenderer3D::DrawMesh(Mesh* mesh) const
{
	if (!GetWireframeMode())
	{
		glEnableClientState(GL_VERTEX_ARRAY);

		if (mesh->id_textures != -1) {
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, mesh->id_textures);

			glBindBuffer(GL_ARRAY_BUFFER, mesh->id_uvs);
			glTexCoordPointer(3, GL_FLOAT, 0, NULL);
		}

		if (mesh->normals != nullptr)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->id_normals);
			glNormalPointer(GL_FLOAT, 0, NULL);
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_indices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		/* Draw */
		glDrawElements(GL_TRIANGLES, mesh->num_indices * 3, GL_UNSIGNED_INT, NULL);

		/* Unbind buffers and texture */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glDisable(GL_TEXTURE_2D);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	/* Draw mesh lines */
	if(draw_mesh_lines || GetWireframeMode())
		DrawMeshLines(mesh, mesh_lines_width);

	/* Draw vertices */
	if(draw_mesh_vertices)
		DrawMeshVertices(mesh, mesh_vertices_size);

	/* Draw vertex normals */
	if(draw_mesh_vertex_normals)
		DrawMeshVertexNormals(mesh, mesh_vertex_normals_width);

	/* Draw face normals */
	if(draw_mesh_face_normals)
		DrawMeshFaceNormals(mesh, mesh_face_normals_width);
}

void ModuleRenderer3D::LoadConfiguration(JSON_Object* configuration)
{
	vsync = json_object_dotget_boolean(configuration, "Engine.Renderer.V_sync");

	wireframe_mode = json_object_dotget_boolean(configuration, "Engine.Renderer.Wireframe_mode");
	
	gl_depth_test = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_depth_test");
	gl_cull_face = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_cull_face");
	gl_lighting = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_lighting");
	gl_color_material = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_color_material");
	gl_texture_2d = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_texture_2d");
	gl_blend = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_blend");
	gl_fog = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_fog");
	gl_alpha_test = json_object_dotget_boolean(configuration, "Engine.Renderer.gl_alpha_test");
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

// ----------------------------------------------------------

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

void ModuleRenderer3D::SetWireframeMode(const bool& value)
{
	wireframe_mode = value;
}

void ModuleRenderer3D::SetDepthTest(const bool& value)
{
	gl_depth_test = value;
	value ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void ModuleRenderer3D::SetCullFace(const bool& value)
{
	gl_cull_face = value;
	value ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void ModuleRenderer3D::SetLighting(const bool& value)
{
	gl_lighting = value;
	value ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
}

void ModuleRenderer3D::SetColorMaterial(const bool& value)
{
	gl_color_material = value;
	value ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
}

void ModuleRenderer3D::SetTexture2D(const bool& value)
{
	gl_texture_2d = value;
	value ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
}

void ModuleRenderer3D::SetBlend(const bool& value)
{
	gl_blend = value;
	value ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

void ModuleRenderer3D::SetFog(const bool& value)
{
	gl_fog = value;
	value ? glEnable(GL_FOG) : glDisable(GL_FOG);
}

void ModuleRenderer3D::SetAlphaTest(const bool& value)
{
	gl_alpha_test = value;
	value ? glEnable(GL_ALPHA_TEST) : glDisable(GL_ALPHA_TEST);
}

// ----------------------------------------------------------

bool ModuleRenderer3D::GetVSync() const
{
	return vsync;
}

bool ModuleRenderer3D::GetWireframeMode() const
{
	return wireframe_mode;
}

bool ModuleRenderer3D::GetDepthTest() const
{
	return gl_depth_test;
}

bool ModuleRenderer3D::GetCullFace() const
{
	return gl_cull_face;
}

bool ModuleRenderer3D::GetLighting() const
{
	return gl_lighting;
}

bool ModuleRenderer3D::GetColorMaterial() const
{
	return gl_color_material;
}

bool ModuleRenderer3D::GetTexture2D() const
{
	return gl_texture_2d;
}

bool ModuleRenderer3D::GetBlend() const
{
	return gl_blend;
}

bool ModuleRenderer3D::GetFog() const
{
	return gl_fog;
}

bool ModuleRenderer3D::GetAlphaTest() const
{
	return gl_alpha_test;
}

// -------------------------------------------------------

void ModuleRenderer3D::SetDrawMeshLines(const bool& value)
{
	draw_mesh_lines = value;
}

void ModuleRenderer3D::SetDrawMeshVertices(const bool& value)
{
	draw_mesh_vertices = value;
}

void ModuleRenderer3D::SetDrawMeshVertexNormals(const bool& value)
{
	draw_mesh_vertex_normals = value;
}

void ModuleRenderer3D::SetDrawMeshFaceNormals(const bool& value)
{
	draw_mesh_face_normals = value;
}

bool ModuleRenderer3D::GetDrawMeshLines() const
{
	return draw_mesh_lines;
}

bool ModuleRenderer3D::GetDrawMeshVertices() const
{
	return draw_mesh_vertices;
}

bool ModuleRenderer3D::GetDrawMeshVertexNormals() const
{
	return draw_mesh_vertex_normals;
}

bool ModuleRenderer3D::GetDrawMeshFaceNormals() const
{
	return draw_mesh_face_normals;
}

// -----------------------

void ModuleRenderer3D::DrawMeshLines(Mesh* mesh, const float& size) const
{
	glColor3f(App->renderer3D->mesh_lines_color.r,
		App->renderer3D->mesh_lines_color.g,
		App->renderer3D->mesh_lines_color.b);

	glEnableClientState(GL_VERTEX_ARRAY);

	glLineWidth(size);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, mesh->num_indices * 3, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glColor3f(255.0f, 255.0f, 255.0f);
}

void ModuleRenderer3D::DrawMeshVertices(Mesh* mesh, const float& size) const
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(App->renderer3D->mesh_vertices_color.r,
		App->renderer3D->mesh_vertices_color.g,
		App->renderer3D->mesh_vertices_color.b);

	for (int i = 0; i < mesh->num_vertices * 3; i += 3)
	{
		glVertex3f(mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2]);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glPointSize(1.0f);
}

void ModuleRenderer3D::DrawMeshVertexNormals(Mesh* mesh, const float& width) const
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(App->renderer3D->mesh_vertex_normals_color.r,
		App->renderer3D->mesh_vertex_normals_color.g,
		App->renderer3D->mesh_vertex_normals_color.b);

	for (int i = 0; i < mesh->num_normals * 3; i += 3)
	{
		vec3 normal_vector = normalize({ mesh->normals[i], mesh->normals[i + 1], mesh->normals[i + 2] });

		glVertex3f(mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2]);
		glVertex3f(mesh->vertices[i] + normal_vector.x, mesh->vertices[i + 1] + normal_vector.y, mesh->vertices[i + 2] + normal_vector.z);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glLineWidth(1.0f);
}

void ModuleRenderer3D::DrawMeshFaceNormals(Mesh* mesh, const float& width) const
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(App->renderer3D->mesh_face_normals_color.r,
		App->renderer3D->mesh_face_normals_color.g,
		App->renderer3D->mesh_face_normals_color.b);

	for (int i = 0; i < mesh->num_indices; i += 3)
	{
		glVertex3f(mesh->center_face_point[i], mesh->center_face_point[i + 1], 
			mesh->center_face_point[i + 2]);
		glVertex3f(mesh->center_face_point[i] + mesh->center_face_normal_point[i],
			mesh->center_face_point[i + 1] + mesh->center_face_normal_point[i + 1], 
			mesh->center_face_point[i + 2] + mesh->center_face_normal_point[i + 2]);
	}

	glColor3f(255.0f, 255.0f, 255.0f);
	glEnd();
	glLineWidth(1.0f);
}
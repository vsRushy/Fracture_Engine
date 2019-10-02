#include "GL/glew.h"

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "MathGeoLib.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG(LOG_INFORMATION, "Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	float cube_vertices_1[] = {
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,

		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,

		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,

		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,

		 1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f
	};


	float cube_vertices_2[] = {
		-1.0f, -1.0f,  1.0f, // index 0
		 1.0f, -1.0f,  1.0f, // index 1
		-1.0f,  1.0f,  1.0f, // index 2
		 1.0f, -1.0f, -1.0f, // index 3
		 1.0f,  1.0f,  1.0f, // index 4
		-1.0f, -1.0f, -1.0f, // index 5
		 1.0f,  1.0f, -1.0f, // index 6
		-1.0f,  1.0f, -1.0f  // index 7
	};

	uint cube_indices[] = {
		0, 1, 2,
		2, 1, 4,

		1, 3, 4,
		4, 3, 6,

		3, 5, 6,
		6, 5, 7,

		5, 0, 7,
		7, 0, 2,

		2, 4, 7,
		7, 4, 6,

		5, 3, 0,
		0, 3, 1
	};

	/* Vertex Buffer Object for cube 1*/
	/*glGenBuffers(1, (GLuint*) &(vbo_id_1));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, cube_vertices_1, GL_STATIC_DRAW);*/


	/* Vertex Buffer Object for cube 2*/
	glGenBuffers(1, (GLuint*) &(vbo_id_2));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, cube_vertices_2, GL_STATIC_DRAW);

	/* Index Buffer Object */
	glGenBuffers(1, (GLuint*) &(ibo_id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 3 * 12, cube_indices, GL_STATIC_DRAW);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG(LOG_INFORMATION, "Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/* Draw cube 1 */
	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);*/

	/* Draw cube 2 */
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);

	glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

	return UPDATE_CONTINUE;
}

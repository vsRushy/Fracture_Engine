#include "GL/glew.h"

#include "P_Cube.h"

P_Cube::P_Cube(const vec3& position) : Primitive(position)
{
	type = PRIMITIVE_TYPE::CUBE;
	shape = par_shapes_create_cube();
	par_shapes_translate(shape, position.x, position.y, position.z);

	/* VBO */
	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * shape->npoints * 3, shape->points, GL_STATIC_DRAW);
	
	/* IBO */
	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * shape->ntriangles * 3, shape->triangles, GL_STATIC_DRAW);
}

P_Cube::~P_Cube()
{

}

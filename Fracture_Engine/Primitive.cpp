#include "Primitive.h"

Primitive::Primitive(const vec3& position)
{
	this->position.Set(position.x, position.y, position.z);
}

Primitive::~Primitive()
{
	par_shapes_free_mesh(shape);
}

vec3 Primitive::GetPosition() const
{
	return position;
}

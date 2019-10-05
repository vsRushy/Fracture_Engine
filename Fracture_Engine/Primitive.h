#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glmath.h"
#include "Par/par_shapes.h"

#include "Globals.h"

enum class PRIMITIVE_TYPE
{
	UNKNOWN = -1,

	CUBE,
	SPHERE,
	PLANE
};

class Primitive
{
public:
	Primitive(const vec3& position);
	virtual ~Primitive();
	
	vec3 GetPosition() const;

public:
	vec3 position;
	par_shapes_mesh* shape = nullptr;
	PRIMITIVE_TYPE type = PRIMITIVE_TYPE::UNKNOWN;

	uint vbo_id;
	uint ibo_id;
};

#endif /* __PRIMITIVE_H__ */
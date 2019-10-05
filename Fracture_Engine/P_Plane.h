#ifndef __P_PLANE_H__
#define __P_PLANE_H__

#include "Primitive.h"

/* TOFIX. don't use par_shapes for plane */
class P_Plane : public Primitive
{
public:
	P_Plane(const vec3& position);
	~P_Plane();
};

#endif /* __P_PLANE_H__ */
#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Primitive.h"

class P_Sphere : public Primitive
{
public:
	P_Sphere(const vec3& position);
	~P_Sphere();
};

#endif /* __SPHERE_H__ */
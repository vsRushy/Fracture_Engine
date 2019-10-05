#ifndef __P_CUBE_H__
#define __P_CUBE_H__

#include "Primitive.h"

class P_Cube : public Primitive
{
public:
	P_Cube(const vec3& position);
	~P_Cube();
};

#endif /* __P_CUBE_H__ */
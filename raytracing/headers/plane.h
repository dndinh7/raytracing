#ifndef PLANE_H
#define PLANE_H

#include "shape.h"
#include "hittable.h"
#include "vec3.h"

class plane : public shape, public hittable {


	private:
		point3 origin;

};


#endif
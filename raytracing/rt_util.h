#ifndef RT_UTIL_H
#define RT_UTIL_H

#include <cmath>
#include <limits>
#include <memory>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// functions
inline double degrees_to_rad(double degrees) {
	return degrees * 180 / pi;
}

// headers
#include "ray.h"
#include "vec3.h"
#include "interval.h"


#endif
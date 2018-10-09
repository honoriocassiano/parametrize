/*
 * Ray.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Ray.h"

namespace param {

Ray::Ray(const Point& _origin, const Vector& _direction) :
		orig(_origin), dir(_direction) {
}

Ray::~Ray() {
}

} /* namespace param */

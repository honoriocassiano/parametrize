/*
 * Ray.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include "Vector.h"

namespace param {

class Ray {
public:
	Ray(const Point& origin, const Vector& direction);
	virtual ~Ray();

private:
	Point orig;
	Vector dir;
};

} /* namespace param */

#endif /* RAY_H_ */

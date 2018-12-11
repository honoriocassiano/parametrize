/*
 * Raycaster2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef RAYCASTER2_H_
#define RAYCASTER2_H_

#include <cmath>
#include <vector>

#include "utils.h"

namespace param {
struct Polygon;
class Ray2;
} /* namespace param */

namespace param {

class Raycaster2 {
public:
	Raycaster2();
	virtual ~Raycaster2();

	std::vector<CastEl> Cast(const Ray2& ray, Polygon* mesh,
			float maxDistanceFront = INFINITY,
			float maxDistanceBack = -INFINITY);
};
} /* namespace param */

#endif /* RAYCASTER2_H_ */

/*
 * Raycaster.h
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "Ray.h"
#include "Triangle.h"

#include <vector>

namespace param {

struct CastEl {
	float distance;
	bool in;
};

struct {
	bool operator()(const CastEl& c1, const CastEl& c2) {
		return c1.distance <= c2.distance;
	}
} castElComp;

class Raycaster {
public:
	Raycaster();
	virtual ~Raycaster();

	std::vector<CastEl> Cast(const Ray& ray,
			const std::vector<Triangle*>& triangles);
};

} /* namespace param */

#endif /* RAYCASTER_H_ */

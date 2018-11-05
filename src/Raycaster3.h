/*
 * Raycaster.h
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#ifndef RAYCASTER3_H_
#define RAYCASTER3_H_

#include "Triangle.h"

#include <vector>
#include "Ray3.h"

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

class Raycaster3 {
public:
	Raycaster3();
	virtual ~Raycaster3();

	std::vector<CastEl> Cast(const Ray3& ray,
			const std::vector<Triangle*>& triangles);
};

} /* namespace param */

#endif /* RAYCASTER3_H_ */

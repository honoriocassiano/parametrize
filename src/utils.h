/*
 * utils.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "defaults.h"

#include <math.h>
#include <glm/vec2.hpp>

namespace param {

struct SimpleMesh {
	glm::vec2* vertices;
	int* indices;
	std::size_t size;
};

struct CastEl {
	float distance;
	bool in;

	CastEl(float distance, bool in) :
			distance(distance), in(in) {

	}
};

struct {
	bool operator()(const CastEl& c1, const CastEl& c2) {
		return c1.distance <= c2.distance;
	}
} castElComp;

constexpr bool IsClose(double value, double number = 0,
		double epsilon = EPSILON) {
	return fabs(value - number) <= EPSILON;
}
}

#endif /* UTILS_H_ */

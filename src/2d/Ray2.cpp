/*
 * Ray2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Ray2.h"

#include <math.h>

#include "../utils.h"

namespace param {

Ray2::Ray2(const glm::vec2& origin, const glm::vec2& direction) :
		orig(origin), dir(direction) {
}

Ray2::~Ray2() {
}

void Ray2::Set(const glm::vec2& origin, const glm::vec2& direction) {
	orig = origin;
	dir = direction;
}

float Ray2::Intersect(const glm::vec2& v1, const glm::vec2& v2) const {
	auto r = v2 - v1;

	auto u = NAN;

	if (!(IsClose(cross(r, dir)) && !IsClose(cross((v1 - orig), r)))) {
		auto t1 = cross((orig - v1), dir) / cross(r, dir);
		auto t2 = cross((v1 - orig), r) / cross(dir, r);

		if ((t1 >= 0) && (t1 <= 1) && (t2 >= 0)) {
			u = t2;
		}
	}

	return u;
}

bool Ray2::Intersect(const glm::vec2& v1, const glm::vec2& v2, float& u) const {

	auto r = v2 - v1;

	if (IsClose(cross(r, dir)) && !IsClose(cross((v1 - orig), r))) {
		return false;
	} else {
		auto t1 = cross((orig - v1), dir) / cross(r, dir);
		auto t2 = cross((v1 - orig), r) / cross(dir, r);

		if ((t1 >= 0) && (t1 <= 1)) {
			u = t2;

			return true;
		}
	}

	return false;
}

glm::vec2 Ray2::GetDirection() const {
	return dir;
}

glm::vec2 Ray2::GetOrigin() const {
	return orig;
}

} /* namespace param */


/*
 * Ray2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Ray2.h"

#include <math.h>

#include "utils.h"

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

bool Ray2::Intersect(const glm::vec2& v1, const glm::vec2& v2, float& t,
		float& u) const {

	auto r = v2 - v1;

	auto origin = orig;

	// Check if cast a vertex
	{
		auto alphaX = (v1.x - origin.x) / dir.x;
		auto alphaY = (v1.y - origin.y) / dir.y;

		auto betaX = (v2.x - origin.x) / dir.x;
		auto betaY = (v2.y - origin.y) / dir.y;

		// Move the origin if cast a vertex
		if (closeto(alphaX, alphaY) || closeto(betaX, betaY)) {
			origin.y += 2 * REL_TOL;
		}
	}

	if (closeto(cross(r, dir), 0) && !closeto(cross((v1 - origin), r), 0)) {
		return false;
	} else {
		auto t1 = cross((origin - v1), dir) / cross(r, dir);
		auto t2 = cross((v1 - origin), r) / cross(dir, r);

		if ((t1 >= 0) && (t1 <= 1)) {
			t = t1;
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


/*
 * Ray2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Ray2.h"

#include "../defaults.h"
#include "../utils.h"

namespace param {

float cross(const glm::vec2& v1, const glm::vec2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}

Ray2::Ray2(const glm::vec2& origin, const glm::vec2& direction) :
		orig(origin), dir(direction) {
}

Ray2::~Ray2() {
}

void Ray2::Set(const glm::vec2& origin, const glm::vec2& direction) {
	orig = origin;
	dir = direction;
}

bool Ray2::Intersect(const Edge2* edge, glm::vec2& intersecetionPoint) const {
	auto v = edge->Get();

	auto r = *v[1] - *v[0];

	intersecetionPoint = glm::vec2();

	if (IsClose(cross(r, dir)) && !IsClose(cross((*v[0] - orig), r))) {
		return false;
	} else {
		auto t = cross((orig - *v[0]), dir) / cross(r, dir);
		auto u = cross((*v[0] - orig), r) / cross(dir, r);

		if ((t >= 0) && (t <= 1) && (u >= 0)) {
			intersecetionPoint = *v[0] + t * r;
		}

		return true;
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

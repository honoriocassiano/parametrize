/*
 * Ray.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Ray.h"

#include "defaults.h"

#include <glm/geometric.hpp>

namespace param {

Ray::Ray(const glm::vec3& _origin, const glm::vec3& _direction) :
		orig(_origin), dir(glm::normalize(_direction)) {
}

Ray::~Ray() {
}

bool Ray::Intersect(const Triangle* triangle) const {

	float u, v;
	auto tpoints = triangle->get();

	// Möller–Trumbore algorithm
	auto v0v1 = *tpoints[1] - *tpoints[0];
	auto v0v2 = *tpoints[2] - *tpoints[0];

	auto pvec = glm::cross(dir, v0v2);

	auto det = glm::dot(v0v1, pvec);

	if (det < EPSILON) {
		return false;
	}

	auto inv = 1 / det;

	auto aux = orig - *tpoints[0];

	u = glm::dot(dir, pvec) * inv;

	if ((u < 0) || (u > 1)) {
		return false;
	}

	aux = glm::cross(aux, v0v1);
	v = glm::dot(dir, aux) * inv;

	if ((v < 0) || (u + v > 1)) {
		return false;
	}

	return true;
}

float Ray::GetIntersectionDistance(const Triangle* triangle) const {

	auto points = triangle->get();

	auto normal = glm::cross(*points[1] - *points[0], *points[2] - *points[0]);

	return glm::dot((*points[0] - orig), normal) / glm::dot(dir, normal);

//	return ((d * dir) + orig);
}

} /* namespace param */

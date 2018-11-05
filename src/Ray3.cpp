/*
 * Ray.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Ray3.h"

#include "defaults.h"

#include <glm/geometric.hpp>

namespace param {

Ray3::Ray3(const glm::vec3& _origin, const glm::vec3& _direction) :
		orig(_origin), dir(glm::normalize(_direction)) {
}

Ray3::~Ray3() {
}

bool Ray3::Intersect(const Triangle* triangle) const {

	float u, v;
	auto tpoints = triangle->Get();

	// Möller–Trumbore algorithm
	auto v0v1 = *tpoints[1] - *tpoints[0];
	auto v0v2 = *tpoints[2] - *tpoints[0];

	auto pvec = glm::cross(dir, v0v2);

	auto det = glm::dot(v0v1, pvec);

//	if (det < EPSILON) {
	if ((det > -EPSILON) && (det < EPSILON)) {
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

float Ray3::GetIntersectionDistance(const Triangle* triangle) const {

	auto points = triangle->Get();
	auto normal = triangle->GetNormal();

	return glm::dot((*points[0] - orig), normal) / glm::dot(dir, normal);
}

void Ray3::Set(const glm::vec3& origin, const glm::vec3& direction) {
	orig = origin;
	dir = direction;
}

glm::vec3 Ray3::GetDirection() const {
	return dir;
}

glm::vec3 Ray3::GetOrigin() const {
	return orig;
}

} /* namespace param */

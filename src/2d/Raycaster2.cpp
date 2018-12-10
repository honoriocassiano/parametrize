/*
 * Raycaster2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Raycaster2.h"

#include <algorithm>
#include <glm/geometric.hpp>

namespace param {

Raycaster2::Raycaster2() {
}

Raycaster2::~Raycaster2() {
}

std::vector<CastEl> Raycaster2::Cast(const Ray2& ray, const Polygon& mesh) {

//	glm::vec2 intPoint;
	float u;
	std::vector<CastEl> casts;

	for (int i = 0; i < mesh.size; ++i) {

		auto v1 = mesh.vertices[i];
		auto v2 = mesh.vertices[(i + 1) % mesh.size];

//		if (ray.Intersect(v1, v2, intPoint)) {
		if (ray.Intersect(v1, v2, u)) {

			auto normal = (v2 - v1);
			normal = glm::vec2(normal.y, -normal.x);

//			auto distance = glm::distance(ray.GetOrigin(), intPoint);
			auto distance =
					(u >= 0) ?
							glm::length(u * ray.GetDirection()) :
							-glm::length(u * ray.GetDirection());

			auto in = (glm::dot(normal, ray.GetDirection()) >= 0);

			casts.emplace_back(distance, in);

		}
	}

	std::sort(casts.begin(), casts.end(), castElComp);

	return casts;
}

} /* namespace param */


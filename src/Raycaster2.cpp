/*
 * Raycaster2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Raycaster2.h"

#include <glm/detail/type_vec.hpp>
#include <glm/geometric.hpp>
#include <algorithm>
#include <cstdio>

#include "defaults.h"
#include "Polygon.h"
#include "Ray2.h"

namespace param {

Raycaster2::Raycaster2() {
}

Raycaster2::~Raycaster2() {
}

std::vector<CastEl> Raycaster2::Cast(const Ray2& ray, Polygon* mesh,
		float maxDistanceFront, float maxDistanceBack) {

	float t, u;
	std::vector<CastEl> casts;

	for (int i = 0; i < mesh->size; ++i) {

		auto v1 = mesh->vertices[i];
		auto v2 = mesh->vertices[(i + 1) % mesh->size];

		if (ray.Intersect(v1, v2, t, u)) {

			auto normal = (v2 - v1);
			normal = glm::vec2(normal.y, -normal.x);

			auto distance =
					(u >= 0) ?
							glm::length(u * ray.GetDirection()) :
							-glm::length(u * ray.GetDirection());

			if ((distance + REL_TOL) > maxDistanceBack
					&& (distance - REL_TOL) < maxDistanceFront) {
				auto in = (glm::dot(normal, ray.GetDirection()) >= 0);

				casts.emplace_back(distance, t, in);
			}
		}
	}

	std::sort(casts.begin(), casts.end(), castElComp);

	return casts;
}

} /* namespace param */


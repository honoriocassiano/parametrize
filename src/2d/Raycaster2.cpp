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

std::vector<CastEl> Raycaster2::Cast(const Ray2& ray,
		const std::vector<Edge2*>& edges) {

	glm::vec2 intPoint;
	std::vector<CastEl> casts;

	for (const auto& e : edges) {

		if (ray.Intersect(e, intPoint)) {

			auto distance = glm::distance(ray.GetOrigin(), intPoint);
			auto in = (glm::dot(e->GetNormal(), ray.GetDirection()) >= 0);

			casts.emplace_back(distance, in);

			auto temp = e->Get();
		}
	}

	std::sort(casts.begin(), casts.end(), castElComp);

	return casts;
}

} /* namespace param */


/*
 * Raytracer.cpp
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#include "Raycaster3.h"

#include <algorithm>
#include <glm/geometric.hpp>

namespace param {

Raycaster3::Raycaster3() {
}

Raycaster3::~Raycaster3() {
}

std::vector<CastEl> Raycaster3::Cast(const Ray3& ray,
		const std::vector<Triangle*>& triangles) {

	std::vector<CastEl> casts;

	for (const auto& t : triangles) {
		if (ray.Intersect(t)) {
			auto distance = ray.GetIntersectionDistance(t);
			auto in = (glm::dot(t->GetNormal(), ray.GetDirection()) >= 0);

			casts.push_back( { distance, in });

			auto temp = t->Get();
		}
	}

	std::sort(casts.begin(), casts.end(), castElComp);

	return casts;
}

} /* namespace param */

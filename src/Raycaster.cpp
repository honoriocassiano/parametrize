/*
 * Raytracer.cpp
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#include "Raycaster.h"

namespace param {

Raycaster::Raycaster() {
}

Raycaster::~Raycaster() {
}

std::vector<float> Raycaster::Cast(const Ray& ray, const std::vector<Triangle*>& triangles) {

	std::vector<float> distances;

	for(const auto& t : triangles) {
		if(ray.Intersect(t)) {
			distances.push_back(ray.GetIntersectionDistance(t));
		}
	}

	return distances;
}

} /* namespace param */

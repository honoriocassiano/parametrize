/*
 * Parametrizer2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Parametrizer2.h"

#include "Raycaster2.h"

namespace param {

Parametrizer2::Parametrizer2(bool _wrap) :
		wrap(_wrap) {
}

Parametrizer2::~Parametrizer2() {
}

std::tuple<glm::vec2*, int*> Parametrizer2::GetGLMesh(float* distances,
		float step) const {
	// TODO Implement this
	return std::tuple<glm::vec2*, int*>();
}

float* Parametrizer2::Paramatrize(std::vector<Edge2*> edges, float step,
		std::size_t& size) {

	size = (int(1 / step) + 1);

	glm::vec2 origin, direction;

	Ray2 ray(origin, direction);
	Raycaster2 caster;

	auto maxStep = 1 + step;

	float* matrix = new float[size];

	for (int i = 0; i < size; ++i) {

		this->GetNext(i, step, origin, direction);

//		printf("(%.2f, %.2f)\n", direction.x, direction.y);

		ray.Set(origin, direction);

		// TODO Add max distance to cast
		auto casts = caster.Cast(ray, edges);

//		printf("%lu\n", casts.size());

		if (casts.size() > 2) {
			// TODO Mark to recast
		}

		if (casts.size() > 0) {
			//			matrix[int(u / stepU)][int(v / stepV)] = casts[0].distance;
			matrix[i] = casts[0].distance;
		} else {
			matrix[i] = NAN;
		}
	}

	return matrix;
}

} /* namespace param */

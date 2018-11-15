/*
 * Parametrizer2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Parametrizer2.h"

#include "Raycaster2.h"

namespace param {

Parametrizer2::Parametrizer2(const SimpleMesh& _mesh, std::size_t _splits) :
		mesh(_mesh), splits(_splits), child(nullptr), distances(nullptr) {
}

Parametrizer2::~Parametrizer2() {
	delete[] child;
	delete[] distances;
}

Polygon Parametrizer2::GetPolygon() const {

	float step = 1.0 / splits;

	glm::vec2 origin, direction;

	glm::vec2 *points = new glm::vec2[splits];

	for (int i = 0; i < splits; ++i) {
		this->GetNext(i, step, origin, direction);

		points[i] = origin + distances[i] * direction;
	}

	return Polygon(points, splits);
}

float Parametrizer2::Paramatrize() {

	float step = 1.0 / splits;

	glm::vec2 origin, direction;

	Ray2 ray(origin, direction);
	Raycaster2 caster;

	distances = new float[splits];

	for (int i = 0; i < splits; ++i) {

		this->GetNext(i, step, origin, direction);

		ray.Set(origin, direction);

		// TODO Add max distance to cast
		auto casts = caster.Cast(ray, mesh);

		if (casts.size() > 2) {
			// TODO Mark to recast
		}

		if (casts.size() > 0) {
			distances[i] = casts[0].distance;
		} else {
			distances[i] = NAN;
		}
	}

// TODO Return error
	return 0;
}

} /* namespace param */

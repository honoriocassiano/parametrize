/*
 * Parametrizer.cpp
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#include "Parametrizer.h"

#include "defaults.h"
#include "Raycaster.h"

namespace param {

int toMatrix(float u, float v, float stepU, float stepV) {
	int posU = int(u / stepU);
	int posV = int(v / stepV);

	return (int(1 / stepV) + 1) * posU + posV;
}

Parametrizer::Parametrizer(bool _wrap) :
		wrap(_wrap) {
}

Parametrizer::~Parametrizer() {
}

std::tuple<glm::vec3*, int*> Parametrizer::GetGLMesh(float* distances,
		float stepU, float stepV) const {

	// TODO Implement this function
}

// TODO Change this for "circular" polyhedrons
float* Parametrizer::Paramatrize(std::vector<Triangle*> triangles, float stepU,
		float stepV, int& w, int& h) {

	w = (int(1 / stepV) + 1);
	h = (int(1 / stepU) + 1);

	float* matrix = new float[w * h];

	glm::vec3 origin, direction;

	Ray ray(origin, direction);
	Raycaster caster;

	for (float u = 0; (1 - u) <= EPSILON; u += stepU) {
		for (float v = 0; (1 - v) <= EPSILON; v += stepV) {
			this->GetStep(u, v, origin, direction);

			ray.Set(origin, direction);

			// TODO Add max distance to cast
			auto casts = caster.Cast(ray, triangles);

			if (casts.size() > 2) {
				// TODO Mark to recast
			}

			if (casts.size() > 0) {
//			matrix[int(u / stepU)][int(v / stepV)] = casts[0].distance;
				matrix[toMatrix(u, v, stepU, stepV)] = casts[0].distance;
			} else {
				matrix[toMatrix(u, v, stepU, stepV)] = -1;
			}
		}
	}

	return matrix;
}

} /* namespace param */

/*
 * CircleParametrizer.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "CircleParametrizer.h"

#include <math.h>
#include <glm/geometric.hpp>

namespace param {

CircleParametrizer::CircleParametrizer(const SimpleMesh& mesh, float step,
		glm::vec2 center, float radius) :
		Parametrizer2(mesh, step), c(center), r(
				radius) {
}

CircleParametrizer::~CircleParametrizer() {
}

void CircleParametrizer::GetNext(int i, float step, glm::vec2& origin,
		glm::vec2& direction) const {

	float u = (-i * step) * 2 * M_PI;

	origin = glm::vec2(r * cos(u), r * sin(u));
	direction = glm::normalize(c - origin);
}

} /* namespace param */

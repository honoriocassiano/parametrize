/*
 * PlaneParametrizer.cpp
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#include <glm/geometric.hpp>
#include "PlaneParametrizer3.h"

namespace param {

PlaneParametrizer::PlaneParametrizer(const glm::vec3& _p0, const glm::vec3& _u,
		const glm::vec3& _v) :
		p0(_p0), u(_u), v(_v) {

	normal = glm::normalize(glm::cross(u, v));
}

PlaneParametrizer::~PlaneParametrizer() {
}

void PlaneParametrizer::GetStep(float a, float b, glm::vec3& origin,
		glm::vec3& direction) const {

	origin = a * u + b * v + p0;
	direction = normal;
}

} /* namespace param */
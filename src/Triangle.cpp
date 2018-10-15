/*
 * Triangle.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Triangle.h"

namespace param {

Triangle::Triangle(glm::vec3* p1, glm::vec3* p2, glm::vec3* p3) :
		points( { p1, p2, p3 }) {
}

Triangle::~Triangle() {
}

const std::array<glm::vec3*, 3>& Triangle::get() const {
	return points;
}

} /* namespace param */

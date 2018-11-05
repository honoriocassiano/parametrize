/*
 * Edge2.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Edge2.h"

namespace param {

Edge2::Edge2(glm::vec2* v1, glm::vec2* v2) :
		vertices { v1, v2 } {

	normal = (*v2 - *v1);
	normal = glm::vec2(normal.y, -normal.x);
}

Edge2::~Edge2() {
}

const std::array<glm::vec2*, 2>& Edge2::Get() const {
	return vertices;
}

const glm::vec2 Edge2::GetNormal() const {
	return normal;
}

} /* namespace param */

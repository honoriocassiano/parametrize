/*
 * ParametrizedPolygon.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "ParametrizedPolygon.h"

namespace param {

ParametrizedPolygon::ParametrizedPolygon(float* _distances,
		glm::vec2* _vertices, std::size_t _size) :
		child(nullptr), distances(_distances), vertices(_vertices), size(_size) {
}

ParametrizedPolygon::~ParametrizedPolygon() {
	if (child) {
		delete child;
	}

	delete[] distances;
	delete[] vertices;
}

} /* namespace param */

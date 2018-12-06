/*
 * CircleParametrizer2.cpp
 *
 *  Created on: 25 de nov de 2018
 *      Author: cassiano
 */

#include "CircleParametrizer2.h"

#include <math.h>
#include <glm/geometric.hpp>

#include <stdio.h>

namespace param {

CircleParametrizer2::CircleParametrizer2(SimpleMesh* _mesh, std::size_t size,
		glm::vec2 _center, float _radius) :
		ParametrizedPolygon(), center(_center), radius(_radius) {

	auto step = 1.0 / size;

	auto vertices = new glm::vec2[size];
	auto normals = new glm::vec2[size];

	glm::vec2 lastNormal;

	for (long i = 0; i < size; ++i) {

		float u = (-i * step) * 2 * M_PI;

		vertices[i] = glm::vec2(radius * cos(u), radius * sin(u));
		normals[i] = glm::normalize(center - vertices[i]);
	}

	mesh = _mesh;
	layers = new std::vector<VertexHolder>;

	layers->emplace_back(vertices, normals, nullptr, nullptr, size, size);
}

CircleParametrizer2::~CircleParametrizer2() {
}

} /* namespace param */

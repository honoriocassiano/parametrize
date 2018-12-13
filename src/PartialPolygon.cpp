/*
 * PartialPolygon.cpp
 *
 *  Created on: 13 de dez de 2018
 *      Author: cassiano
 */

#include "PartialPolygon.h"

#include <GL/gl.h>
#include <algorithm>
#include <cstddef>

#include "Polygon.h"

namespace param {

PartialPolygon::PartialPolygon() :
		closed(false) {
}

PartialPolygon::~PartialPolygon() {
}

void PartialPolygon::AddVertex(const glm::vec2& p) {
	if (!closed) {
		vertices.push_back(p);
	}
}

void PartialPolygon::Clear() {
	vertices.clear();
	closed = false;
}

Polygon* PartialPolygon::GetPolygon() const {
	if (!closed)
		return nullptr;

	if (vertices.size() < 3)
		return nullptr;

	auto newVertices = new glm::vec2[vertices.size()];

	std::copy(vertices.begin(), vertices.end(), newVertices);

	return new Polygon(newVertices, vertices.size());
}

bool PartialPolygon::Close() {
	if (vertices.size() > 2) {
		closed = true;
	}

	return closed;
}

void PartialPolygon::Draw(bool points) const {
	if (points) {
		glPointSize(5.0);
		glBegin(GL_POINTS);
	} else {
		glBegin(GL_LINE_STRIP);
	}

	for (std::size_t i = 0; i < vertices.size(); ++i) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}

	glEnd();
}

bool PartialPolygon::IsClosed() const {
	return closed;
}

} /* namespace param */

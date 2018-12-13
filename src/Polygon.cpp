/*
 * Polygon.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Polygon.h"

#include <GL/gl.h>

namespace param {

Polygon::Polygon(glm::vec2* _vertices, std::size_t _size) :
		vertices(_vertices), size(_size) {
}

glm::vec2 Polygon::GetCentroid() const {

	float centroidX = 0, centroidY = 0;

	for (std::size_t i = 0; i < size; ++i) {
		centroidX += vertices[i].x;
		centroidY += vertices[i].y;
	}

	return glm::vec2(centroidX / size, centroidY / size);
}

void Polygon::Draw(bool points) const {

	if (points) {
		glPointSize(5.0);
		glBegin(GL_POINTS);
	} else {
		glBegin(GL_LINE_LOOP);
	}

	for (std::size_t i = 0; i < size; ++i) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}

	glEnd();
}

Polygon::~Polygon() {
	delete vertices;
}

} /* namespace param */


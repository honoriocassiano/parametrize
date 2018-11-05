/*
 * Polygon.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Polygon.h"

#include <GL/gl.h>

#include <stdio.h>

namespace param {

Polygon::Polygon(glm::vec2* _positions, std::size_t _size) :
		positions(_positions), size(_size) {
}

void Polygon::Draw(bool points) const {

	if(points) {
		glBegin(GL_POINTS);
	} else {
		glBegin(GL_LINE_LOOP);
	}


	for (int i = 0; i < size; ++i) {
		glVertex2f(positions[i].x, positions[i].y);

//		printf("(%.2f), %.2f)\n", positions[i].x, positions[i].y);
	}

	glEnd();
}

Polygon::~Polygon() {
	delete[] positions;
}

} /* namespace param */

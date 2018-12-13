/*
 * Polygon.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "Polygon.h"

#include <glm/detail/func_geometric.hpp>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

namespace param {

Polygon::Polygon(glm::vec2* _vertices, std::size_t _size) :
		vertices(_vertices), size(_size) {

	float left, right, top, bottom;

	left = right = vertices[0].x;
	bottom = top = vertices[0].y;

	for (std::size_t i = 1; i < size; ++i) {
		auto v = vertices[i];

		if (v.x < left) {
			left = v.x;
		} else if (v.x > right) {
			right = v.x;
		}

		if (v.y < bottom) {
			bottom = v.y;
		} else if (v.y > top) {
			top = v.y;
		}
	}

	bRectTopLeft = glm::vec2(left, top);
	bRectBottomRight = glm::vec2(right, bottom);

	bCircleCenter = glm::vec2((right + left) / 2, (top + bottom) / 2);
	bCircleRadius = glm::length(glm::vec2(right, top) - bCircleCenter);
}

void Polygon::GetBoundingCircle(glm::vec2& center, float& radius) const {
	center = bCircleCenter;
	radius = bCircleRadius;
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

void Polygon::DrawBoundingRect() const {
	glBegin(GL_LINE_LOOP);

	glVertex2f(bRectTopLeft.x, bRectTopLeft.y);
	glVertex2f(bRectTopLeft.x, bRectBottomRight.y);
	glVertex2f(bRectBottomRight.x, bRectBottomRight.y);
	glVertex2f(bRectBottomRight.x, bRectTopLeft.y);

	glEnd();
}

Polygon::~Polygon() {
	delete vertices;
}

} /* namespace param */


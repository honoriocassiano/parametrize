/*
 * utils.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "defaults.h"

#include <math.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>

namespace param {

struct VertexHolder {
	glm::vec2* vertices;
	glm::vec2* normals;
	float* distances;
	std::size_t size;
	std::size_t count;

	VertexHolder(glm::vec2* _vertices, glm::vec2* _normals, float* _distances,
			std::size_t _size, std::size_t _count) :
			vertices(_vertices), normals(_normals), distances(_distances), size(
					_size), count(_count) {

	}
};

struct SimpleMesh {
	glm::vec2* vertices;
	int* indices;
	std::size_t size;

	void Draw(bool points=false) const {
		if (points) {
			glPointSize(3.0);
			glBegin(GL_POINTS);
		} else {
			glBegin(GL_LINE_LOOP);
		}

		for (std::size_t i = 0; i < size; ++i) {
			glVertex2f(vertices[indices[i]].x, vertices[indices[i]].y);
		}

		glEnd();
	}
};

struct CastEl {
	float distance;
	bool in;

	CastEl(float distance, bool in) :
			distance(distance), in(in) {

	}
};

struct {
	bool operator()(const CastEl& c1, const CastEl& c2) {
		return c1.distance <= c2.distance;
	}
} castElComp;

constexpr bool IsClose(double value, double number = 0,
		double epsilon = EPSILON) {
	return fabs(value - number) <= EPSILON;
}
}

#endif /* UTILS_H_ */

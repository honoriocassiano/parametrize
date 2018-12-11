/*
 * utils.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <ext/type_traits.h>
#include <glm/detail/type_vec.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

#include "defaults.h"

namespace glm {
glm::vec2& normal(glm::vec2&& v);

float cross(const glm::vec2& v1, const glm::vec2& v2);
}

namespace param {

struct VertexHolder;
struct VertexIndex;

bool closeto(float v1, float v2, float rtol = REL_TOL, float atol = ABS_TOL);

VertexIndex GetByPosition(const std::vector<VertexHolder>& layers,
		std::size_t i);

struct VertexIndex {
	std::size_t layer;
	std::size_t pos;
};

struct VertexHolder {
	glm::vec2* vertices;
	glm::vec2* normals;
	float* distances;

	VertexHolder(glm::vec2* _vertices, glm::vec2* _normals, float* _distances) :
			vertices(_vertices), normals(_normals), distances(_distances) {

	}
};

struct CastEl {
	float distance;
	float u;
	bool in;

	CastEl(float distance, float u, bool in) :
			distance(distance), u(u), in(in) {

	}
};

struct {
	bool operator()(const CastEl& c1, const CastEl& c2) {
//		if (closeto(c1.distance, 0)) {
//			return true;
//		} else if (closeto(c2.distance, 0)) {
//			return false;
//		}
//
//		return c1.distance <= c2.distance;

		return c1.distance <= c2.distance;
	}
} castElComp;

}

#endif /* UTILS_H_ */

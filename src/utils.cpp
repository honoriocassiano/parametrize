/*
 * utils.cpp
 *
 *  Created on: 4 de dez de 2018
 *      Author: cassiano
 */

#include "utils.h"

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <cstddef>

namespace glm {
glm::vec2& normal(glm::vec2&& v) {
	auto tmp = v.x;
	v.x = -v.y;
	v.y = tmp;
	return v;
}

float cross(const glm::vec2& v1, const glm::vec2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}
}

namespace param {

bool closeto(float v1, float v2, float rtol, float atol) {
	return fabs(v1 - v2)
			<= std::max(rtol * std::max(abs(v1), abs(v2)), atol);
}

VertexIndex GetByPosition(const std::vector<VertexHolder>& layers,
		std::size_t i) {
	if (layers.size() == 1) {
		return VertexIndex { 0, i };
	}

	std::size_t level = 0, pos = 0;
	std::size_t levels = layers.size();

	if (layers.size() == 3 && i == 2) {
		int a = 1;
	}

	for (auto l = 0; l < levels; ++l) {
		auto temp = 1 << l;

		if (l < (levels - 1)) {
			if ((i - temp) % (1 << (l + 1)) == 0) {
				level = levels - l - 1;
				pos = (i - temp) / (1 << (l + 1));

				break;
			}
		} else {
			level = 0;
			pos = i / (1 << l);
		}
	}

	return VertexIndex { level, pos };
}
}


/*
 * utils.cpp
 *
 *  Created on: 4 de dez de 2018
 *      Author: cassiano
 */

#include "utils.h"

namespace param {

VertexIndex GetByPosition(const std::vector<VertexHolder>& layers,
		std::size_t i) {
	if (layers.size() == 1) {
		return VertexIndex { 0, i };
	}

	std::size_t level = 0, pos = 0;
	std::size_t levels = layers.size();

	if (i >= layers.back().count) {
		return VertexIndex { 0, 0 };
	}

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

VertexIndex GetByPosition(std::vector<VertexHolder>* layers, std::size_t i) {
	return GetByPosition(*layers, i);
}

void ToNormal(glm::vec2& v) {
	auto tmp = v.x;
	v.x = -v.y;
	v.y = tmp;
}
}
;


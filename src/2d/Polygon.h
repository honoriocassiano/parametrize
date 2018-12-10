/*
 * Polygon.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include <glm/vec2.hpp>

namespace param {

struct Polygon {
public:
	Polygon(glm::vec2* vertices, std::size_t size);

	void Draw(bool points = false) const;

	virtual ~Polygon();


	glm::vec2* vertices;
	std::size_t size;
};

} /* namespace param */

#endif /* POLYGON_H_ */

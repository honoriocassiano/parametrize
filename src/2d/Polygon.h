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

class Polygon {
public:
	Polygon(glm::vec2* positions, std::size_t size);

	void Draw() const;

	virtual ~Polygon();

private:

	glm::vec2* positions;

	std::size_t size;
};

} /* namespace param */

#endif /* POLYGON_H_ */

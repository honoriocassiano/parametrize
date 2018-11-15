/*
 * ParametrizedPolygon.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef PARAMETRIZEDPOLYGON_H_
#define PARAMETRIZEDPOLYGON_H_

#include <glm/vec2.hpp>

namespace param {

class ParametrizedPolygon {
public:
	ParametrizedPolygon(float* distances, glm::vec2* vertices,
			std::size_t size);
	virtual ~ParametrizedPolygon();

private:

	ParametrizedPolygon* child;

	std::size_t size;

	float* distances;
	glm::vec2* vertices;
};

} /* namespace param */

#endif /* PARAMETRIZEDPOLYGON_H_ */

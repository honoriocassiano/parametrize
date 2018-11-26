/*
 * ParametrizedPolygon.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef PARAMETRIZEDPOLYGON_H_
#define PARAMETRIZEDPOLYGON_H_

#include "Polygon.h"

#include "../utils.h"

#include <vector>
#include <glm/vec2.hpp>

namespace param {

class ParametrizedPolygon {
public:
	ParametrizedPolygon(SimpleMesh* mesh, glm::vec2* vertices,
			std::size_t size);

	virtual ~ParametrizedPolygon();

	Polygon GetPolygon();

	virtual float Parametrize();

protected:

	ParametrizedPolygon();

	ParametrizedPolygon(SimpleMesh* mesh, glm::vec2* vertices, std::size_t size,
			unsigned char level, std::vector<VertexHolder>* layers);

private:
	void ComputeNormals();

protected:
	SimpleMesh* mesh;
	ParametrizedPolygon* child;

//	std::size_t size;
//
//	float* distances;
//	glm::vec2* vertices;
	unsigned char level;

	std::vector<VertexHolder>* layers;
};

} /* namespace param */

#endif /* PARAMETRIZEDPOLYGON_H_ */

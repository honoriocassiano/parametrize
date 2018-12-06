/*
 * CircleParametrizer.h
 *
 *  Created on: 25 de nov de 2018
 *      Author: cassiano
 */

#ifndef CIRCLEPARAMETRIZER_H_
#define CIRCLEPARAMETRIZER_H_

#include <glm/detail/type_vec.hpp>

#include "ParametrizedPolygon.h"

namespace param {

class CircleParametrizer {
public:
	CircleParametrizer(SimpleMesh* mesh, std::size_t steps, glm::vec2 center,
			float radius);
	virtual ~CircleParametrizer();

	Polygon GetPolygon();

	/***
	 * Compute normals by vertex
	 */
	void ComputeNormals();

	virtual float Parametrize();

protected:

	virtual void Cast();

//private:
//	void ComputeNormals();

private:
	SimpleMesh* mesh;
//	ParametrizedPolygon* child;

//	std::size_t size;
//
//	float* distances;
//	glm::vec2* vertices;
	unsigned char level;

	std::vector<VertexHolder> layers;

private:
	float radius;
	glm::vec2 center;
};

}
/* namespace param */

#endif /* CIRCLEPARAMETRIZER_H_ */

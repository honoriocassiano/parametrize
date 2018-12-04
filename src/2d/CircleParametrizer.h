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

//	virtual glm::vec2 GetMidPoint();

	Polygon GetPolygon();

	virtual float Parametrize();

//protected:
//
//	ParametrizedPolygon();
//
//	ParametrizedPolygon(SimpleMesh* mesh, glm::vec2* vertices, std::size_t size,
//			unsigned char level, std::vector<VertexHolder>* layers);

private:
	void ComputeNormals();

protected:
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

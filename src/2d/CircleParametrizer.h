/*
 * CircleParametrizer.h
 *
 *  Created on: 25 de nov de 2018
 *      Author: cassiano
 */

#ifndef CIRCLEPARAMETRIZER_H_
#define CIRCLEPARAMETRIZER_H_

#include <glm/detail/type_vec.hpp>

#include "../utils.h"
#include "Polygon.h"

#include <vector>
#include <glm/vec2.hpp>

namespace param {

class CircleParametrizer {
public:
	CircleParametrizer(Polygon* mesh, std::size_t steps, glm::vec2 center,
			float radius);
	virtual ~CircleParametrizer();

	Polygon* GetPolygon();

	/***
	 * Compute normals by vertex
	 */
	void ComputeNormals();

	virtual float Parametrize();
	void UnParametrize();

protected:

	virtual void Cast();

//private:
//	void ComputeNormals();

private:
	Polygon* mesh;
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

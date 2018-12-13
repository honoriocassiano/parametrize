/*
 * CircleParametrizer.h
 *
 *  Created on: 25 de nov de 2018
 *      Author: cassiano
 */

#ifndef CIRCLEPARAMETRIZER_H_
#define CIRCLEPARAMETRIZER_H_

#include <glm/detail/type_vec.hpp>

#include "utils.h"
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

	void Draw();

	virtual float Parametrize();
	void UnParametrize();

private:
	/***
	 * Compute normals by vertex
	 */
	void ComputeNormals();

	std::size_t Size(std::size_t level) const;
	std::size_t Count() const;

protected:

	virtual void Cast();

private:
	Polygon* mesh;

	std::vector<VertexHolder> layers;

private:
	std::size_t numRays;
	float radius;
	glm::vec2 center;
};

}
/* namespace param */

#endif /* CIRCLEPARAMETRIZER_H_ */

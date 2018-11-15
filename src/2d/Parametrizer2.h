/*
 * Parametrizer2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef PARAMETRIZER2_H_
#define PARAMETRIZER2_H_

#include "Edge2.h"
#include "Polygon.h"
#include "../utils.h"

#include <tuple>
#include <vector>
#include <glm/vec2.hpp>

namespace param {

class Parametrizer2 {
public:
	Parametrizer2(const SimpleMesh& mesh, std::size_t splits);
	virtual ~Parametrizer2();

	Polygon GetPolygon() const;

	float Paramatrize();

protected:

	virtual void GetNext(int i, float step, glm::vec2& origin,
			glm::vec2& direction) const = 0;

protected:

	float * distances;
	Parametrizer2* child;

	SimpleMesh mesh;
	std::size_t splits;
};

} /* namespace param */

#endif /* PARAMETRIZER2_H_ */

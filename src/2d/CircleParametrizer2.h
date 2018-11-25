/*
 * CircleParametrizer2.h
 *
 *  Created on: 25 de nov de 2018
 *      Author: cassiano
 */

#ifndef CIRCLEPARAMETRIZER2_H_
#define CIRCLEPARAMETRIZER2_H_

#include <glm/detail/type_vec.hpp>

#include "ParametrizedPolygon.h"

namespace param {

class CircleParametrizer2: public ParametrizedPolygon {
public:
	CircleParametrizer2(SimpleMesh* mesh, std::size_t steps, glm::vec2 center,
			float radius);
	virtual ~CircleParametrizer2();

private:
	float radius;
	glm::vec2 center;
};

}
/* namespace param */

#endif /* CIRCLEPARAMETRIZER2_H_ */

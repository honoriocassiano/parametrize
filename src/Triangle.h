/*
 * Triangle.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <array>
#include <glm/vec3.hpp>

namespace param {

class Triangle {
public:
	Triangle(glm::vec3* p1, glm::vec3* p2, glm::vec3* p3);
	virtual ~Triangle();

private:
	glm::vec3* points[3];
};

} /* namespace param */

#endif /* TRIANGLE_H_ */

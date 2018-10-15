/*
 * Ray.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <glm/vec3.hpp>

namespace param {

class Ray {
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	virtual ~Ray();

private:
	glm::vec3 orig;
	glm::vec3 dir;
};

} /* namespace param */

#endif /* RAY_H_ */

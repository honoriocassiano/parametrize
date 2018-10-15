/*
 * Ray.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include "Triangle.h"

#include <glm/vec3.hpp>

namespace param {

class Ray {
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	virtual ~Ray();

	bool Intersect(const Triangle* triangle) const;
	float GetIntersectionDistance(const Triangle* triangle) const;

	glm::vec3 GetDir() const;

private:
	glm::vec3 orig;
	glm::vec3 dir;
};

} /* namespace param */

#endif /* RAY_H_ */

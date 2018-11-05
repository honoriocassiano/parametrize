/*
 * Ray2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef RAY2_H_
#define RAY2_H_

#include "Edge2.h"

#include <glm/vec2.hpp>

namespace param {

class Ray2 {
public:
	Ray2(const glm::vec2& origin, const glm::vec2& direction);
	virtual ~Ray2();

	void Set(const glm::vec2& origin, const glm::vec2& direction);

	bool Intersect(const Edge2* edge, glm::vec2& intsecetionPoint) const;

	glm::vec2 GetDirection() const;
	glm::vec2 GetOrigin() const;

private:
	glm::vec2 orig;
	glm::vec2 dir;
};

} /* namespace param */

#endif /* RAY2_H_ */

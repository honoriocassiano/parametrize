/*
 * Ray2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef RAY2_H_
#define RAY2_H_

#include <glm/vec2.hpp>

namespace param {

class Ray2 {
public:
	Ray2() = default;
	Ray2(const glm::vec2& origin, const glm::vec2& direction);

	virtual ~Ray2();

	void Set(const glm::vec2& origin, const glm::vec2& direction);

//	bool Intersect(const glm::vec2& v1, const glm::vec2& v2, glm::vec2& intsecetionPoint) const;
	bool Intersect(const glm::vec2& v1, const glm::vec2& v2, float& u) const;
	float Intersect(const glm::vec2& v1, const glm::vec2& v2) const;

	glm::vec2 GetDirection() const;
	glm::vec2 GetOrigin() const;

private:
	glm::vec2 orig;
	glm::vec2 dir;
};

} /* namespace param */

#endif /* RAY2_H_ */

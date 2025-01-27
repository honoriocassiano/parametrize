/*
 * Polygon.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <cstddef>

namespace param {

struct Polygon {
public:
	Polygon(glm::vec2* vertices, std::size_t size);

	void Draw(bool points = false) const;

	void DrawBoundingRect() const;

	void GetBoundingCircle(glm::vec2& center, float& radius) const;

	virtual ~Polygon();

	glm::vec2* vertices;
	std::size_t size;

private:
	glm::vec2 bCircleCenter;
	float bCircleRadius;

	glm::vec2 bRectTopLeft;
	glm::vec2 bRectBottomRight;
};

} /* namespace param */

#endif /* POLYGON_H_ */

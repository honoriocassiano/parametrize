/*
 * Edge2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef EDGE2_H_
#define EDGE2_H_

#include <array>
#include <glm/vec2.hpp>

namespace param {

class Edge2 {
public:
	Edge2(glm::vec2* v1, glm::vec2* v2);
	virtual ~Edge2();

	const std::array<glm::vec2*, 2>& Get() const;

	const glm::vec2 GetNormal() const;

private:
	glm::vec2 normal;
	std::array<glm::vec2*, 2> vertices;
};
}
/* namespace param */

#endif /* EDGE2_H_ */

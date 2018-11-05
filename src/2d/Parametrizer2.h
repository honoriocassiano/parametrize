/*
 * Parametrizer2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef PARAMETRIZER2_H_
#define PARAMETRIZER2_H_

#include "Edge2.h"

#include <tuple>
#include <vector>
#include <glm/vec2.hpp>

namespace param {

class Parametrizer2 {
public:
	Parametrizer2(bool wrap = true);
	virtual ~Parametrizer2();

	virtual void GetNext(int i, float step, glm::vec2& origin,
			glm::vec2& direction) const = 0;

	std::tuple<glm::vec2*, int*> GetGLMesh(float* distances, float step) const;

	float* Paramatrize(std::vector<Edge2*> edges, float step, std::size_t& size);

private:
	bool wrap;
};

} /* namespace param */

#endif /* PARAMETRIZER2_H_ */

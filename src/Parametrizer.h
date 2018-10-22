/*
 * Parametrizer.h
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#ifndef PARAMETRIZER_H_
#define PARAMETRIZER_H_

#include "Triangle.h"

#include <vector>
#include <tuple>

namespace param {

class Parametrizer {
public:
	Parametrizer(bool wrap = true);
	virtual ~Parametrizer();

	virtual void GetStep(float u, float v, glm::vec3& origin,
			glm::vec3& direction) const = 0;

	std::tuple<glm::vec3*, int*> GetGLMesh(float* distances, float stepU, float stepV) const;

	float* Paramatrize(std::vector<Triangle*> triangles, float stepU,
			float stepV, int& w, int& h);

private:
	bool wrap;
};

} /* namespace param */

#endif /* PARAMETRIZER_H_ */

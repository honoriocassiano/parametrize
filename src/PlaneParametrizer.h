/*
 * PlaneParametrizer.h
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#ifndef PLANEPARAMETRIZER_H_
#define PLANEPARAMETRIZER_H_

#include "Parametrizer.h"

#include <glm/vec3.hpp>

namespace param {

class PlaneParametrizer: public Parametrizer {
public:
	PlaneParametrizer(const glm::vec3& p0, const glm::vec3& u,
			const glm::vec3& v);
	virtual ~PlaneParametrizer();

	void GetStep(float a, float b, glm::vec3& origin,
			glm::vec3& direction) const override;

private:
	glm::vec3 p0;
	glm::vec3 u;
	glm::vec3 v;

	glm::vec3 normal;
};

} /* namespace param */

#endif /* PLANEPARAMETRIZER_H_ */

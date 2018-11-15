/*
 * CircleParametrizer.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef CIRCLEPARAMETRIZER_H_
#define CIRCLEPARAMETRIZER_H_

#include "Parametrizer2.h"

#include "../utils.h"

namespace param {

class CircleParametrizer: public Parametrizer2 {
public:
	CircleParametrizer(const SimpleMesh& mesh, float step, glm::vec2 center, float radius);
	virtual ~CircleParametrizer();

protected:
	void GetNext(int i, float step, glm::vec2& origin,
			glm::vec2& direction) const override;

private:
	glm::vec2 c;
	float r;
};

} /* namespace param */

#endif /* CIRCLEPARAMETRIZER_H_ */

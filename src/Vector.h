/*
 * Vector.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include "Point.h"

namespace param {

class Vector : public Point {
public:
	Vector(float x = 0, float y = 0, float z = 0);
	virtual ~Vector();
};

} /* namespace param */

#endif /* VECTOR_H_ */

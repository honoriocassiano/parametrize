/*
 * Triangle.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include "Point.h"
#include <array>

namespace param {

class Triangle {
public:
	Triangle(Point* p1, Point* p2, Point* p3,);
	virtual ~Triangle();

private:
	std::array<Point*, 3> points;

};

} /* namespace param */

#endif /* TRIANGLE_H_ */

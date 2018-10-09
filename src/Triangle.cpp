/*
 * Triangle.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Triangle.h"

namespace param {

Triangle::Triangle(Point* p1, Point* p2, Point* p3) :
		points( { p1, p2, p3 }) {
}

Triangle::~Triangle() {
}

} /* namespace param */

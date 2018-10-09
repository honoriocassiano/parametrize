/*
 * Point.cpp
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#include "Point.h"

namespace param {

Point::Point(float x, float y, float z) :
		values( { x, y, z }) {

}

Point::~Point() {
}

std::array<float, 3> Point::get() {
	return this->values;
}

std::array<float, 3> Point::get() const {
	return this->values;
}

void Point::set(float x, float y, float z) {
	values = {x, y, z};
}

}
/* namespace param */

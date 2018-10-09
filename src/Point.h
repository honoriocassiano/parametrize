/*
 * Point.h
 *
 *  Created on: 8 de out de 2018
 *      Author: cassiano
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include <array>

namespace param {

class Point {
public:
	Point(float x = 0, float y = 0, float z = 0);
	virtual ~Point();

	std::array<float, 3> get();
	std::array<float, 3> get() const;

	void set(float x, float y, float z);

private:

	std::array<float, 3> values;

};

} /* namespace param */

#endif /* POINT_H_ */

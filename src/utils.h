/*
 * utils.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "defaults.h"
#include <math.h>

namespace param {

constexpr bool IsClose(double value, double number = 0, double epsilon = EPSILON) {
	return fabs(value - number) <= EPSILON;
}
}

#endif /* UTILS_H_ */

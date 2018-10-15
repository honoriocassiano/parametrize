/*
 * Raytracer.h
 *
 *  Created on: 15 de out de 2018
 *      Author: cassiano
 */

#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "Ray.h"
#include "Triangle.h"

#include <vector>

namespace param {

class Raycaster {
public:
	Raycaster();
	virtual ~Raycaster();

	std::vector<float> Cast(const Ray& ray, const std::vector<Triangle*>& triangles);
};

} /* namespace param */

#endif /* RAYCASTER_H_ */

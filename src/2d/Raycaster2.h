/*
 * Raycaster2.h
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#ifndef RAYCASTER2_H_
#define RAYCASTER2_H_

#include <vector>

#include "../utils.h"
#include "Edge2.h"
#include "Ray2.h"

namespace param {

	class Raycaster2 {
	public:
		Raycaster2();
		virtual ~Raycaster2();


	std::vector<CastEl> Cast(const Ray2& ray,
				const std::vector<Edge2*>& edges);
	};
} /* namespace param */

#endif /* RAYCASTER2_H_ */
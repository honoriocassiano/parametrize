/*
 * PartialPolygon.h
 *
 *  Created on: 13 de dez de 2018
 *      Author: cassiano
 */

#ifndef PARTIALPOLYGON_H_
#define PARTIALPOLYGON_H_

#include <glm/detail/type_vec.hpp>
#include <vector>

namespace param {
struct Polygon;
} /* namespace param */

namespace param {

class PartialPolygon {
public:
	PartialPolygon();
	virtual ~PartialPolygon();

	void AddVertex(const glm::vec2& p);

	void Draw(bool points = false) const;

	void Clear();

	Polygon* GetPolygon() const;

	bool Close();
	bool IsClosed() const;

private:
	std::vector<glm::vec2> vertices;

	bool closed;
};

} /* namespace param */

#endif /* PARTIALPOLYGON_H_ */

/*
 * ParametrizedPolygon.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "ParametrizedPolygon.h"

#include "Ray2.h"
#include "Raycaster2.h"

#include <glm/geometric.hpp>

namespace param {

struct VertexIndex {
	std::size_t layer;
	std::size_t pos;
};

VertexIndex GetByPosition(std::vector<VertexHolder>* layers, std::size_t i) {
	std::size_t level = -1, pos = -1;
	std::size_t levels = layers->size();

	if (i >= layers->back().count) {
		return VertexIndex { 0, 0 };
	}

	for (auto l = 0; l < levels; ++l) {
		auto temp = 1 << l;

		if (l < (levels - 1)) {
			if ((i - temp) % (1 << (l + 1)) == 0) {
				level = levels - level - 1;
				pos = (i - temp) / (1 << (l + 1));

				break;
			}
		} else {
			level = 0;
			pos = i / (1 << i);
		}
	}

	return VertexIndex { level, pos };
}

void ToNormal(glm::vec2& v) {
	auto tmp = v.x;
	v.x = -v.y;
	v.y = tmp;
}

ParametrizedPolygon::ParametrizedPolygon() :
		mesh(nullptr), child(nullptr), level(0), layers(nullptr) {
}

//ParametrizedPolygon::ParametrizedPolygon(float* _distances,
//		glm::vec2* _vertices, std::size_t _size) :
//		ParametrizedPolygon(_distances, _vertices, _size, nullptr) {
//}
ParametrizedPolygon::ParametrizedPolygon(SimpleMesh* mesh, glm::vec2* _vertices,
		std::size_t _size) :
		ParametrizedPolygon(mesh, _vertices, _size, 0, nullptr) {
}

//ParametrizedPolygon::ParametrizedPolygon(float* _distances,
//		glm::vec2* _vertices, std::size_t _size, unsigned char _level,
//		std::vector<VertexHolder>* _layers) :
//		child(nullptr), level(_level), layers(_layers) {
ParametrizedPolygon::ParametrizedPolygon(SimpleMesh* _mesh, glm::vec2* vertices,
		std::size_t size, unsigned char _level,
		std::vector<VertexHolder>* _layers, glm::vec2* normals) :
		mesh(_mesh), child(nullptr), level(_level), layers(_layers) {

	if (!layers) {
		layers = new std::vector<VertexHolder>;
	}

	std::size_t count = size;

	if (layers->size() > 0) {
		count += layers->back().count;
	}

	if (!normals) {
		normals = new glm::vec2[size];

		glm::vec2 lastNormal;

		for (std::size_t i = 0; i < size; ++i) {

			auto current = (i + 1) % size;

			auto v1 = vertices[current];
			auto v2 = vertices[(i + 2) % size];

			auto temp1 = glm::normalize(v2 - v1);

			if (i == 0) {
				auto vFirst = vertices[i];
				lastNormal = glm::normalize(v1 - vFirst);

				ToNormal(lastNormal);
			}

			ToNormal(temp1);

			normals[i] = (temp1 + lastNormal) * 0.5f;

			lastNormal = temp1;
		}
	}

	layers->emplace_back(vertices, normals, nullptr, size, count);
}

ParametrizedPolygon::~ParametrizedPolygon() {

	if (child) {
		delete child;
	}

	auto temp = layers->back();

	delete[] temp.vertices;
	delete[] temp.normals;

	if (temp.distances) {
		delete temp.distances;
	}

	layers->pop_back();

	if (!level) {
		delete layers;
	}
}

Polygon ParametrizedPolygon::GetPolygon() {
	if (child) {
		return child->GetPolygon();
	}

	auto currentPos = GetByPosition(layers, 0);

	auto vertices = new glm::vec2[layers->back().count];

	for (auto i = 0; i < layers->back().count; ++i) {
		auto nextPos = GetByPosition(layers, (i + 1) % layers->back().count);

		const auto& current = layers->at(currentPos.layer);
		const auto& next = layers->at(nextPos.layer);

		auto v1 = current.vertices[currentPos.pos]
				+ current.normals[currentPos.pos]
						* current.distances[currentPos.pos];

		auto v2 = next.vertices[nextPos.pos]
				+ next.normals[nextPos.pos] * next.distances[nextPos.pos];

		vertices[i] = (v1 + v2) * 0.5f;
	}

	return Polygon(vertices, layers->back().count);
}

float ParametrizedPolygon::Parametrize() {

	if (child) {
		return child->Parametrize();
	}

	auto ref = layers->at(level);

	glm::vec2 origin, direction;

	Ray2 ray(origin, direction);
	Raycaster2 caster;

	float* newDistances = new float[ref.count];
	glm::vec2* newVertices = new glm::vec2[ref.count];

	auto currentPos = GetByPosition(layers, 0);

	for (auto i = 0; i < layers->back().count; ++i) {
		auto nextPos = GetByPosition(layers, (i + 1) % layers->back().count);

		const auto& current = layers->at(currentPos.layer);
		const auto& next = layers->at(nextPos.layer);

		auto v1 = current.vertices[currentPos.pos]
				+ current.normals[currentPos.pos]
						* current.distances[currentPos.pos];

		auto v2 = next.vertices[nextPos.pos]
				+ next.normals[nextPos.pos] * next.distances[nextPos.pos];

		newVertices[i] = (v1 + v2) * 0.5f;

		//		this->GetNext(i, step, origin, direction);
		//
		//		ray.Set(origin, direction);
		//
		//		// TODO Add max distance to cast
		//		auto casts = caster.Cast(ray, mesh);
		//
		//		if (casts.size() > 2) {
		//			// TODO Mark to recast
		//		}
		//
		//		if (casts.size() > 0) {
		//			distances[i] = casts[0].distance;
		//		} else {
		//			distances[i] = NAN;
		//		}
		currentPos = nextPos;
	}

	child = new ParametrizedPolygon(mesh, newVertices, ref.count, level + 1,
			layers);

	return 0;
}

} /* namespace param */


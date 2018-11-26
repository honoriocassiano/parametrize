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

	if (layers->size() == 1) {
		return VertexIndex { 0, i };
	}

	std::size_t level = 0, pos = 0;
	std::size_t levels = layers->size();

	if (i >= layers->back().count) {
		return VertexIndex { 0, 0 };
	}

	if (layers->size() == 3 && i == 2) {
		int a = 1;
	}

	for (auto l = 0; l < levels; ++l) {
		auto temp = 1 << l;

		if (l < (levels - 1)) {
			if ((i - temp) % (1 << (l + 1)) == 0) {
				level = levels - l - 1;
				pos = (i - temp) / (1 << (l + 1));

				break;
			}
		} else {
			level = 0;
			pos = i / (1 << l);
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

	layers->emplace_back(vertices, normals, nullptr, size, count);

	if (!normals) {
//		normals = ComputeNormals(vertices, size);
		ComputeNormals();
	}
}

void ParametrizedPolygon::ComputeNormals() {

	auto& ref = layers->back();

//	auto normals = new glm::vec2[size];
	ref.normals = new glm::vec2[ref.size];

//	glm::vec2 lastNormal;

//	for (std::size_t i = 0; i < ref.count; ++i) {
	for (std::size_t i = 1; i < ref.count; i += 2) {

		auto prev = GetByPosition(layers, i - 1);
		auto curr = GetByPosition(layers, i);
		auto next = GetByPosition(layers, (i + 1) % ref.count);

//		auto v1 = ref.vertices[current];
//		auto v2 = ref.vertices[(i + 4) % ref.count];
		auto v1 = layers->at(prev.layer).vertices[prev.pos]
				+ (layers->at(prev.layer).normals[prev.pos]
						* layers->at(prev.layer).distances[prev.pos]);

		auto v2 = layers->at(curr.layer).vertices[curr.pos];

		auto v3 = layers->at(next.layer).vertices[next.pos]
				+ (layers->at(next.layer).normals[next.pos]
						* layers->at(next.layer).distances[next.pos]);

		auto temp1 = glm::normalize(v2 - v1);
		auto temp2 = glm::normalize(v3 - v2);

//		if (i == 1) {
////			auto vFirst = ref.vertices[i];
//			auto first = GetByPosition(layers, i);
//			auto vFirst = layers->at(first.layer).vertices[first.pos];
//
//			lastNormal = glm::normalize(v1 - vFirst);
//
//			ToNormal(lastNormal);
//		}

		ToNormal(temp1);
		ToNormal(temp2);

		layers->at(curr.layer).normals[curr.pos] = (temp1 + temp2) * 0.5f;

//		printf("%f %f\n", v3.x, v3.y);
//		printf("%f %f\n", layers->at(next.layer).vertices[next.pos].x, layers->at(next.layer).vertices[next.pos].y);
//		printf("%f %f\n", layers->at(next.layer).normals[next.pos].x, layers->at(next.layer).normals[next.pos].y);
//		printf("%f\n\n", layers->at(next.layer).distances[next.pos]);

		printf("%f %f\n", v1.x, v1.y);
		printf("%f %f\n", v2.x, v2.y);
		printf("%f %f\n\n", v3.x, v3.y);

//		printf("%f %f\n", layers->at(curr.layer).normals[curr.pos].x,
//				layers->at(curr.layer).normals[curr.pos].y);

//		lastNormal = temp1;
	}
//	for (std::size_t i = 0; i < size; ++i) {
//
//		auto current = (i + 1) % size;
//
//		auto v1 = vertices[current];
//		auto v2 = vertices[(i + 2) % size];
//
//		auto temp1 = glm::normalize(v2 - v1);
//
//		if (i == 0) {
//			auto vFirst = vertices[i];
//			lastNormal = glm::normalize(v1 - vFirst);
//
//			ToNormal(lastNormal);
//		}
//
//		ToNormal(temp1);
//
//		normals[i] = (temp1 + lastNormal) * 0.5f;
//
//		lastNormal = temp1;
//	}

//	return normals;
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
//	if (child) {
//		return child->GetPolygon();
//	}

//	auto currentPos = GetByPosition(layers, 0);

	auto vertices = new glm::vec2[layers->back().count];

	for (std::size_t i = 0; i < layers->back().count; ++i) {
		auto currentPos = GetByPosition(layers, i);

//		printf("%lu %lu\n", currentPos.layer, currentPos.pos);

		const auto& current = layers->at(currentPos.layer);
//		const auto& next = layers->at(nextPos.layer);

//		printf("%lu, %f %f\n", i, current.vertices[currentPos.pos].x,
//				current.vertices[currentPos.pos].y);

		auto v1 = current.vertices[currentPos.pos]
				+ current.normals[currentPos.pos]
						* current.distances[currentPos.pos];

//		auto v2 = next.vertices[nextPos.pos]
//				+ next.normals[nextPos.pos] * next.distances[nextPos.pos];

//		vertices[i] = (v1 + v2) * 0.5f;
		vertices[i] = v1;

//		printf("%f %f\n", current.vertices[currentPos.pos].x,
//				current.vertices[currentPos.pos].y);
//		printf("%f %f\n", current.normals[currentPos.pos].x,
//						current.normals[currentPos.pos].y);
//		printf("%f\n\n", current.distances[currentPos.pos]);
	}

//	for (std::size_t l = 0; l < layers->size(); ++l) {
//		for (std::size_t i = 0; i < layers->at(l).size; ++i) {
//			printf("%lu %f %f\n", i, layers->at(l).normals[i].x,
//					layers->at(l).normals[i].y);
//		}
//		printf("\n");
//	}

	return Polygon(vertices, layers->back().count);
}

float ParametrizedPolygon::Parametrize() {

	if (child) {
		return child->Parametrize();
	} else if (!layers->back().distances) {
		// Calc distances

		auto& ref = layers->back();

		glm::vec2 origin, direction;

		Ray2 ray(origin, direction);
		Raycaster2 caster;

		float* newDistances = new float[ref.size];
		glm::vec2* newVertices = new glm::vec2[ref.size];

		ref.distances = new float[ref.size];

		for (std::size_t i = 0; i < layers->back().size; ++i) {

			auto current = layers->back();

			ray.Set(current.vertices[i], current.normals[i]);

			// TODO Add max distance to cast
			auto casts = caster.Cast(ray, *mesh);

			if (casts.size() > 2) {
				// TODO Mark to recast
			}

			if (casts.size() > 0) {
				current.distances[i] = casts[0].distance;
			}
		}
	} else {
		// Create child

		auto& ref = layers->back();

		glm::vec2 origin, direction;

		Ray2 ray(origin, direction);
		Raycaster2 caster;

		float* newDistances = new float[ref.count];
		glm::vec2* newVertices = new glm::vec2[ref.count];

		auto currentPos = GetByPosition(layers, 0);

//		ref.distances = new float[ref.size];

		for (std::size_t i = 0; i < layers->back().count; ++i) {
			auto nextPos = GetByPosition(layers,
					(i + 1) % layers->back().count);

			const auto& current = layers->at(currentPos.layer);
			const auto& next = layers->at(nextPos.layer);

			auto v1 = current.vertices[currentPos.pos]
					+ (current.normals[currentPos.pos]
							* current.distances[currentPos.pos]);

			auto v2 = next.vertices[nextPos.pos]
					+ (next.normals[nextPos.pos] * next.distances[nextPos.pos]);

			newVertices[i] = (v1 + v2) * 0.5f;

//			printf("%lu, %f %f\n", i, current.vertices[currentPos.pos].x,
//					current.vertices[currentPos.pos].y);

//			printf("%f %f\n", newVertices[i].x, newVertices[i].y);

//			ray.Set(origin, direction);
//
//			// TODO Add max distance to cast
//			auto casts = caster.Cast(ray, *mesh);
//
//			if (casts.size() > 2) {
//				// TODO Mark to recast
//			}
//
//			if (casts.size() > 0) {
//				current.distances[currentPos.pos] = casts[0].distance;
//			} else {
//				current.distances[currentPos.pos] = NAN;
//			}

			currentPos = nextPos;
		}

		child = new ParametrizedPolygon(mesh, newVertices, ref.count, level + 1,
				layers);

		//	TODO Return this value
		child->Parametrize();
	}

	return 0;
}

} /* namespace param */


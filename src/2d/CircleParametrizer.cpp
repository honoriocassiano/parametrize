/*
 * CircleParametrizer.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "CircleParametrizer.h"

#include "Ray2.h"
#include "Raycaster2.h"

#include <glm/geometric.hpp>

namespace param {

CircleParametrizer::CircleParametrizer(SimpleMesh* _mesh, std::size_t size,
		glm::vec2 _center, float _radius) :
		mesh(_mesh), center(_center), radius(_radius), level(0) {

	auto step = 1.0 / size;

	auto vertices = new glm::vec2[size];
	auto normals = new glm::vec2[size];

	glm::vec2 lastNormal;

	for (long i = 0; i < size; ++i) {

		float u = (-i * step) * 2 * M_PI;

		vertices[i] = glm::vec2(radius * cos(u), radius * sin(u));
		normals[i] = glm::normalize(center - vertices[i]);
	}

	layers.emplace_back(vertices, normals, nullptr, size, size);
}

//void CircleParametrizer::ComputeNormals() {
//
//	auto& ref = layers.back();
//
//	ref.normals = new glm::vec2[ref.size];
//
//	for (std::size_t i = 1; i < ref.count; i += 2) {
//
//		auto prev = GetByPosition(layers, i - 1);
//		auto curr = GetByPosition(layers, i);
//		auto next = GetByPosition(layers, (i + 1) % ref.count);
//
//		auto v1 = layers.at(prev.layer).vertices[prev.pos]
//				+ (layers.at(prev.layer).normals[prev.pos]
//						* layers.at(prev.layer).distances[prev.pos]);
//
//		auto v2 = layers.at(curr.layer).vertices[curr.pos];
//
//		auto v3 = layers.at(next.layer).vertices[next.pos]
//				+ (layers.at(next.layer).normals[next.pos]
//						* layers.at(next.layer).distances[next.pos]);
//
//		auto temp1 = glm::normalize(v2 - v1);
//		auto temp2 = glm::normalize(v3 - v2);
//
//		ToNormal(temp1);
//		ToNormal(temp2);
//
//		layers.at(curr.layer).normals[curr.pos] = (temp1 + temp2) * 0.5f;
//	}
//}

CircleParametrizer::~CircleParametrizer() {

	auto temp = layers.back();

	delete[] temp.vertices;
	delete[] temp.normals;

	if (temp.distances) {
		delete temp.distances;
	}

	layers.pop_back();
}

Polygon CircleParametrizer::GetPolygon() {

	auto vertices = new glm::vec2[layers.back().count];

	for (std::size_t i = 0; i < layers.back().count; ++i) {
		auto currentPos = GetByPosition(layers, i);

		const auto& current = layers.at(currentPos.layer);

		auto v1 = current.vertices[currentPos.pos]
				+ current.normals[currentPos.pos]
						* current.distances[currentPos.pos];

		vertices[i] = v1;
	}

	return Polygon(vertices, layers.back().count);
}

float CircleParametrizer::Parametrize() {

//	if (child) {
//		return child->Parametrize();
//	} else if (!layers.back().distances) {

//	printf("%p %lu\n", layers.back().distances, layers.size());

	if (layers.back().distances) {

		auto ray = Ray2();

		auto size = layers.back().count;

		auto newVertices = new glm::vec2[size];

//		for (std::size_t i = 0; i < size; ++i) {
		for (std::size_t i = 0; i < size; ++i) {
			auto posPrev = GetByPosition(layers, (i + size - 1) % size);
			auto posCurr = GetByPosition(layers, i);
			auto posNext = GetByPosition(layers, (i + 1) % size);

			auto prev = layers[posPrev.layer];
			auto curr = layers[posCurr.layer];
			auto next = layers[posNext.layer];

			auto pPrev = prev.vertices[posPrev.pos]
					+ (prev.distances[posPrev.pos] * prev.normals[posPrev.pos]);

			auto pCurr = curr.vertices[posCurr.pos]
					+ (curr.distances[posCurr.pos] * curr.normals[posCurr.pos]);

			auto pNext = next.vertices[posNext.pos]
					+ (next.distances[posNext.pos] * next.normals[posNext.pos]);

			ray.Set(curr.vertices[posCurr.pos], curr.normals[posCurr.pos]);

			float u = ray.Intersect(pPrev, pNext);

//			printf("%d %f %f\n", isnan(u), u, curr.distances[posCurr.pos]);

			if (!isnan(u) && u < curr.distances[posCurr.pos]) {
//				printf("aaaaa\n");
				newVertices[i] = curr.vertices[posCurr.pos]
						+ (u * curr.normals[posCurr.pos]);

//				printf("%f %f\n", pPrev.x, pPrev.y);
//				printf("%f %f\n", pNext.x, pNext.y);
//
//				printf("%f\n", prev.distances[posPrev.pos]);
			} else {

				if (prev.vertices[posPrev.pos]) {

				}

				newVertices[i] = (prev.vertices[posPrev.pos]
						+ next.vertices[posNext.pos]) * 0.5f;

//				printf("aaaaa\n");
			}

		}

		for (std::size_t i = 0; i < size; ++i) {
			printf("%f %f\n", newVertices[i].x, newVertices[i].y);
		}
	}

	if ((layers.size() == 1) && !layers.back().distances) {
		// Calc distances
		auto& ref = layers.back();

		glm::vec2 origin, direction;

		Ray2 ray(origin, direction);
		Raycaster2 caster;

		float* newDistances = new float[ref.size];
		glm::vec2* newVertices = new glm::vec2[ref.size];

		ref.distances = new float[ref.size];

		for (std::size_t i = 0; i < layers.back().size; ++i) {

			auto current = layers.back();

			ray.Set(current.vertices[i], current.normals[i]);

			// TODO Add max distance to cast
			auto casts = caster.Cast(ray, *mesh);

			if (casts.size() > 2) {
				// TODO Mark to recast
			}

			if (casts.size() > 0) {
				current.distances[i] = casts[0].distance;

				printf("%lu: %f\n", i, casts[0].distance);
			}
		}
	}

//	} else {
//		// Create child
//		auto& ref = layers.back();
//
//		glm::vec2 origin, direction;
//
//		Ray2 ray(origin, direction);
//		Raycaster2 caster;
//
//		float* newDistances = new float[ref.count];
//		glm::vec2* newVertices = new glm::vec2[ref.count];
//
//		auto currentPos = GetByPosition(layers, 0);
//
//		for (std::size_t i = 0; i < layers.back().count; ++i) {
//			auto nextPos = GetByPosition(layers, (i + 1) % layers.back().count);
//
//			const auto& current = layers.at(currentPos.layer);
//			const auto& next = layers.at(nextPos.layer);
//
//			auto v1 = current.vertices[currentPos.pos]
//					+ (current.normals[currentPos.pos]
//							* current.distances[currentPos.pos]);
//
//			auto v2 = next.vertices[nextPos.pos]
//					+ (next.normals[nextPos.pos] * next.distances[nextPos.pos]);
//
//			newVertices[i] = (v1 + v2) * 0.5f;
//
//			currentPos = nextPos;
//		}
//
////		child = new CircleParametrizer(mesh, newVertices, ref.count, level + 1,
////				layers);
////
////		//	TODO Return this value
////		child->Parametrize();
//	}

	return 0;

}

} /* namespace param */


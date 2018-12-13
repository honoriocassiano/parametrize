/*
 * CircleParametrizer.cpp
 *
 *  Created on: 5 de nov de 2018
 *      Author: cassiano
 */

#include "CircleParametrizer.h"

#include "Ray2.h"
#include "Raycaster2.h"
#include "utils.h"

#include <stdio.h>
#include <cmath>
#include <glm/geometric.hpp>

namespace param {

CircleParametrizer::CircleParametrizer(Polygon* _mesh, std::size_t size,
		glm::vec2 _center, float _radius) :
		mesh(_mesh), numRays(size), center(_center), radius(_radius) {

	auto step = 1.0 / size;

	auto vertices = new glm::vec2[size];
	auto normals = new glm::vec2[size];
	auto actives = new bool[size];

	glm::vec2 lastNormal;

	for (long i = 0; i < size; ++i) {

		float u = (-i * step) * 2 * M_PI;

		vertices[i] = glm::vec2(radius * cos(u) + center.x,
				radius * sin(u) + center.y);
		normals[i] = glm::normalize(center - vertices[i]);
		actives[i] = true;
	}

	layers.emplace_back(vertices, normals, nullptr);
}

CircleParametrizer::~CircleParametrizer() {

	for (auto l : layers) {
		if (l.distances) {
			delete l.distances;
		}

		delete l.vertices;
		delete l.normals;
	}
}

Polygon* CircleParametrizer::GetPolygon() {

	if (!layers.size()
			|| ((layers.size() == 1) && (layers.back().distances == nullptr))) {
		return nullptr;
	}

	auto vertices = new glm::vec2[Count()];

	for (std::size_t i = 0; i < Count(); ++i) {
		auto currentPos = GetByPosition(layers, i);

		const auto& current = layers.at(currentPos.layer);

		auto v1 = current.vertices[currentPos.pos]
				+ current.normals[currentPos.pos]
						* current.distances[currentPos.pos];

		vertices[i] = v1;

	}

	return new Polygon(vertices, Count());
}

void CircleParametrizer::ComputeNormals() {
	auto& ref = layers.back();

	auto count = Count();
	auto size = Size(layers.size() - 1);

	ref.normals = new glm::vec2[size];

	for (std::size_t i = 1; i < count; i += 2) {

		auto prev = GetByPosition(layers, i - 1);
		auto curr = GetByPosition(layers, i);
		auto next = GetByPosition(layers, (i + 1) % count);

		auto v1 = layers.at(prev.layer).vertices[prev.pos]
				+ (layers.at(prev.layer).normals[prev.pos]
						* layers.at(prev.layer).distances[prev.pos]);

		auto v2 = layers.at(curr.layer).vertices[curr.pos];

		auto v3 = layers.at(next.layer).vertices[next.pos]
				+ (layers.at(next.layer).normals[next.pos]
						* layers.at(next.layer).distances[next.pos]);

		auto temp1 = glm::normal(glm::normalize(v2 - v1));
		auto temp2 = glm::normal(glm::normalize(v3 - v2));

		ref.normals[curr.pos] = -(temp1 + temp2) * 0.5f;
	}
}

std::size_t CircleParametrizer::Count() const {
	return (1l << layers.size() - 1l) * numRays;
}

std::size_t CircleParametrizer::Size(std::size_t level) const {
	return (level == 0) ? numRays : (1 << (level - 1)) * numRays;
}

void CircleParametrizer::Cast() {

	auto& currentLayer = layers.back();

	// Safe distance to start a ray
	auto safeDistance = 2 * radius;
	auto size = Size(layers.size() - 1);

	glm::vec2 origin, direction;

	Ray2 ray(origin, direction);
	Raycaster2 caster;

	currentLayer.distances = new float[size];

	if (layers.size() > 1) {
		auto polygon = GetPolygon();

		for (std::size_t i = 0; i < size; ++i) {
			ray.Set(currentLayer.vertices[i], currentLayer.normals[i]);

//			auto maxDistanceFront = INFINITY;
//			auto maxDistanceBack = -INFINITY;
//
//			// Cast current polygon
//			auto meshCasts = caster.Cast(ray, polygon);
//
//			// Get first cast on front and back
//			for (std::size_t j = 0; j < meshCasts.size(); ++j) {
//
//				auto d = meshCasts[j].distance;
//
//				// If distance is close to 0, consider as a front cast
//				if (d > -REL_TOL && d < maxDistanceFront) {
//					maxDistanceFront = d;
//				} else if (d < -REL_TOL && d > maxDistanceBack) {
//					maxDistanceBack = d;
//				}
//			}
//
//			maxDistanceFront += safeDistance + REL_TOL;
//			maxDistanceBack += safeDistance - REL_TOL;

			bool inside;
			std::size_t countBack = 0;
			float lastDistance = INFINITY;
			std::vector<CastEl> casts;

			// Move ray origin to a safe point
			ray.Set(
					currentLayer.vertices[i]
							+ (-(safeDistance) * currentLayer.normals[i]),
					currentLayer.normals[i]);

			casts = caster.Cast(ray, mesh);

			// Count casts behind real origin
			while ((casts[countBack].distance < (safeDistance - REL_TOL))
					&& (countBack < casts.size())) {
				++countBack;
			}

			// If odd, point is inside the surface
			inside = (countBack % 2);

			// If inside, get first cast on back
			// Else, first cast on front
			if (inside) {
				currentLayer.distances[i] = casts[countBack - 1].distance
						- safeDistance;
			} else {
				currentLayer.distances[i] = casts[countBack].distance
						- safeDistance;
			}
		}
	} else if (layers.size() == 1) {
		for (std::size_t i = 0; i < size; ++i) {

			std::size_t castSize = 0;
			float lastDistance = INFINITY;
			std::vector<CastEl> casts;

			ray.Set(currentLayer.vertices[i], currentLayer.normals[i]);
			casts = caster.Cast(ray, mesh);

			// Filter casts with vertices
			for (auto cast : casts) {
				if (!closeto(cast.distance, lastDistance)) {

					casts.push_back(cast);

					lastDistance = cast.distance;
				}
			}

			currentLayer.distances[i] = casts[0].distance;
		}
	} else {
		return;
	}
}

void CircleParametrizer::UnParametrize() {

	if (layers.size() > 1) {

		auto& l = layers.back();

		if (l.distances) {
			delete l.distances;
		}

		delete l.vertices;
		delete l.normals;

		layers.pop_back();
	} else if (layers.size() == 1) {

		auto& l = layers.back();

		if (l.distances) {
			delete l.distances;

			l.distances = nullptr;
		}
	}
}

float CircleParametrizer::Parametrize() {

	if (layers.back().distances) {
		auto& ref = layers.back();
		auto count = Count();

		glm::vec2 origin, direction;

		Ray2 ray(origin, direction);
		Raycaster2 caster;

		glm::vec2* newVertices = new glm::vec2[count];

		auto currentPos = GetByPosition(layers, 0);

		for (std::size_t i = 0; i < count; ++i) {
			auto nextPos = GetByPosition(layers, (i + 1) % count);

			const auto& current = layers.at(currentPos.layer);
			const auto& next = layers.at(nextPos.layer);

			auto v1 = current.vertices[currentPos.pos]
					+ (current.normals[currentPos.pos]
							* current.distances[currentPos.pos]);

			auto v2 = next.vertices[nextPos.pos]
					+ (next.normals[nextPos.pos] * next.distances[nextPos.pos]);

			newVertices[i] = (v1 + v2) * 0.5f;

			currentPos = nextPos;
		}

		layers.emplace_back(newVertices, nullptr, nullptr);

		ComputeNormals();
	}

	Cast();

	// TODO Return some value
	return 0;

}

} /* namespace param */


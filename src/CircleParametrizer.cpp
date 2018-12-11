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

		vertices[i] = glm::vec2(radius * cos(u), radius * sin(u));
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
	auto& ref = layers.back();
	// Calc distances
	glm::vec2 origin, direction;

	Ray2 ray(origin, direction);
	Raycaster2 caster;

	auto size = Size(layers.size() - 1);

	float* newDistances = new float[size];
	glm::vec2* newVertices = new glm::vec2[size];

	ref.distances = new float[size];

	auto polygon = GetPolygon();
	auto current = layers.back();

	auto safeDistance = 2 * radius;

	for (std::size_t i = 0; i < size; ++i) {

		ray.Set(current.vertices[i], current.normals[i]);
//		ray.Set(current.vertices[i] + (-safeDistance * current.normals[i]),
//				current.normals[i]);

//		printf("%f %f\n", current.vertices[i].x, current.vertices[i].y);
//		printf("%f %f\n", current.normals[i].x, current.normals[i].y);
//		printf("\n");

		auto maxDistanceFront = INFINITY;
		auto maxDistanceBack = -INFINITY;

		auto meshCasts = caster.Cast(ray, polygon);

		ray.Set(current.vertices[i] + (-(safeDistance) * current.normals[i]),
				current.normals[i]);

		for (std::size_t j = 0; j < meshCasts.size(); ++j) {
			auto d = meshCasts[j].distance;

//			if (closeto(d, 0)) {
//				// TODO IGNORE IT ALL
//				current.distances[i] = 0;
//
//				break;
//			} else {

			if (d > -REL_TOL && d < maxDistanceFront) {
				maxDistanceFront = d + REL_TOL;
			} else if (d < -REL_TOL && d > maxDistanceBack) {
				maxDistanceBack = d + REL_TOL;
			}
		}

//		auto casts = caster.Cast(ray, mesh, maxDistanceFront, maxDistanceBack);
		auto casts = caster.Cast(ray, mesh);

//		for (const auto& c : casts) {
//			printf("%f %f %f\n", c.distance, maxDistanceFront, maxDistanceBack);
//		}
		//*************************************************************

		//			std::size_t countBack = 0;
		std::size_t countFront = 0;
		float lastDistance = INFINITY;
		bool testOrientation = false;

//		while ((casts[countBack].distance < safeDistance)
//				&& (countBack < casts.size())) {
//			++countBack;
//
//			if(closeto(casts[countBack].u, round(casts[countBack].u))) {
//				++duplicated;
//			}
//		}

		std::vector<CastEl> realCasts;

		// Filter casts with vertices
		for (auto cast : casts) {

//			printf("cast: %f %f\n", cast.distance, lastDistance);

			if (!closeto(cast.distance, lastDistance)) {

				lastDistance = cast.distance;

				cast.distance -= safeDistance;

				realCasts.push_back(cast);
			}
		}

		{

			while ((realCasts[realCasts.size() - countFront - 1].distance
					> -REL_TOL) && (countFront < realCasts.size())) {
				++countFront;
			}
		}

//		for (const auto& cast : casts) {
//
////			if (casts[countBack].distance < safeDistance) {
//			if (cast.distance < safeDistance) {
//				++countBack;
//			}
//
//			if (closeto(cast.distance, lastDistance)) {
//				++duplicated;
//				lastDistance = cast.distance;
//			}
//
////			if (closeto(casts[countBack].u, round(casts[countBack].u))) {
////				++duplicated;
////			}
//		}

//		auto castSize = casts.size() - duplicated;
		auto castSize = realCasts.size();

		//			bool outside = (countBack % 2);
//		bool inside = ((realCasts.size() - countFront) % 2);
		bool inside = countFront % 2;

//		if (testOrientation) {
//			inside = !realCasts[countBack - 1].in;
////			outside = (countBack % 2);
//		}

//		printf("%lu, %lu\n", countFront, realCasts.size());
//
////		if(countBack == 2) {
//		for (auto c : realCasts) {
//			printf("%e\n", c.distance);
//		}
//		printf("\n");
//		}

		if (inside) {

			printf("INSIDE!\n");
			printf("%lu %lu %lu\n", countFront, casts.size(), realCasts.size());
			printf("%f %f\n", current.vertices[i].x, current.vertices[i].y);

//			for(auto& c: realCasts) {
//				printf("%f\n", c.distance);
//			}

//		if (inside || (!inside && countBack == realCasts.size())) {
			//				current.distances[i] = casts[countBack].distance;
//			current.distances[i] = realCasts[countFront - 1].distance;

			current.distances[i] =
					realCasts[realCasts.size() - countFront - 1].distance;

			//				printf("FIRST\n");
		} else {

//			current.distances[i] = realCasts[0].distance;
			if (countFront < realCasts.size()) {
				current.distances[i] = realCasts[countFront].distance;
			} else {
				current.distances[i] = realCasts[0].distance;
			}

//			current.distances[i] =

//			printf("%lu, %lu\n", countBack, realCasts.size());

			//				current.distances[i] = casts[countBack - 1].distance;
			//				current.distances[i] = 1;
			//				printf("SECOND\n");

			//				printf("%f\n", casts[countBack - 1].distance);

			//				printf("%f %f\n", current.vertices[i].x,
			//						current.vertices[i].y);
			//				for (const auto& c : casts) {
			//					printf("%f\n", c.distance);
			//				}

		}

		//			printf("%f %f\n", current.vertices[i].x, current.vertices[i].y);
		//			printf("%f %f\n", current.normals[i].x, current.normals[i].y);
//		printf("%f\n", current.distances[i]);
		printf("\n");

		//*************************************************************

//		if (closeto(casts[0].distance, 0)) {
//			current.distances[i] = 0;
//		} else {
////			std::size_t countBack = 0;
//			std::size_t countBack = 0;
//
//			while ((casts[countBack].distance < 0) && (countBack < casts.size())) {
//				++countBack;
//			}
//
////			bool outside = (countBack % 2);
//			bool outside = ((casts.size() - countBack) % 2);
//
//			if (outside) {
////				current.distances[i] = casts[countBack].distance;
//				current.distances[i] = casts[countBack - 1].distance;
//
////				printf("FIRST\n");
//			} else {
//
////				printf("%lu\n", casts.size());
//
//				current.distances[i] = casts[countBack].distance;
////				current.distances[i] = casts[countBack - 1].distance;
////				current.distances[i] = 1;
////				printf("SECOND\n");
//
////				printf("%f\n", casts[countBack - 1].distance);
//
////				printf("%f %f\n", current.vertices[i].x,
////						current.vertices[i].y);
////				for (const auto& c : casts) {
////					printf("%f\n", c.distance);
////				}
//
//			}
//
////			printf("%f %f\n", current.vertices[i].x, current.vertices[i].y);
////			printf("%f %f\n", current.normals[i].x, current.normals[i].y);
//			printf("%f\n", current.distances[i]);
//			printf("\n");
//		}

//		if (casts.size() > 0) {
//			current.distances[i] = casts[0].distance;
//		}
	}

//	printf("\n");
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
		// Create child
		auto& ref = layers.back();
		auto count = Count();

		glm::vec2 origin, direction;

		Ray2 ray(origin, direction);
		Raycaster2 caster;

		float* newDistances = new float[count];
		glm::vec2* newNormals = new glm::vec2[count];
		glm::vec2* newVertices = new glm::vec2[count];
//		bool* newActives = new bool[count];

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

		layers.emplace_back(newVertices, nullptr, newDistances);

		ComputeNormals();
	}

	Cast();

// TODO Return some value
	return 0;

}

} /* namespace param */


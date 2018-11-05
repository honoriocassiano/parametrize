#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>

#include "2d/CircleParametrizer.h"
#include "2d/Edge2.h"

using namespace param;

int main(int argc, char const *argv[]) {

	std::size_t size = 10;
	float x = 1, y = 1;

	glm::vec2 ps[4] = { glm::vec2(-x, -y), glm::vec2(-x, y), glm::vec2(x, y),
			glm::vec2(x, -y) };

	Edge2 e1(&ps[0], &ps[1]);
	Edge2 e2(&ps[1], &ps[2]);
	Edge2 e3(&ps[2], &ps[3]);
	Edge2 e4(&ps[3], &ps[0]);

	CircleParametrizer p(glm::vec2(), 3);

	auto f = p.Paramatrize(std::vector<Edge2*> { &e1, &e2, &e3, &e4 }, size);

	auto poly = p.GetPolygon(f, size);
//	for (std::size_t i = 0; i < size; ++i) {
//		printf("%.3f ", f[i]);
//	}
//	printf("\n");

//	float x = 1, y = 1, z = 1;
//	glm::vec3 points[4] = { glm::vec3(0, y, 0), glm::vec3(x, -y, 0), glm::vec3(
//			-x, -y, 0), glm::vec3(0, 0, -z) };
//
//	Triangle t1(&points[0], &points[2], &points[1]);
//
//	Triangle t2(&points[3], &points[0], &points[1]);
//	Triangle t3(&points[3], &points[1], &points[2]);
//	Triangle t4(&points[3], &points[2], &points[0]);
//
////	Ray ray(glm::vec3(0, 0, -0.5), glm::vec3(0, 0, 1));
//	int w, h;
//
//	PlaneParametrizer p(glm::vec3(-1, -1, 2), glm::vec3(0, 2, 0),
//			glm::vec3(2, 0, 0));
//
////	auto d = p.Paramatrize(std::vector<Triangle*> { &t1, &t2, &t3, &t4 }, 0.5f,
////			0.5f, w, h);
//	auto d = p.Paramatrize(std::vector<Triangle*> { &t1 }, 0.5f, 1.1f, w, h);
//
//
////	for (int i = 0; i < w * h; ++i) {
////		std::printf("%f\n", d[i]);
////	}

	return 0;
}

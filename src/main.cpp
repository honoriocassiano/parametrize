#include "Triangle.h"
#include "Ray.h"
#include "Raycaster.h"

#include <cstdio>

using namespace param;

int main(int argc, char const *argv[]) {

	float x = 1, y = 1, z = 1;

	glm::vec3 points[4] = { glm::vec3(0, y, 0), glm::vec3(x, -y, 0), glm::vec3(
			-x, -y, 0), glm::vec3(0, 0, -z) };

	Triangle t1(&points[0], &points[2], &points[1]);

	Triangle t2(&points[3], &points[0], &points[1]);
	Triangle t3(&points[3], &points[1], &points[2]);
	Triangle t4(&points[3], &points[2], &points[0]);

//	Ray ray(glm::vec3(0, 0, -0.5), glm::vec3(0, 0, 1));
	Ray ray(glm::vec3(0, 0, 0.5), glm::vec3(0, 0, -1));

	Raycaster caster;

	auto values = caster.Cast(ray,
			std::vector<Triangle*> { &t1, &t2, &t3, &t4 });

	for (auto v : values) {
		std::printf("%.3lf, %d\n", v.distance, v.in);
	}

	return 0;
}

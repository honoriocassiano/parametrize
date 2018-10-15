#include "Triangle.h"
#include "Ray.h"
#include "Raycaster.h"

#include <cstdio>

using namespace param;

int main(int argc, char const *argv[]) {

	float x = 1, y = 1;

	glm::vec3 points[3] = { glm::vec3(0, y, 0), glm::vec3(x, -y, 0), glm::vec3(
			-x, -y, 0) };

	Triangle t(&points[0], &points[1], &points[2]);

	Ray ray(glm::vec3(x, -y, -0.5), glm::vec3(0, 0, 1));

	Raycaster caster;

	auto values = caster.Cast(ray, std::vector<Triangle*> { &t });

	for (auto v : values) {
		std::printf("%f", v);
	}

	return 0;
}

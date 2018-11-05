#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <vector>

#include "PlaneParametrizer3.h"
#include "Triangle.h"

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
	int w, h;

	PlaneParametrizer p(glm::vec3(-1, -1, 2), glm::vec3(0, 2, 0),
			glm::vec3(2, 0, 0));

//	auto d = p.Paramatrize(std::vector<Triangle*> { &t1, &t2, &t3, &t4 }, 0.5f,
//			0.5f, w, h);
	auto d = p.Paramatrize(std::vector<Triangle*> { &t1 }, 0.5f, 1.1f, w, h);


//	for (int i = 0; i < w * h; ++i) {
//		std::printf("%f\n", d[i]);
//	}

	return 0;
}

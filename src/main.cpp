#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <GL/gl.h>
#include <cstddef>
#include <vector>

#include "2d/CircleParametrizer.h"
#include "2d/Edge2.h"
#include "2d/Polygon.h"
#include "2d/CircleParametrizer2.h"

using namespace param;

void init(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char const *argv[]) {

	int w = 800, h = 800;
	std::size_t size = 20;
	float x = 1, y = 1;

	glm::vec2 ps[4] = { glm::vec2(-x, -y), glm::vec2(-x, y), glm::vec2(x, y),
			glm::vec2(x, -y) };

	int idx[4] = { 0, 1, 2, 3 };

	SimpleMesh sm { ps, idx, 4 };

//	Edge2 e1(&ps[0], &ps[1]);
//	Edge2 e2(&ps[1], &ps[2]);
//	Edge2 e3(&ps[2], &ps[3]);
//	Edge2 e4(&ps[3], &ps[0]);

//	CircleParametrizer p({ps, idx, 4}, size, glm::vec2(), 3);
	CircleParametrizer2 p(&sm, 4, glm::vec2(), 3);

//	auto f = p.Paramatrize(std::vector<Edge2*> { &e1, &e2, &e3, &e4 }, size);
	auto f = p.Parametrize();

//	auto poly1 = p.GetPolygon();

	f = p.Parametrize();
	p.Parametrize();

	auto poly2 = p.GetPolygon();

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(w, h, "Parametrizer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

//	glfwSetCursorPosCallback(window, pick/Squares);

//	glfwSetKeyCallback(window, key_callback);
	init(w, h);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

//		glColor3f(1, 1, 1);
//		poly1.Draw();

//		glColor3f(1, 0, 0);
		poly2.Draw(1);
//		poly.Draw(true);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
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

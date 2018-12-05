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

	glm::vec2 ps[8] = { glm::vec2(-x, -y), glm::vec2(-x, y), glm::vec2(x, y),
			glm::vec2(x, -y), glm::vec2(0.25, -0.25), glm::vec2(0.5, 0.5),
			glm::vec2(-0.5, 0.5), glm::vec2(-0.25, -0.25) };

	int idx[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	SimpleMesh sm { ps, idx, 8 };

	CircleParametrizer p(&sm, 4, glm::vec2(), 4);
//	CircleParametrizer2 p(&sm, 4, glm::vec2(), 3);
//	CircleParametrizer2 p(&sm, 3, glm::vec2(), 3);

	auto f = p.Parametrize();

	p.Parametrize();

//	auto poly1 = p.GetPolygon();

//	f = p.Parametrize();
//	f = p.Parametrize();



//	auto poly2 = p.GetPolygon();
//
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(w, h, "Parametrizer", NULL, NULL);
//	if (!window) {
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
////	glfwSetCursorPosCallback(window, pick/Squares);
//
////	glfwSetKeyCallback(window, key_callback);
//	init(w, h);
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window)) {
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glColor3f(0.5, 0.5, 0.5);
////		poly1.Draw();
//		sm.Draw();
//
////		glColor3f(1, 0, 0);
//		glColor3f(1, 1, 1);
//		poly2.Draw();
//
//		glColor3f(1, 0, 0);
//		poly2.Draw(true);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();

	return 0;
}

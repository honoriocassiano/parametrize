#include <glm/detail/type_vec.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/X.h>
#include <cstddef>

#include "2d/CircleParametrizer.h"
#include "2d/Polygon.h"
#include "Window.h"

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

	auto ps = new glm::vec2[8] { glm::vec2(-x, -y), glm::vec2(-x, y), glm::vec2(
			x, y), glm::vec2(x, -y), glm::vec2(0.25, -0.25), glm::vec2(0.5,
			0.5), glm::vec2(-0.5, 0.5), glm::vec2(-0.25, -0.25) };

	auto sm = new Polygon(ps, 8);

	auto p = new CircleParametrizer(sm, 4, glm::vec2(), 4);

	param::Window::cp = p;
	param::Window::originalPolygon = sm;

	param::Window window(w, h);

	window.Run();

	return 0;
}

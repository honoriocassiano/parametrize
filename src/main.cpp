#include <glm/detail/type_vec.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstddef>

#include "CircleParametrizer.h"
#include "Polygon.h"
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

	param::Window window(w, h);

	window.Run();

	return 0;
}

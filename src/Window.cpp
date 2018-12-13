/*
 * Window.cpp
 *
 *  Created on: 10 de dez de 2018
 *      Author: cassiano
 */

#include "Window.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdexcept>

#include "CircleParametrizer.h"
#include "Polygon.h"

namespace param {
class CircleParametrizer;
} /* namespace param */

namespace param {

int Window::width = 0;
int Window::height = 0;

GLFWwindow* Window::window = nullptr;
CircleParametrizer* Window::cp = nullptr;

Polygon* Window::originalPolygon = nullptr;
Polygon* Window::parametrizedPolygon = nullptr;

Window::Window(int _width, int _height) {

	width = _width;
	height = _height;

	/* Initialize the library */
	if (!glfwInit()) {
		throw std::runtime_error("Error initializing GLFW!");
	}
}

Window::~Window() {
	glfwDestroyWindow(window);

	if (originalPolygon) {
		delete originalPolygon;
	}

	if (parametrizedPolygon) {
		delete parametrizedPolygon;
	}

	window = nullptr;
	originalPolygon = nullptr;
	parametrizedPolygon = nullptr;

	width = 0;
	height = 0;
}

void Window::Run() {
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Parametrizer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("Error creating window!");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	Init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (originalPolygon) {
			glColor3f(0.5, 0.5, 0.5);
			originalPolygon->Draw();
		}

		if (parametrizedPolygon) {
			glColor3f(1, 1, 1);
			parametrizedPolygon->Draw();

			glColor3f(1, 0, 0);
			parametrizedPolygon->Draw(true);
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

void Window::KeyPressed(GLFWwindow * window, int key, int scancode, int action,
		int mods) {

	if (action == GLFW_PRESS) {

		switch (key) {

		case GLFW_KEY_S:
			Parametrize();
			break;

		case GLFW_KEY_E:
//			ResetScene();
			break;

		case GLFW_KEY_U:
			UnParametrize();
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		}

	}
}

void Window::ResetScene() {
	delete cp;
	delete originalPolygon;
}

void Window::Parametrize() {

	if (parametrizedPolygon) {
		delete parametrizedPolygon;

		parametrizedPolygon = nullptr;
	}

	if (cp && originalPolygon) {

		cp->Parametrize();

		parametrizedPolygon = cp->GetPolygon();
	}
}

void Window::UnParametrize() {

	if (parametrizedPolygon) {
		delete parametrizedPolygon;

		parametrizedPolygon = nullptr;
	}

	if (cp) {
		cp->UnParametrize();

		parametrizedPolygon = cp->GetPolygon();
	}
}

void Window::Init() {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glfwSetKeyCallback(window, KeyPressed);
}

} /* namespace param */

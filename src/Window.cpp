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
#include "PartialPolygon.h"
#include "Polygon.h"

namespace param {
class CircleParametrizer;
} /* namespace param */

namespace param {

int Window::width = 0;
int Window::height = 0;

bool Window::drawing = true;
bool Window::showingBoundingRect = false;
bool Window::showingParametrizer = false;

GLFWwindow* Window::window = nullptr;
CircleParametrizer* Window::cp = nullptr;

Polygon* Window::originalPolygon = nullptr;
Polygon* Window::parametrizedPolygon = nullptr;
PartialPolygon Window::partialPolygon = PartialPolygon();

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

		Render();
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
			ResetScene();
			break;

		case GLFW_KEY_U:
			UnParametrize();
			break;

		case GLFW_KEY_C:
			if (cp) {
				showingParametrizer = !showingParametrizer;
			}
			break;

		case GLFW_KEY_B:
			if (originalPolygon) {
				showingBoundingRect = !showingBoundingRect;
			}
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
	}
}

void Window::ResetScene() {

	partialPolygon.Clear();

	if (!drawing) {
		if (cp) {
			delete cp;
		}

		if (originalPolygon) {
			delete originalPolygon;
		}

		if (parametrizedPolygon) {
			delete parametrizedPolygon;
		}

		cp = nullptr;
		originalPolygon = nullptr;
		parametrizedPolygon = nullptr;
	}

	drawing = true;
	showingBoundingRect = false;
	showingParametrizer = false;
}

void Window::Parametrize() {

	if (!cp) {

		if (originalPolygon) {

			glm::vec2 center;
			float radius;

			originalPolygon->GetBoundingCircle(center, radius);

			cp = new CircleParametrizer(originalPolygon, 8, center,
					radius * 1.1);
		}
	}

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

void Window::MouseClick(GLFWwindow* window, int button, int action, int mods) {

	if (drawing) {
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				if (!partialPolygon.IsClosed()) {

					double windowX, windowY;
					double worldX, worldY;

					glfwGetCursorPos(window, &windowX, &windowY);

					// Convert window to world coordinates
					worldX = 2 * ((windowX - width / 2) / width);
					worldY = 2 * (((height - windowY) - height / 2) / height);

					partialPolygon.AddVertex(glm::vec2(worldX, worldY));
				}
			} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				bool closed = partialPolygon.Close();

				if (closed) {

					originalPolygon = partialPolygon.GetPolygon();

					drawing = false;
				} else {
					printf("Cannot close the polygon!\n");
				}
			}
		}
	}
}

void Window::Init() {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glfwSetKeyCallback(window, KeyPressed);
	glfwSetMouseButtonCallback(window, MouseClick);
}

void Window::Render() {
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	if (drawing) {
		glColor3f(1, 1, 1);
		partialPolygon.Draw();
	} else {
		if (originalPolygon) {
			glColor3f(0.5, 0.5, 0.5);
			originalPolygon->Draw();

			if (showingBoundingRect) {
				glColor3f(0, 0, 1);
				originalPolygon->DrawBoundingRect();
			}
		}

		if (parametrizedPolygon) {
			glColor3f(1, 1, 1);
			parametrizedPolygon->Draw();

			glColor3f(1, 0, 0);
			parametrizedPolygon->Draw(true);
		}

		if (showingParametrizer) {
			cp->Draw();
		}
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

} /* namespace param */

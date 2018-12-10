/*
 * Window.h
 *
 *  Created on: 10 de dez de 2018
 *      Author: cassiano
 */

#ifndef WINDOW_H_
#define WINDOW_H_
namespace param {
class CircleParametrizer;
} /* namespace param */

namespace param {
struct Polygon;
} /* namespace param */

struct GLFWwindow;

namespace param {

class Window {

public:

	Window(int width, int height);
	virtual ~Window();

	void Run();

private:
	static void KeyPressed(GLFWwindow *, int, int, int, int);
	static void ResetScene();
	static void Parametrize();
	static void UnParametrize();

	void Init();

public:

	static GLFWwindow* window;
	static int width;
	static int height;

	static Polygon* originalPolygon;
	static Polygon* parametrizedPolygon;
	static CircleParametrizer* cp;
};

} /* namespace param */

#endif /* WINDOW_H_ */

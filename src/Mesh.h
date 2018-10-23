/*
 * Mesh.h
 *
 *  Created on: 22 de out de 2018
 *      Author: cassiano
 */

#ifndef MESH_H_
#define MESH_H_

#include <glm/vec3.hpp>

#include "GL/GLee.h"
#include <GL/gl.h>

namespace param {

class Mesh {
public:
	Mesh(glm::vec3* positions, std::size_t pSize, int* indices,
			std::size_t iSize);

	void Draw() const;

	virtual ~Mesh();

private:

	std::size_t size;

	GLuint vbo;
	GLuint ibo;
};

} /* namespace param */

#endif /* MESH_H_ */

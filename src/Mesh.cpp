/*
 * Mesh.cpp
 *
 *  Created on: 22 de out de 2018
 *      Author: cassiano
 */

#include "Mesh.h"

namespace param {

Mesh::Mesh(glm::vec3* positions, std::size_t pSize, int* indices,
		std::size_t iSize) :
		vbo(0), ibo(0), size(iSize / 4) {

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, pSize, (GLvoid *) positions, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, (GLvoid *) indices,
	GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw() const {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_QUADS, size, GL_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

} /* namespace param */

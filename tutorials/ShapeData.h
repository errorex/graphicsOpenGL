#pragma once 
#include "Vertex.h"

#include<GL/glew.h>

class ShapeData {
public:
	ShapeData();
	Vertex *vertices;
	GLushort *indices;
	GLuint numVertices;
	GLuint numIndices;

	GLsizeiptr vertexBufferSize();
	GLsizeiptr indexBufferSize();
	void cleanUp();
};
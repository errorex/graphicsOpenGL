#include "ShapeData.h"

ShapeData::ShapeData(): 
	vertices(0), numVertices(0), 
	indices(0), numIndices(0){

}

GLsizeiptr ShapeData::vertexBufferSize() {
	return numVertices * sizeof(Vertex);
}

GLsizeiptr ShapeData::indexBufferSize() {
	return numIndices * sizeof(GLushort);	
}

void ShapeData::cleanUp(){
	delete [] vertices;
	delete [] vertices;
	numVertices = numVertices = 0;
}
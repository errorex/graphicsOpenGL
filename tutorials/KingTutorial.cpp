
#include "KingTutorial.h"
#include <unistd.h>
#include "ShapeGenerator.h"

GLuint num_indices;

KingTutorial::KingTutorial() : MyGLWindow(){
	// printf("KingTutorial constructor\n");
	num_triangles = 0;
}

int KingTutorial::loadGraphics(){
	// MyGLWindow::loadGraphics();
	cout << "KingTutorial loadGraphics" << endl;

	glewInit();

	glEnable(GL_DEPTH_TEST);	

	ShapeData shape = ShapeGenerator::makeCube();
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);


	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	
	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");	
	vertexColor = glGetAttribLocation(programID, "vertexColor");

	//use our shader	
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	
	glEnableVertexAttribArray(vertexColor);
	glVertexAttribPointer(vertexColor,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*6, (char*)(sizeof(GLfloat) * 3));

	
	glUseProgram(programID);	

	num_indices = shape.numIndices;
	// shape.cleanUp();
	return 0;
}

void KingTutorial::unloadGraphics(){

	
	// triangle.cleanUp();	

	// Cleanup VBO
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


void KingTutorial::runGraphics(){

	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		
	glfwGetWindowSize(window, &window_width, &window_height);
	glViewport(0,0, window_width, window_height);

	vec3 dominatingColor(1.0f,0.0f,0.0f);

	mat4 projectionMatrix = perspective(radians(60.0f), ((float)window_width)/window_height, 0.1f, 10.0f);
	mat4 projectTranslationMatrix = translate(projectionMatrix, vec3(0.0f, 0.0f,-3.0f));			
	mat4 fullTransformMatrix = rotate(projectTranslationMatrix, radians(54.0f), vec3(1.0f, 0.0f, 0.0f));
	
	GLuint dominatingColorUniformLocation = glGetUniformLocation(programID, "dominatingColor");	
	GLuint fullTransformMatrixUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
	

	glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);	
	//sendAnotherTringleToOpenGL();

	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// usleep(50 * 1000);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, 0);

	// glDisableVertexAttribArray(vertexPosition_modelspaceID);
}


KingTutorial::~KingTutorial(){
	
}



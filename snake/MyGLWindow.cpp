#include "MyGLWindow.h"

MyGLWindow::MyGLWindow(void){
	printf("\nmyglwindow constructor\n");
}

int MyGLWindow::loadGraphics(void){

	printf("MyGLWindow::loadGraphics\n");

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;		
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	//Get a handle for our "MVP" uniform
	// only during the initialisation
	MatrixID = glGetUniformLocation(programID, "MVP");
	
	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");

	//Pojection matrix: 45º Field of view, 4:3 ratio, display range: 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f,0.1f,100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,1.0f,100.0f);

	View = glm::lookAt(
		glm::vec3(4,3,3), 	//camera is at (4,3,3), in world space
		glm::vec3(0,0,0),	// and looks at the origin
		glm::vec3(0,1,0)  	// Head is up (set to 0,-1,0 to look upside-down)
	);

	//Model matrix: an identity matrix (model will be at origin)
	Model = glm::mat4(1.0f);

	//Our ModelViewProjection  : multiplication of our 3 matrices
	MVP = Projection * View * Model;

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return 0;
}

void MyGLWindow::unloadGraphics(void){	
	// Cleanup VBO
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void MyGLWindow::runGraphics(void){	

	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programID);

	// Send our tranformation to the currently bound shader, in the MVP uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		vertexPosition_modelspaceID, // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(vertexPosition_modelspaceID);

}


int MyGLWindow::init(void){
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 700, 240, "Tutorial 03 - Matrices", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	

	if(loadGraphics() < 0){
		return -1;
	}

	do{
		
		runGraphics();
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	unloadGraphics();

	return 0;
}



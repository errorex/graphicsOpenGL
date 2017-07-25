#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW



// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

#include <iostream>

using namespace std;
using glm::vec3;
using glm::mat4;
using glm::radians;

class MyGLWindow {
private:
	

protected:
	GLFWwindow* window;
	GLuint programID;
	GLuint MatrixID;	
	GLuint vertexPosition_modelspaceID;
	GLuint vertexColor;
	glm::mat4 Projection;	
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;
	static const GLfloat g_vertex_buffer_data[];
	GLuint vertexBuffer;
	GLuint indexBuffer;

	virtual int loadGraphics(void);
	virtual void unloadGraphics(void);
	virtual void runGraphics(void);

public:

	MyGLWindow(void);
	int init(void);
};

#endif
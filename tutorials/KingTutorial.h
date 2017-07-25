#ifndef KING_TUTORIAL_H
#define KING_TUTORIAL_H

#include "MyGLWindow.h"

class KingTutorial : public MyGLWindow
{

private:
	GLsizei window_width;
	GLsizei window_height;
	GLuint num_triangles;
public:
	void sendAnotherTringleToOpenGL();
	int loadGraphics();	
	void runGraphics();
	void unloadGraphics();

	KingTutorial();
	~KingTutorial();
};

#endif
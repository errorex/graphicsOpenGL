#ifndef _BALL_OBJECT_H_
#define _BALL_OBJECT_H_

#include "GameObject.h"

class BallObject : public GameObject{
	public:
		GLfloat		radius;
		GLboolean 	stuck;

		BallObject();
		BallObject(glm::vec2 pos, GLfloat pRadius, glm::vec2 velocity, 
			Texture2D sprite);

		glm::vec2 move(GLfloat dt, GLuint window_width);
		void reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
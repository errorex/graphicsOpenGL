#include "BallObject.h"

BallObject::BallObject()
	: GameObject(), radius(12.5f), stuck(GL_TRUE) {}

BallObject::BallObject(glm::vec2 pos, GLfloat pRadius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2( pRadius * 2, pRadius * 2 ), sprite, glm::vec3( 1.0f ), velocity), 
		radius(pRadius), stuck(GL_TRUE) {}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity){
	this->position = position;
	this->velocity = velocity;
	this->stuck = GL_TRUE;
}

glm::vec2 BallObject::move(GLfloat dt, GLuint window_width){
	if(!this->stuck){
		this->position += this->velocity * dt;

		if(this->position.x <= 0.0f){
			this->velocity.x = - this->velocity.x;
			this->position.x = 0.0f;
		}else if(this->position.x + this->size.x >= window_width){
			this->velocity.x = -this->velocity.x;
			this->position.x = window_width - this->size.x;
		}

		if(this->position.y <= 0.0f){
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}
	}
	return this->position;
}
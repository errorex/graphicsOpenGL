#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	glm::vec2 	position, size, velocity;
	glm::vec3 	color;
	GLfloat 	rotation;
	GLboolean 	isSolid, destroyed;

	Texture2D sprite;

	GameObject();
	GameObject(glm::vec2 pPosition, glm::vec2 pSize, Texture2D pSprite, glm::vec3 pColor = glm::vec3(1.0f), glm::vec2 pVelocity = glm::vec2(0.0f, 0.0f) );

	virtual void draw(SpriteRenderer &pRenderer);


	~GameObject(){ }
	
};

#endif
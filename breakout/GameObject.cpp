#include "GameObject.h"

GameObject::GameObject() 
	: position(0, 0), size(1, 1), velocity(0.0f), color(1.0f), 
	rotation(0.0f), sprite(), isSolid(false), destroyed(false) { 

	}

GameObject::GameObject(glm::vec2 pPosition, glm::vec2 pSize, 
		Texture2D pSprite, glm::vec3 pColor, glm::vec2 pVelocity) 
	: position(pPosition), size(pSize), velocity(pVelocity), 
	color(pColor), rotation(0.0f), sprite(pSprite), isSolid(false), 
	destroyed(false) { 

	}
	
void GameObject::draw(SpriteRenderer &pRenderer){
	
	pRenderer.DrawSprite(this->sprite, this->position, this->size, 
		this->rotation, this->color);

}

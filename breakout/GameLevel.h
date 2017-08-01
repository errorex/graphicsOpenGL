#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel
{
public:
	std::vector<GameObject> bricks;

	GameLevel() { }
	GameLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight) { 
		load(file, levelWidth, levelHeight); 
	}

	void load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	void draw(SpriteRenderer &pRenderer);
	GLboolean isComplete();

	~GameLevel() { }
private:
	void init(std::vector<std::vector<GLuint>> tileData, 
		GLuint levelWidth, GLuint levelHeight);
};

#endif
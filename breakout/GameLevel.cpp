#include "GameLevel.h"

#include <fstream>
#include <sstream>
#include <iostream>


void GameLevel::draw(SpriteRenderer &pRenderer){
	for (GameObject &tile : this->bricks){
		if(!tile.destroyed){
			tile.draw(pRenderer);
		}
	}
}

GLboolean GameLevel::isComplete(){
	for (GameObject &tile : this->bricks){
		if(!tile.isSolid && !tile.destroyed){
			return GL_FALSE;
		}
	}
	return GL_TRUE;
}

void GameLevel::load(const GLchar *file, GLuint levelWidth, GLuint levelHeight){

	std::cout << "GameLevel::load(" << file << " ," << levelWidth << ", " << levelHeight << std::endl;

	this->bricks.clear();

	GLuint tileCode;
	GameLevel level;

	std::string line;
    std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;

	if(fstream){
		while(std::getline(fstream, line)){
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while(sstream >> tileCode){
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if(tileData.size() > 0){
			this->init(tileData, levelWidth, levelHeight);
		}
	}

}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, 
		GLuint levelWidth, GLuint levelHeight){

	std::cout << "GameLevel::init" << std::endl;

	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width);
	GLfloat unit_height = levelHeight / height;

	

	for (GLuint y = 0; y < height; ++y) {
		
		for (GLuint x = 0; x < width; ++x) {
			
			// std::cout << "tileData["<<x<<"]["<<y<<"]="<<tileData[y][x]<<std::endl;
			if (tileData[y][x] >= 1) {

				glm::vec3 color = glm::vec3(1.0f);
				std::string blockType = "block";

				switch (tileData[y][x]){
					case 1:
						color = glm::vec3(0.8f, 0.8f, 0.7f);
						blockType = "block_solid";
						break;
					case 2:
						color = glm::vec3(0.2f, 0.6f, 1.0f);
						break;
					case 3:
						color = glm::vec3(0.0f, 0.7f, 0.0f);
						break;
					case 4:
						color = glm::vec3(0.8f, 0.8f, 0.4f);
						break;
					case 5:
						color = glm::vec3(1.0f, 0.5f, 0.0f);
						break;
				}

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture(blockType),
					color)); 
			}	

		}

	}

}

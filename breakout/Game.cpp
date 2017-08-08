#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <iostream>
#include <string>
#include <memory>

// Game-related State data
SpriteRenderer  *gRenderer;
GameObject      *gPlayer;
BallObject      *gBall;


Game::Game(GLuint width, GLuint height) 
	: state(GAME_ACTIVE), keys(), width(width), height(height) 
{ 

}

Game::~Game()
{
    delete gRenderer;
    delete gPlayer;
}

void Game::Init()
{
    std::cout << "breakout init" << std::endl;


    // Load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), 
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);


    // Load textures
    ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", GL_TRUE, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", GL_TRUE, "paddle");

    //load levels
    for(GLushort x = 0; x < this->levelsQuantity; x++){
        std::string str = "levels/" + std::to_string(x+1) + ".lvl";
        //this->levels.reserve(this->levelsQuantity);
        this->levels.push_back(*std::unique_ptr<GameLevel>(new GameLevel(str.c_str(), this->width, this->height*0.5)));
    }
    this->levelNum = 0;

    //configure game objects
    glm::vec2 playerPos = glm::vec2(this->width / 2 - PLAYER_SIZE.x / 2, 
        this->height - PLAYER_SIZE.y);
    Texture2D paddleTexture = ResourceManager::GetTexture("paddle");
    gPlayer = new GameObject(playerPos, PLAYER_SIZE, paddleTexture);


    //configure the Ball
    glm::vec2 ballPos = playerPos + glm::vec2( PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 );
    Texture2D faceTexture = ResourceManager::GetTexture("face");
    gBall = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, faceTexture);

    // Set render-specific controls
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    gRenderer = new SpriteRenderer(myShader);    
}

void Game::Update(GLfloat pDt)
{
    if(this->state == GAME_ACTIVE){
        gBall->move(pDt,this->width);
        doCollisions();
    }
    
}


void Game::ProcessInput(GLfloat pDt)
{
    if (this->state == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * pDt;
        // Move playerboard
        if (this->keys[GLFW_KEY_A])
        {
            if (gPlayer->position.x >= 0){
                gPlayer->position.x -= velocity;
                if(gBall->stuck){
                    gBall->position.x -= velocity;
                }
            }
        }

        if (this->keys[GLFW_KEY_D])
        {
            if (gPlayer->position.x <= this->width - gPlayer->size.x){
                gPlayer->position.x += velocity;
                if(gBall->stuck){
                    gBall->position.x += velocity;
                }
            }
        }

        if(this->keys[GLFW_KEY_SPACE]){
            gBall->stuck = false;
        }               
    }

    if(this->keys[GLFW_KEY_P]){                        
        this->state = this->state == GAME_ACTIVE ? GAME_PAUSED : GAME_ACTIVE;
    }

}

void Game::Render()	
{
    if(this->state == GAME_ACTIVE || this->state == GAME_PAUSED){
        Texture2D background = ResourceManager::GetTexture("background");
        gRenderer->DrawSprite(background, glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);

        this->levels[this->levelNum].draw(*gRenderer);

        gPlayer->draw(*gRenderer);
        gBall->draw(*gRenderer);

    }

	// Texture2D myTexture;
	// myTexture = ResourceManager::GetTexture("face");
 //    gRenderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), glm::radians(45.0f), 
 //        glm::vec3(1.0f, 1.0f, 1.0f));
}

GLboolean Game::checkCollisionsSquares(GameObject &a, GameObject &b){
    GLboolean x_collision = (a.position.x + a.size.x) >= b.position.x &&
                    (b.position.x + b.size.x) >= a.position.x;

    GLboolean y_collision =  (a.position.y + a.size.y) >= b.position.y &&
                    (b.position.y + b.size.y) >= a.position.y;

    return x_collision && y_collision;
}

GLboolean Game::checkCollisionsCircleSquare(BallObject &circle, GameObject &square){
     // Get center point circle first 
    glm::vec2 center(circle.position + circle.radius);
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(square.size.x / 2, square.size.y / 2);
    glm::vec2 aabb_center(
        square.position.x + aabb_half_extents.x, 
        square.position.y + aabb_half_extents.y
    );
    // Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    return glm::length(difference) < circle.radius;
}    

void Game::doCollisions(){
    for(GameObject &brick : this->levels[this->levelNum].bricks){
        if( checkCollisionsCircleSquare(*gBall, brick) ){
            if(!brick.destroyed){
                brick.destroyed = GL_TRUE;
            }
        }
    }
}
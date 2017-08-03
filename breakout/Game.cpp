#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "BallObject.h"
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
    gBall->move(pDt,this->width);
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

}

void Game::Render()	
{
    if(this->state == GAME_ACTIVE){
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
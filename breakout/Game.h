/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glfw3.h>

#include "GameLevel.h"
#include <vector>

#include "BallObject.h"

// Represents the current state of the game
enum GameState {    
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_PAUSED
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(1000.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    const GLushort levelsQuantity = 4;
    // Game state
    GameState              state;	
    GLboolean              keys[1024];
    GLuint                 width, height;

    std::vector<GameLevel> levels;
    GLuint                 levelNum;

    // Constructor/Destructor
    Game(GLuint pWidth, GLuint Height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // GameLoop
    void ProcessInput(GLfloat pDt);
    void Update(GLfloat pDt);
    void Render();
    GLboolean checkCollisionsSquares(GameObject &a, GameObject &b);    
    GLboolean checkCollisionsCircleSquare(BallObject &circle, GameObject &square);
    void doCollisions();
};

#endif
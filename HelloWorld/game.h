#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
#include "paddle.h"

//creates ball object
void SpawnBall();

//tracks location, collision, etc of objects over time
void StepFrame(float timeElapsed);

//creates brick objects and lays out obs in game
void SetUpScene();

//function to check for collision between ball and paddle by calculatind delta x and y 
bool willBounce(const Paddle& paddle, const Play::GameObject& ball);
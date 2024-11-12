#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
#include "paddle.h"

void SpawnBall();

void StepFrame(float timeElapsed);

void SetUpScene();

//bool willBounce(const Paddle paddle, const  GameObject brick);
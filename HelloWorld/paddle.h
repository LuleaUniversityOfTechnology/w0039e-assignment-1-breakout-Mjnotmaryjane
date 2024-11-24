#pragma once
#include "Play.h"
#include "constants.h"

//struct to build paddle
struct Paddle
{
	Play::Point2D Pos = {DISPLAY_WIDTH/2,20};		//paddle position
	int width;
	int height;
};

float Min(float x, float y);

float Max(float x, float y);

void DrawPaddle(const Paddle& paddle);

void updatePaddle( Paddle& paddle, float traverse);
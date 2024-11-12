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



void DrawPaddle(const Paddle& paddle);

void updatePaddle( Paddle& paddle, float traverse);
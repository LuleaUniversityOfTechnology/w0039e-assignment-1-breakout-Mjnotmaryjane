#include "paddle.h"
#include "Play.h"
#include "constants.h"


void DrawPaddle(const Paddle& paddle) {
	Play::Point2D bottomLeft = {paddle.Pos.x, paddle.Pos.y };
	Play::Point2D topRight = { paddle.Pos.x + 30, paddle.Pos.y + 10 };
	Play::DrawRect(bottomLeft, topRight, Play::cOrange, true);
}

void updatePaddle(Paddle& paddle, float traverse){
	paddle.Pos.x += traverse;
}
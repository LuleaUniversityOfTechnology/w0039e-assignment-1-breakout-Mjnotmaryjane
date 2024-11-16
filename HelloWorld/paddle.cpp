#include "paddle.h"
#include "Play.h"
#include "constants.h"

//creates a paddle from the draw rect play.h fucntion.
void DrawPaddle(const Paddle& paddle) {
	Play::Point2D bottomLeft = {paddle.Pos.x, paddle.Pos.y };
	Play::Point2D topRight = { paddle.Pos.x + 110, paddle.Pos.y + 10 };
	Play::DrawRect(bottomLeft, topRight, Play::cMagenta, true);
}

//used to change the position of the paddle frame by frame. couple with keyboard commands
void updatePaddle(Paddle& paddle, float traverse){
	paddle.Pos.x += traverse;
}
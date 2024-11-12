#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"



void SpawnBall() {
	const int objectID = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH /  2, DISPLAY_HEIGHT-360 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectID);
	ball.velocity = normalize({ 1,1 }) * ballSpeed;
}

void SetUpScene()
{
	for (int x = 5; x < DISPLAY_WIDTH-20; x+=17) {
		for (int y = DISPLAY_HEIGHT - 20; y > DISPLAY_HEIGHT-160 ;y-=11) {
			const int brickID = Play::CreateGameObject(ObjectType::TYPE_BRICK, { x,y }, 6, "brick");
			GameObject& brick = Play::GetGameObject(brickID);
		}
	}
	
}



void StepFrame(float elapsedTime) {
	const std::vector<int> ballIDs = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIDs = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int ball: ballIDs) {
		GameObject& currentBall = Play::GetGameObject(ball);
		Play::UpdateGameObject(currentBall);
		if (currentBall.pos.x > DISPLAY_WIDTH-5 || currentBall.pos.x<0) {
			currentBall.velocity.x = currentBall.velocity.x*(-1);
		}
		if (currentBall.pos.y > DISPLAY_HEIGHT-5 || currentBall.pos.y < 0) {
			currentBall.velocity.y = currentBall.velocity.y * (-1);
		}
		Play::DrawObject(currentBall);
		
	}
	for (int brick : brickIDs) {
		GameObject& currentBrick = Play::GetGameObject(brick);		
		for(int ball: ballIDs){
			GameObject& currentBall = Play::GetGameObject(ball);
			if (Play::IsColliding(currentBall, currentBrick)) {
				Play::DestroyGameObject(currentBrick.GetId());
				currentBall.velocity *= (-1);
			
			}
			else {
				Play::DrawObject(currentBrick);
			}
		}

	}
}



#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"



void SpawnBall() {
	const int objectID = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH /  2, DISPLAY_HEIGHT - 360 }, 4, "ball");
}

void StepFrame(float elapsedTime) {
	const std::vector<int> ballIDs = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int ball: ballIDs) {
		Play::DrawObject(Play::GetGameObject(ball));
	}
}



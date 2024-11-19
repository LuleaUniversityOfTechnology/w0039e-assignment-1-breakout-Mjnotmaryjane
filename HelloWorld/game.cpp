#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "paddle.h"
#include <algorithm>
#include <fstream>
#include <iostream>

//global var from Paddle struct
Paddle pad;

//global var for current player score
unsigned int CurrentScore;


//int variable to track dynamic array size.
unsigned int ScoreSize = 5;
//Dynamically allocated array for high score keeping
unsigned int* pHighScores;


//File variable for loading and saving
fstream ScoreFile;

//prints list of high scores
void HighScoresDraw() {
	int displayDecrement=260;
	Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - 60, DISPLAY_HEIGHT - 240), "High Scores: ");
	for (int i = 0; i < 5; i++) {
		std::string Score = std::to_string(pHighScores[i]);
		Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - 60, DISPLAY_HEIGHT - displayDecrement), Score.c_str());
		displayDecrement += 20;
	}
}

//sorts the Highscore array. call in gam set up!
void Sort() {
	std::sort((pHighScores), (pHighScores + ScoreSize), [](int a, int b) {
		return a > b; });
}
		
//checks current score when game ends. call in stepframe. only checks last item in array.
void ScoreCheck() {
	if (CurrentScore > pHighScores[4]) {
		pHighScores[4] = CurrentScore;
		std::sort((pHighScores),(pHighScores + ScoreSize), [](int a, int b) {
			return a > b; });
	}
	CurrentScore = 0;
}


//creates ball object 
void SpawnBall() {
	const int objectID = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH /  2, DISPLAY_HEIGHT-200 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectID);
	ball.velocity = normalize({ 1,-1 }) * ballSpeed;
}

//creates brick objects and lays out obs in game
void SetUpScene()
{
	for (int x = 5; x < DISPLAY_WIDTH-20; x+=17) {
		for (int y = DISPLAY_HEIGHT - 20; y > DISPLAY_HEIGHT-160 ;y-=11) {
			const int brickID = Play::CreateGameObject(ObjectType::TYPE_BRICK, { x,y }, 6, "brick");
			GameObject& brick = Play::GetGameObject(brickID);
		}
	}
	
}


//function to check for collision between ball and paddle by calculatind delta x and y 
//make sure topLefy and bottomRightX match DrawPaddle in paddle.cpp tp avoid collision issues
bool willBounce(const Paddle& paddle, const Play::GameObject& ball) {
	const float topLeftX = paddle.Pos.x;
	const float topLeftY = paddle.Pos.y+10;
	const float bottomRightX = paddle.Pos.x+110;
	const float bottomRightY = paddle.Pos.y;
	const float dx = ball.pos.x - std::max(topLeftX, std::min(ball.pos.x, bottomRightX));
	const float dy = ball.pos.y - std::max(topLeftY, std::min(ball.pos.y, bottomRightY));
	return (dx * dx + dy * dy) < (ball.radius*ball.radius);
}


//resets game while remaining inside stepFrame
void ResetGame() {
	Play::DestroyAllGameObjects();
	pad.Pos.x = (DISPLAY_WIDTH / 2);
	SetUpScene();
	SpawnBall();
}

void FileSave(){
	ScoreFile.open("Scores.txt", ios::out);
	if (ScoreFile.is_open()) {
		for (int i = 0; i < 5; i++) {
			ScoreFile << pHighScores[i] << endl;
		}
		ScoreFile.close();
	}
	delete[] pHighScores;
}

void loadFile(){
	ScoreFile.open("Scores.txt",ios::in);
	if (ScoreFile.is_open()) {
		std::string firstline;
		int count = 0;
		while (std::getline(ScoreFile, firstline)) {
			++count;
		}
		ScoreSize = count;
		ScoreFile.close();

	ScoreFile.open("Scores.txt", ios::in);
	if (ScoreFile.is_open()) {
		std::string line;
		pHighScores = new unsigned int[count];
		unsigned int score;
		int i = 0;
		while (std::getline(ScoreFile, line)) {
			score = std::stoi(line);
			pHighScores[i] = score;
			i++;
		}
	}
	}
	ScoreFile.close();
}


//manages objects and their interactions from frame to frame
//iterates through ball objects and updates position,veloctiy, etc.
//keeps track of block collision and destruction
void StepFrame(float elapsedTime) {
	const std::vector<int> ballIDs = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIDs = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int ball: ballIDs) {
		GameObject& currentBall = Play::GetGameObject(ball);
		Play::UpdateGameObject(currentBall);
		if (currentBall.pos.x > DISPLAY_WIDTH-5 or currentBall.pos.x < 0) {
			currentBall.velocity.x = currentBall.velocity.x*(-1);
		}
		if (currentBall.pos.y > DISPLAY_HEIGHT-5) {
			currentBall.velocity.y = currentBall.velocity.y * (-1);
		}
		Play::DrawObject(currentBall);
		if (willBounce(pad,currentBall)) {
			currentBall.velocity.y = currentBall.velocity.y * (-1);
		}
		if (currentBall.pos.y < 0) {
			ScoreCheck();
			ResetGame();
		}
	}
	for (int brick : brickIDs) {
		GameObject& currentBrick = Play::GetGameObject(brick);		
		for(int ball: ballIDs){
			GameObject& currentBall = Play::GetGameObject(ball);
			if (Play::IsColliding(currentBall, currentBrick)) {
				Play::DestroyGameObject(currentBrick.GetId());
				currentBall.velocity.y *= (-1);
				CurrentScore += 1;
			}
			else {
				Play::DrawObject(currentBrick);
			}
		}
		
	}
	if (Play::KeyDown(Play::KEY_LEFT)) {
		updatePaddle(pad, -3.0);
	}
	if (Play::KeyDown(Play::KEY_RIGHT)) {
		updatePaddle(pad, 3.0);
	}
	DrawPaddle(pad);
	HighScoresDraw();
	Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - 620, DISPLAY_HEIGHT - 320), std::to_string(CurrentScore).c_str());
}



#pragma once
#include <string>
#include <iostream>
#include <conio.h>

#include "Board.h"
#include "Snake.h"

using namespace std;

class Player {
private:
	string name;
	int score;
	Snake *snake;
public:
	Player(string playerName);
	~Player();

	string getName();

	Snake *getSnake();
	void setSnake(Snake *snake);

	int getScore();
	void setScore(int score);

	bool round(Board *board);
};
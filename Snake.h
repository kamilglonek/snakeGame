#pragma once
#include <deque>
#include <iostream>

#include "SnakePart.h"
#include "Head.h"
#include "Tail.h"
#include "Body.h"
#include "Direction.h"
#include "Board.h"

using namespace std;

class Snake
{
private:
	int headX;
	int headY;
	deque<class SnakePart *> body;
	Direction direction;
	int length;
public:
	Snake();
	~Snake();

	SnakePart *getBody(int position);
	void setupSnake(Board *board, int headX, int headY); // in uml we do not have a arrow connection between snake and board

	void move(Field *field);	

	Direction getDirection();
	void setDirection(char inputKey);

	int getHeadX();
	void setheadX(int headX);

	int getHeadY();
	void setHeadY(int headY);

	int getLength();

	void lengthen(int amount);

	bool affect(Surprise * surprise, int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten);
};


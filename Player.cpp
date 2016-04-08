#include "Player.h"


Player::Player(string playerName) {
	this->name = playerName;
	this->snake = new Snake();
}

Player::~Player() {
	delete snake;
}

string Player::getName() {
	return name;
}

Snake* Player::getSnake() {
	return this->snake;
}

void Player::setSnake(Snake *snake) {
	this-> snake=snake;
}


int Player::getScore() {
	return score;
}

void Player::setScore(int score) {
	this->score = score;
}

bool Player::round(Board *board) {
	bool isGameOver = false;
	Field *head = board->getField(snake->getHeadX(), snake->getHeadY());
	if (head->isEmpty()) {
		if (!head->isBound()) {
			snake->move(head);
		}
		else {
			isGameOver = true;
		}
	}
	else {
		isGameOver = true;
	}
	return isGameOver;
}

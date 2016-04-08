#include "GameField.h"

GameField::GameField() { 
}


GameField::~GameField() {
}


Surprise * GameField::getSurprise() {
	return this->surprise;
}

void GameField::setSurprise(int number) {
	if (number % 3 == 0) this->surprise = new Apple();
	else if (number % 3 == 1) this->surprise = new Banana();
	else if (number % 3 == 2) this->surprise = new Bomb();
}

void GameField::removeSurprise() {
	this->surprise = NULL;
}


bool GameField::isBound() {
	return false;
}

bool GameField::isSurprise() {
	if(surprise == NULL) return false;
	else return true;
}

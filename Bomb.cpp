#include "Bomb.h"

Bomb::Bomb() {
	this->shape = 'Q';
}

Bomb::~Bomb() {
}

char Bomb::getShape() {
	return this->shape;
}


void Bomb::getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten) {
	affectNumber = 0;
	isBomb = true;
}

bool Bomb::isNormalSurprise() {
	return false;
}

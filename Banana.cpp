#include "Banana.h"


Banana::Banana() {
	this->shape = 'C';
}

Banana::~Banana() {
}

char Banana::getShape() {
	return this->shape;
}


void Banana::getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten) {
	affectNumber = 2;
	isBomb = false;
	isSurpriseEaten = true;
}

bool Banana::isNormalSurprise() {
	return false;
}

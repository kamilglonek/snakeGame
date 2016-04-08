#include "Apple.h"


Apple::Apple() {
	this->shape = '@';
}

Apple::~Apple() {
}

char Apple::getShape() {
	return this->shape;
}

void Apple::getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten) {
	affectNumber = 1;
	isBomb = false;
	isAppleEaten = true;
}

bool Apple::isNormalSurprise() {
	return true;
}


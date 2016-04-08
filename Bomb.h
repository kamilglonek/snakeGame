#pragma once
#include "Surprise.h"
class Bomb: public Surprise {
private:
	char shape;
public:
	Bomb();
	~Bomb();

	char getShape();

	void getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten);

	bool isNormalSurprise();
};


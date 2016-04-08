#pragma once
#include "Surprise.h"

class Apple: public Surprise {
private:
	char shape;

public:
	Apple();
	~Apple();

	char getShape();


	void getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten);

	bool isNormalSurprise();
};


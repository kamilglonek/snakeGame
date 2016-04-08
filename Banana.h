#pragma once
#include "Surprise.h"

class Banana: public Surprise {
private:
	char shape;
public:
	Banana();
	~Banana();

	char getShape();

	void getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten);

	bool isNormalSurprise();
};

